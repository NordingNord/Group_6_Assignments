#include <stdint.h>
#include "ap_axi_sdata.h"
#include "hls_stream.h"

#define R_Weight 0.299
#define G_Weight 0.587
#define B_Weight 0.114
#define Image_Height 50
#define Image_Width 100

// Invert and grayscale image matrix
void Invert(hls::stream< ap_axiu<32,2,5,6>> &Data_In, hls::stream<ap_axiu<32,2,5,6>> &Data_Out){
	// Define input and output as AXI stream interfaces
	#pragma HLS INTERFACE axis port=Data_In
	#pragma HLS INTERFACE axis port=Data_Out
	#pragma hls interface s_axilite port=return

	// Working temp
	ap_axiu<32,2,5,6> tmp;
	
	// Working variables
	volatile int R = 0;
	volatile int G = 0;
	volatile int B = 0;
	volatile int Mask = 0x00000000000000ff;
	volatile int indx = 0;
	
	volatile int Image[Image_Height*Image_Width];
	
	while(1){
		// Read 32 bits
		tmp = Data_In.read();
		Mask = 0x00000000000000ff;
		for(int i = 0; i < 4; i++){
			Image[indx] = (tmp.data.to_int() & Mask) >> (i*8);
			Mask = Mask << 8;
			indx++;
		}

		// The first 8 bits are R, then G, then B. But that is only 24 bits.
		//R = (tmp.data.to_int() & 0xff0000) >> 16;
		//G = (tmp.data.to_int() & 0x00ff00) >> 8;
		//B = (tmp.data.to_int() & 0x0000ff);

		// Grayscale
		//tmp.data = R_Weight * R + G_Weight * G + B_Weight * B;

		// Invert
		//tmp.data = 255-tmp.data;

		// Write inverted image
		//Data_Out.write(tmp);

		if(tmp.last){
			break;
		}
	}

	//Make grayscale matrix
	indx = 0;
	for(int j = 0; j < Image_Height; j++){
		for(int i = 0; i < Image_Width; i++){
			R = Image[indx];
			indx++;
			G = Image[indx];
			indx++;
			B = Image[indx];
			indx++;

			tmp.data = R_Weight * R + G_Weight * G + B_Weight * B;

			tmp.data = 255-tmp.data;

			// Write inverted image
			Data_Out.write(tmp);
		}
	}
}
