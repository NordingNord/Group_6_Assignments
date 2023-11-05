#include <stdint.h>
#include <cmath>
#include "ap_axi_sdata.h"
#include "hls_stream.h"

#define R_Weight 0.299
#define G_Weight 0.587
#define B_Weight 0.114
#define Sobel_Size 3
#define Image_Vertical 77
#define Image_Horizontal 102

// Invert and grayscale image matrix
void Sobel(hls::stream< ap_axiu<1024,2,5,6>> &Data_In, hls::stream<ap_axiu<1024,2,5,6>> &Data_Out){
	// Define input and output as AXI stream interfaces
	#pragma HLS INTERFACE axis port=Data_In
	#pragma HLS INTERFACE axis port=Data_Out
	#pragma hls interface s_axilite port=return

	// Working temp
	ap_axiu<1024,2,5,6> tmp;
	
	// Working variables
	volatile int R = 0;
	volatile int G = 0;
	volatile int B = 0;
	
	// Matrices
	volatile int Vertical_Sobel[Sobel_Size][Sobel_Size] = {{-1,-2,-1},{0,0,0},{1,2,1}};
	volatile int Horizontal_Sobel[Sobel_Size][Sobel_Size] = {{-1,0,1},{-2,0,2},{-1,0,1}};
	volatile int Image[Image_Vertical][Image_Horizontal];
	volatile int Sobel[Image_Vertical][Image_Horizontal];
	
	//Counts
	volatile int Vertical_Count = 0;
	volatile int Horizontal_Count = 0;
	
	// Working temps
	volatile int G1[3];
	volatile int G2[3];
	volatile int G1_Sum = 0;
	volatile int G2_Sum = 0;



	while(1){
		// Read 1024 bits
		tmp = Data_In.read();
		

		// The first 8 bits are R, then G, then B. But that is only 24 bits.

		R = (tmp.data.to_int() & 0xff0000) >> 16;
		G = (tmp.data.to_int() & 0x00ff00) >> 8;
		B = (tmp.data.to_int() & 0x0000ff);
		
		// Grayscale
		tmp.data = R_Weight * R + G_Weight * G + B_Weight * B;
		
		//Insert into matrix
		Image[Vertical_Count][Horizontal_Count] = tmp.data.to_int();
		
		if(Vertical_Count == 0 or Vertical_Count == Image_Vertical-1 or Horizontal_Count == 0 or Horizontal_Count == Image_Horizontal-1){
			Sobel[Vertical_Count][Horizontal_Count] = 0;
		}

		if(Horizontal_Count == Image_Horizontal-1){
			Horizontal_Count = 0;
			Vertical_Count++;
		}
		else{
			Horizontal_Count++;
		}
		
		// Invert
		//tmp.data = 255-tmp.data;

		// Write inverted image
		//Data_Out.write(tmp);

		if(tmp.last){
			break;
		}

	}
	
	// Now work with matrix
	for(int i = 0; i < Image_Vertical; i++){
		for(int j=0; j < Image_Horizontal; j++){
			if(i == 0 or i == Image_Vertical-1 or j == 0 or j == Image_Horizontal-1){
				tmp.data = Sobel[i][j];
			}
			else{
				G1[0] = Vertical_Sobel[0][0]*Image[i-1][j-1] + Vertical_Sobel[0][1]*Image[i-1][j] + Vertical_Sobel[0][2]*Image[i-1][j+1];
				//G1[1] = Vertical_Sobel[1][0]*Image[i][j-1] + Vertical_Sobel[1][1]*Image[i][j] + Vertical_Sobel[1][2]*Image[i][j+1];
				G1[1] = 0;
				G1[2] = Vertical_Sobel[2][0]*Image[i+1][j-1] + Vertical_Sobel[2][1]*Image[i+1][j] + Vertical_Sobel[2][2]*Image[i+1][j+1];
				G1_Sum = G1[0]+G1[1]+G1[2];

				G2[0] = Horizontal_Sobel[0][0]*Image[i-1][j-1] + Horizontal_Sobel[0][1]*Image[i-1][j] + Horizontal_Sobel[0][2]*Image[i-1][j+1];
				G2[1] = Horizontal_Sobel[1][0]*Image[i][j-1] + Horizontal_Sobel[1][1]*Image[i][j] + Horizontal_Sobel[1][2]*Image[i][j+1];
				G2[2] = Horizontal_Sobel[2][0]*Image[i+1][j-1] + Horizontal_Sobel[2][1]*Image[i+1][j] + Horizontal_Sobel[2][2]*Image[i+1][j+1];
				G2_Sum = G2[0]+G2[1]+G2[2];

				Sobel[i][j] = (int)(std::sqrt(G1_Sum*G1_Sum+G2_Sum*G2_Sum)/4);
				tmp.data = Sobel[i][j];
			}
			Data_Out.write(tmp);
		}
	}
}
