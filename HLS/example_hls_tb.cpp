#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ap_axi_sdata.h"
#include "hls_stream.h"

#define Width_Size 1280
#define Height_Size 720
#define RGB 3
#define R_Weight 0.299
#define G_Weight 0.587
#define B_Weight 0.114

void Invert(hls::stream< ap_axis<32,2,5,6>> &Image_In, hls::stream< ap_axis<32,2,5,6>> &Image_Out);

int main() {
	int i = 100;
	hls::stream<ap_axis<32,2,5,6>> A,B;
	ap_axis<32,2,5,6> tmp1,tmp2;
	volatile int data_sum;

	for(int j=0; j < 100; j++){
		tmp1.data = j;
		tmp1.keep = -1;
		tmp1.strb = 1;
		tmp1.user = 1;
		if(j == 99){
			tmp1.last = 1;
		}
		else{
			tmp1.last = 0;
		}
		data_sum += tmp1.data.to_int();
		A.write(tmp1);
	}
	Invert(A,B);
	volatile int Final_Sum = 0;
	for(int i=0;i < 100; i++){
		B.read(tmp2);
		Final_Sum += tmp2.data.to_int();

	}

	if(data_sum+5*100 != Final_Sum){
        std::cout << "ERROR: results mismatch" << std::endl;
        std::cout << "Data_sum=" << data_sum;
        std::cout << " != ";
        std::cout << "Final sum=" << Final_Sum << std::endl;
        return 1;
	}
    std::cout << "Success: results match" << std::endl;
    return 0;
}
