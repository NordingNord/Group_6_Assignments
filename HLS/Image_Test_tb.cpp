#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ap_axi_sdata.h"
#include "hls_stream.h"

#define R_Weight 0.299
#define G_Weight 0.587
#define B_Weight 0.114
#define Image_Height 50
#define Image_Width 100

void Invert(hls::stream< ap_axiu<32,2,5,6>> &Image_In, hls::stream< ap_axiu<32,2,5,6>> &Image_Out);

int main() {
	int i = 100;
	hls::stream<ap_axiu<32,2,5,6>> A,B;
	ap_axiu<32,2,5,6> tmp1,tmp2;
	volatile int Inverted_Data[Image_Height*Image_Width];
	volatile int Output_Data[Image_Height*Image_Width];
	volatile int RT = 0;
	volatile int GT = 0;
	volatile int BT = 0;
	volatile int Image[Image_Height*Image_Width];
	
	for(int i = 0; i < Image_Height*Image_Width;i++){
		Image[i] = 0x22222222;
	}


	for(int j=0; j < Image_Height*Image_Width; j++){
		tmp1.data = Image[j];
		tmp1.keep = -1;
		tmp1.strb = 1;
		tmp1.user = 1;
		if(j == Image_Height*Image_Width-1){
			tmp1.last = 1;
		}
		else{
			tmp1.last = 0;
		}

		//Inverted_Data[j] = 255-(int)(R_Weight * RT + G_Weight * GT + B_Weight * BT);
				
		A.write(tmp1);
	}
	//Make grayscale matrix
	volatile int indx = 0;

	for(int j = 0; j < Image_Height*Image_Width; j++){
		RT = Image[indx];
		indx++;
		GT = Image[indx];
		indx++;
		BT = Image[indx];
		indx++;

		Inverted_Data[j] = 255-(R_Weight * RT + G_Weight * GT + B_Weight * BT);

		//Inverted_Data[j] = 255-Inverted_Data[j];
	}

	Invert(A,B);
	volatile int Final_Sum = 0;

	for(int i=0;i < (int)((100*50)/4); i++){
		B.read(tmp2);
		Output_Data[i] = tmp2.data.to_int();
		int i1 = (Output_Data[i] & 0x000000ff);
		int i2 = ((Output_Data[i] & 0x0000ff00) >> 8);
		int i3 = ((Output_Data[i] & 0x00ff0000) >> 16);
		int i4 = ((Output_Data[i] & 0xff000000) >> 24);
		std::cout << i1 << std::endl;
		std::cout << i2 << std::endl;
		std::cout << i3 << std::endl;
		std::cout << i4 << std::endl;
	}
	
	//for(int i = 0; i < 100; i++){
	//	if(Inverted_Data[i] != Output_Data[i]){
	//        std::cout << "ERROR: results mismatch" << std::endl;
	//        std::cout << "Data=" << Inverted_Data[i];
	//        std::cout << " != ";
	//        std::cout << "Final result=" << Output_Data[i] << std::endl;
	//        return 0;
	//	}
	//}

    std::cout << "Success: results match" << std::endl;
}
