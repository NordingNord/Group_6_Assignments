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

void Invert(hls::stream< ap_axis<64,2,5,6>> &Image_In[Width_Size][Height_Size][RGB], hls::stream< ap_axis<64,2,5,6>> &Image_Out[Width_Size][Height_Size]);

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Initialize input arrays and expected output array
    hls::stream< ap_axis<64,2,5,6>> & Image_In[Width_Size][Height_Size][RGB];
    volatile int Expected_Out[Width_Size][Height_Size];
    hls::stream< ap_axis<64,2,5,6>> & Image_Out[Width_Size][Height_Size];
    hls::stream< ap_axis<64,2,5,6>> & Image_Gray[Width_Size][Height_Size];

    // Populate input arrays with random data
    for(int i = 0; i < Height_Size; i++){
    	for(int j = 0; j < Width_Size; j++){
    		for(int k = 0; k < RGB; k++){
    			// Generate image
        		Image_In[j][i][k] = std::rand() % 255+1;
    		}
    		// Make expected output
    		Image_Gray[j][i] = R_Weight * Image_In[j][i][0] + G_Weight * Image_In[j][i][1] + B_Weight * Image_In[j][i][2];
    		Expected_Out[j][i] = 255-Image_Gray[j][i];
    	}
    }

    // Call the invert function
    Invert(Image_In, Image_Out);

    // Check the results
    bool success = true;

    for(int i = 0; i < Height_Size; i++){
    	for(int j = 0; j < Width_Size; j++){
    		if (Image_Out[j][i] != Expected_Out[j][i]){
    			std::cout << "Mismatch at index " << j << "," << i << ": Expected " << Expected_Out[j][i] << ", Actual " << Image_Out[j][i] << std::endl;
    			success = false;
    		}
    	}
    }

    if (success) {
        std::cout << "Test passed!" << std::endl;
    } else {
        std::cout << "Test failed!" << std::endl;
    }

	while(1)
		;
    return 0;
}
