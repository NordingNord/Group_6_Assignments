#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include "ap_axi_sdata.h"
#include "hls_stream.h"

#define R_Weight 0.299
#define G_Weight 0.587
#define B_Weight 0.114
#define Image_Height 600
#define Image_Width 800

void Invert(hls::stream< ap_axiu<32,2,5,6>> &Image_In, hls::stream< ap_axiu<32,2,5,6>> &Image_Out);

int main() {

	hls::stream<ap_axiu<32,2,5,6>> A,B;
	ap_axiu<32,2,5,6> tmp1,tmp2;

	volatile int Inverted_Data[Image_Height*Image_Width];
	volatile int Output_Data[Image_Height*Image_Width];
	volatile int RT = 0;
	volatile int GT = 0;
	volatile int BT = 0;
	volatile int Old_RT = 0;
	volatile int Old_GT = 0;
	volatile int Image[Image_Height*Image_Width];
	
	// Read test file
	std::string Test_Data;
	std::ifstream Test_File("RGB_array.txt");

	// Image count
	volatile int Image_Count = 0;

	// Get test data
	while(std::getline(Test_File, Test_Data)){
		Image[Image_Count] = std::stoul(Test_Data);
		Image_Count++;
	}
	Test_File.close();

	// Number of packages
	volatile int Package_Num = Image_Count;

	// Grayscale Count
	volatile int Gray_Count = 0;

	// Inverse count
	volatile int Inv_Count = 0;

	// Create stream format and send
	for(int j=0; j < Package_Num; j++){
		tmp1.data = Image[j];
		tmp1.keep = -1;
		tmp1.strb = 1;
		tmp1.user = 1;
		if(j == Package_Num-1){
			tmp1.last = 1;
		}
		else{
			tmp1.last = 0;
		}

		A.write(tmp1);

		// Grayscale and invert
		if(Gray_Count == 0){
			// The first 8 bits are R, then G, then B. But that is only 24 bits.
			RT = (tmp1.data.to_int() & 0x000000ff);
			GT = (tmp1.data.to_int() & 0x0000ff00) >> 8;
			BT = (tmp1.data.to_int() & 0x00ff0000) >> 16;
			Old_RT = (tmp1.data.to_int() & 0xff000000) >> 24;
			Gray_Count++;
			//Grayscale and invert
			Inverted_Data[Inv_Count] = 255-(R_Weight * RT + G_Weight * GT + B_Weight * BT);
			Inv_Count++;
		}
		else if(Gray_Count == 1){
			RT = Old_RT;
			GT = (tmp1.data.to_int() & 0x000000ff);
			BT = (tmp1.data.to_int() & 0x0000ff00) >> 8;
			Old_RT = (tmp1.data.to_int() & 0x00ff0000) >> 16;
			Old_GT = (tmp1.data.to_int() & 0xff000000) >> 24;
			Gray_Count ++;
			//Grayscale and invert
			Inverted_Data[Inv_Count] = 255-(R_Weight * RT + G_Weight * GT + B_Weight * BT);
			Inv_Count++;
		}
		else if(Gray_Count == 2){
			RT = Old_RT;
			GT = Old_GT;
			BT = (tmp1.data.to_int() & 0x000000ff);
			//Grayscale and invert
			Inverted_Data[Inv_Count]  = 255-(R_Weight * RT + G_Weight * GT + B_Weight * BT);
			Inv_Count++;

			RT = (tmp1.data.to_int() & 0x0000ff00) >> 8;
			GT = (tmp1.data.to_int() & 0x00ff0000) >> 16;
			BT = (tmp1.data.to_int() & 0xff000000) >> 24;
			Inverted_Data[Inv_Count] = 255-(R_Weight * RT + G_Weight * GT + B_Weight * BT);
			Gray_Count = 0;
			Inv_Count++;
		}
	}

	Invert(A,B);

	// Load all result data
	volatile int Insert_Count = 0;
	for(int i=0;i < (Image_Height*Image_Width)/4; i++){
		B.read(tmp2);
		Output_Data[Insert_Count] = (tmp2.data.to_int() & 0x000000ff);
		Insert_Count++;
		Output_Data[Insert_Count] = ((tmp2.data.to_int() & 0x0000ff00) >> 8);
		Insert_Count++;
		Output_Data[Insert_Count] = ((tmp2.data.to_int() & 0x00ff0000) >> 16);
		Insert_Count++;
		Output_Data[Insert_Count] = ((tmp2.data.to_int() & 0xff000000) >> 24);
		Insert_Count++;
		if(tmp2.last){
			break;
		}
	}
	
	// print output
	//for(int i = 0; i < Image_Height*Image_Width; i++){
	//	if(i % Image_Width == 0){
	//		std::cout << Output_Data[i] <<"]" << std::endl;
	//	}
	//	else if(i % Image_Height == 0){
	//		std::cout << "[" << Output_Data[i] <<",";
	//	}
	//	else{
	//		std::cout << Output_Data[i] <<",";
	//	}
	//}

	// Test
	volatile int Error = 0;
	for(int i = 0; i < Image_Height*Image_Width; i++){
		if(Output_Data[i] != Inverted_Data[i]){
			std::cout << "ERROR at index: " << i << std::endl;
			std::cout << "Expected: " << Inverted_Data[i] << std::endl;
			std::cout << "Got: " << Output_Data[i] << std::endl;
			Error = 1;
		}
	}
	if(Error == 0){
	    std::cout << "Success: results match" << std::endl;
	}

	// Write to file
	std::ofstream Result_File("Results.txt");
	for(int i = 0; i < Image_Height*Image_Width; i++){
		Result_File << Output_Data[i] << "\n";
	}
	Result_File.close();
}
