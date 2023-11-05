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

#include <stdio.h>

void example(volatile int *a, int value, bool done);

int main()
{
  int i;
  int length = 600*800;
  int A[length];
  int B[length];
  int value = 7;
  bool donner = false;


  printf("HLS AXI-Master example\n");
  //Put data into A
  for(i=0; i < length; i++){
    A[i] = i;
  }

  //Call the hardware function
  example(A, value, donner);

  //Run a software version of the hardware function to validate results
  for(i=0; i < length; i++){
    B[i] = i + value;
  }

  //Compare results
  for(i=0; i < length; i++){
    if(B[i] != A[i]){
      printf("i = %d A = %d B= %d\n",i,A[i],B[i]);
      printf("______ERROR HW and SW results mismatch_____\n");
      return 1;
    }
  }
  printf("!!!!!!!Success HW and SW results match!!!!!!!\n");
  return 0;
}



