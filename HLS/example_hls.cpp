#include <stdint.h>
#include "ap_axi_sdata.h"
#include "hls_stream.h"

#define Width_Size 1280
#define Height_Size 720
#define RGB 360
#define R_Weight 0.299
#define G_Weight 0.587
#define B_Weight 0.114

// Invert and grayscale image matrix
void Invert(hls::stream< ap_axis<32,2,5,6>> &Data_In, hls::stream<ap_axis<32,2,5,6>> &Data_Out){
	// Define input and output as AXI stream interfaces
	#pragma HLS INTERFACE axis port=Data_In
	#pragma HLS INTERFACE axis port=Data_Out
	#pragma hls interface s_axilite port=return

	// I want to convert stream to the bellow array
	//volatile int Image_In[Width_Size][Height_Size][RGB];
	//volatile int Image_Out[Width_Size][Height_Size];
	//volatile int Image_Gray[Width_Size][Height_Size];
	//volatile int Width_Count = 0;
	//volatile int Height_Count = 0;
	//volatile int RGB_Count = 0;
	ap_axis<32,2,5,6> tmp;

	while(1){
		// Read byte
		tmp = Data_In.read();
		// Insert data in matrix

		//Image_In[Width_Count][Height_Count][RGB_Count] = tmp.data.to_int();
		tmp.data = tmp.data+5;

		Data_Out.write(tmp);

		// Counter control
		//if(RGB_Count == RGB-1){
		//	RGB_Count = 0;
		//	if(Height_Count == Height_Size-1){
		//		Height_Count = 0;
		//		if(Width_Count == Width_Size-1){
		//			Width_Count = 0;
		//		}
		//		else{
		//			Width_Count++;
		//		}
		//	}
		//	else{
		//		Height_Count++;
		//	}
		//}
		//else{
		//	RGB_Count++;
		//}

		if(tmp.last){
			break;
		}

	}


    // Convert image to grayscale
    //for(int i = 0; i < Height_Size; i++){
    //	#pragma HLS UNROLL factor=360
    //    for(int j = 0; j < Width_Size;j++){
	//		#pragma HLS UNROLL factor=360
            // Uses the NTSC formular
    //        Image_Gray[j][i] = R_Weight * Image_In[j][i][0] + G_Weight * Image_In[j][i][1] + B_Weight * Image_In[j][i][2];
    //    }
    //}

	// Invert PGM image
	//for(int i = 0; i < Height_Size; i++){
	//	#pragma HLS UNROLL factor=360
	//	for(int j = 0; j < Width_Size;j++){
	//		#pragma HLS UNROLL factor=360
    //                    Image_Out[j][i] = (255-Image_Gray[j][i]);
	//	}
	//}

	// Convert image out back to stream
}

