/*
 * Copyright 2021 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * This file contains an example for creating an AXI4-master interface in Vivado HLS
 */

#include <stdio.h>
#include <string.h>
static const int length = 600*800;
static const int segments = 4;
static const int segmentSize = length/segments;
void example(volatile int *a, int value){
#pragma HLS INTERFACE m_axi port=a depth=segmentSize offset=slave max_widen_bitwidth=1024
	// Above line based on https://docs.xilinx.com/r/2020.2-English/ug1399-vitis-hls/Automatic-Port-Width-Resizing
#pragma HLS INTERFACE s_axilite port=value
#pragma HLS INTERFACE s_axilite port=return

	int i,seg;
	int buff[segmentSize];

	for(seg=0; seg < segments; seg++){
		//memcpy creates a burst access to memory
		//multiple calls of memcpy cannot be pipelined and will be scheduled sequentially
		//memcpy requires a local buffer to store the results of the memory transaction
		memcpy(buff,(const int*)a+seg*segmentSize,segmentSize*sizeof(int));

		for(i=0; i < segmentSize; i++){
#pragma HLS pipeline II=1
			// Above line based on https://docs.xilinx.com/r/2020.2-English/ug1399-vitis-hls/pragma-HLS-pipeline
			buff[i] = buff[i] + value;
		}

		memcpy((int *)a+seg*segmentSize,buff,segmentSize*sizeof(int));

	}
}


