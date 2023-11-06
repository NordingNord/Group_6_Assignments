#include <stdint.h>
#include "ap_axi_sdata.h"
#include "hls_stream.h"

#define R_Weight 0.299
#define G_Weight 0.587
#define B_Weight 0.114
#define Image_Height 600
#define Image_Width 800

// Invert and grayscale image matrix
void Invert(hls::stream< ap_axiu<32,2,5,6>> &Data_In, hls::stream<ap_axiu<32,2,5,6>> &Data_Out){
	// Define input and output as AXI stream interfaces
	#pragma HLS INTERFACE axis port=Data_In
	#pragma HLS INTERFACE axis port=Data_Out
	#pragma hls interface s_axilite port=return

	// Working temp
	ap_axiu<32,2,5,6> tmp, tmpout;
	
	// Working variables
	volatile int R = 0;
	volatile int G = 0;
	volatile int B = 0;
	
	// Incremental variables
	volatile int Count = 0;
	volatile int Old_R = 0;
	volatile int Old_G = 0;
	volatile int Current_Write = 0;
	volatile int Write_Count = 0;
	volatile int Inversed_Value = 0;
	volatile int Inversed_Value_Old = 0;
	volatile int Old_Data = 0;
	
	for(int i = 0; i < Image_Height*Image_Width; i++){
		#pragma HLS PIPELINE
		// Get data
		tmp = Data_In.read();
		tmpout = tmp;

		// Read needed values
		if(Count == 0){
			// The first 8 bits are R, then G, then B. But that is only 24 bits.
			R = (tmp.data.to_int() & 0x000000ff);
			G = (tmp.data.to_int() & 0x0000ff00) >> 8;
			B = (tmp.data.to_int() & 0x00ff0000) >> 16;
			Old_R = (tmp.data.to_int() & 0xff000000) >> 24;
			Count++;
			//Grayscale and invert
			Inversed_Value = 255-(R_Weight * R + G_Weight * G + B_Weight * B);
		}
		else if(Count == 1){
			R = Old_R;
			G = (tmp.data.to_int() & 0x000000ff);
			B = (tmp.data.to_int() & 0x0000ff00) >> 8;
			Old_R = (tmp.data.to_int() & 0x00ff0000) >> 16;
			Old_G = (tmp.data.to_int() & 0xff000000) >> 24;
			Count ++;
			//Grayscale and invert
			Inversed_Value = 255-(R_Weight * R + G_Weight * G + B_Weight * B);
		}
		else if(Count == 2){
			R = Old_R;
			G = Old_G;
			B = (tmp.data.to_int() & 0x000000ff);
			//Grayscale and invert
			Inversed_Value  = 255-(R_Weight * R + G_Weight * G + B_Weight * B);

			R = (tmp.data.to_int() & 0x0000ff00) >> 8;
			G = (tmp.data.to_int() & 0x00ff0000) >> 16;
			B = (tmp.data.to_int() & 0xff000000) >> 24;
			Inversed_Value_Old = 255-(R_Weight * R + G_Weight * G + B_Weight * B);
			Old_Data = 1;
			Count = 0;
		}

		if(Write_Count == 0){
			Current_Write = (Inversed_Value & 0xff) ;
			Write_Count++;
		}
		else if(Write_Count == 1){
			Current_Write = Current_Write | (Inversed_Value & 0xff) << 8;
			Write_Count++;
		}
		else if(Write_Count == 2){
			Current_Write = Current_Write | (Inversed_Value & 0xff) << 16;
			Current_Write = Current_Write | (Inversed_Value_Old & 0xff) << 24;
			tmpout.data = Current_Write;
			// Write inverted image
			Data_Out.write(tmpout);
			Write_Count =0;
			Current_Write = 0;
		}

		if(tmp.last){
			if(Write_Count != 0){
				tmpout.data = Current_Write;
				Data_Out.write(tmpout);
			}
			break;
		}
	}

//	while(1){
//		#pragma HLS PIPELINE
//		// Get data
//		tmp = Data_In.read();
//		tmpout = tmp;
//
//		// Read needed values
//		if(Count == 0){
//			// The first 8 bits are R, then G, then B. But that is only 24 bits.
//			R = (tmp.data.to_int() & 0x000000ff);
//			G = (tmp.data.to_int() & 0x0000ff00) >> 8;
//			B = (tmp.data.to_int() & 0x00ff0000) >> 16;
//			Old_R = (tmp.data.to_int() & 0xff000000) >> 24;
//			Count++;
//			//Grayscale and invert
//			Inversed_Value = 255-(R_Weight * R + G_Weight * G + B_Weight * B);
//		}
//		else if(Count == 1){
//			R = Old_R;
//			G = (tmp.data.to_int() & 0x000000ff);
//			B = (tmp.data.to_int() & 0x0000ff00) >> 8;
//			Old_R = (tmp.data.to_int() & 0x00ff0000) >> 16;
//			Old_G = (tmp.data.to_int() & 0xff000000) >> 24;
//			Count ++;
//			//Grayscale and invert
//			Inversed_Value = 255-(R_Weight * R + G_Weight * G + B_Weight * B);
//		}
//		else if(Count == 2){
//			R = Old_R;
//			G = Old_G;
//			B = (tmp.data.to_int() & 0x000000ff);
//			//Grayscale and invert
//			Inversed_Value  = 255-(R_Weight * R + G_Weight * G + B_Weight * B);
//
//			R = (tmp.data.to_int() & 0x0000ff00) >> 8;
//			G = (tmp.data.to_int() & 0x00ff0000) >> 16;
//			B = (tmp.data.to_int() & 0xff000000) >> 24;
//			Inversed_Value_Old = 255-(R_Weight * R + G_Weight * G + B_Weight * B);
//			Old_Data = 1;
//			Count = 0;
//
//		}
//
//		if(Write_Count == 0){
//			Current_Write = (Inversed_Value & 0xff) ;
//			Write_Count++;
//		}
//		else if(Write_Count == 1){
//			Current_Write = Current_Write | (Inversed_Value & 0xff) << 8;
//			Write_Count++;
//		}
//		else if(Write_Count == 2){
//			Current_Write = Current_Write | (Inversed_Value & 0xff) << 16;
//			Current_Write = Current_Write | (Inversed_Value_Old & 0xff) << 24;
//			tmpout.data = Current_Write;
//			// Write inverted image
//			Data_Out.write(tmpout);
//			Write_Count =0;
//			Current_Write = 0;
//		}
//
//		if(tmp.last){
//			if(Write_Count != 0){
//				tmpout.data = Current_Write;
//				Data_Out.write(tmpout);
//			}
//			break;
//		}
//	}
}
