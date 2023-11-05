/******************************************************************************
 *
 * Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Use of the Software is limited solely to applications:
 * (a) running on a Xilinx device, or
 * (b) that interact with a Xilinx device through a bus or interconnect.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the Xilinx shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in
 * this Software without prior written authorization from Xilinx.
 *
 ******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

// Include files
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xexample.h"

// Constant definitions
#define AXIMasterIP_ID		XPAR_XEXAMPLE_0_DEVICE_ID

#ifdef XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#define DDR_BASE_ADDR		XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#elif defined (XPAR_MIG7SERIES_0_BASEADDR)
#define DDR_BASE_ADDR	XPAR_MIG7SERIES_0_BASEADDR
#elif defined (XPAR_MIG_0_BASEADDR)
#define DDR_BASE_ADDR	XPAR_MIG_0_BASEADDR
#elif defined (XPAR_PSU_DDR_0_S_AXI_BASEADDR)
#define DDR_BASE_ADDR	XPAR_PSU_DDR_0_S_AXI_BASEADDR
#endif

#ifndef DDR_BASE_ADDR
#warning CHECK FOR THE VALID DDR ADDRESS IN XPARAMETERS.H, \
		DEFAULT SET TO 0x01000000
#define MEM_BASE_ADDR		0x01000000
#else
#define MEM_BASE_ADDR		(DDR_BASE_ADDR + 0x1000000)
#endif

#define AXIMASTERIP_TXRX_ADDR		(MEM_BASE_ADDR + 0x00100000)

#define MAX_PKT_LEN			600*800

#define TEST_START_VALUE	0x02
#define VALUE_TO_ADD		5

#define NUMBER_OF_TRANSFERS	10

// Function prototypes
int AXIMasterIP_Test(u16 AXIMasterIP_Instance_ID);
static int CheckData(void);

// Variable definitions
XExample AXIMasterIP_Instance;

// Main definition
int main()
{
	int Status;

	init_platform();

	xil_printf("\r\n--- Entering main() --- \r\n");

	Status = AXIMasterIP_Test(AXIMasterIP_ID);

	if (Status != XST_SUCCESS) {
		xil_printf("\r\n--- AXIMasterIP_Test Example Failed ---\r\n");
		cleanup_platform();
		return XST_FAILURE;
	}

	xil_printf("Successfully ran AXIMasterIP_Test Example\r\n");

	xil_printf("--- Exiting main() --- \r\n");

	cleanup_platform();

	return XST_SUCCESS;
}

// Test definition
int AXIMasterIP_Test(u16 AXIMasterIP_Instance_ID) {
	XExample_Config *AXIMasterIP_CfgPtr;
	int Status;
	int Tries = NUMBER_OF_TRANSFERS;
	int Index;
	u64 *AXIMASTERIP_TXRX_Ptr;
	u64 Value;

	AXIMASTERIP_TXRX_Ptr = (u64 *)AXIMASTERIP_TXRX_ADDR;

	/* Initialize the AXIMasterIP device
	 */
	xil_printf("Initializing AXIMASTERIP");
	AXIMasterIP_CfgPtr = XExample_LookupConfig(AXIMasterIP_Instance_ID);
	if (!AXIMasterIP_CfgPtr) {
		xil_printf("No config found for %d\r\n", AXIMasterIP_Instance_ID);
		return XST_FAILURE;
	}

	Status = XExample_CfgInitialize(&AXIMasterIP_Instance, AXIMasterIP_CfgPtr);
	if (Status != XST_SUCCESS) {
		xil_printf("Initialization failed %d\r\n", Status);
		return XST_FAILURE;
	}
	xil_printf("\r\n--- AXIMASTERIP Initialized --- \r\n");

	// Disable interrupts
	XExample_InterruptDisable(&AXIMasterIP_Instance, 0b11);

	Value = TEST_START_VALUE;

	for(Index = 0; Index < MAX_PKT_LEN; Index ++) {
		AXIMASTERIP_TXRX_Ptr[Index] = Value;
		//xil_printf("Send data: %d = %d \r\n", Index, AXIMASTERIP_TXRX_Ptr[Index]);

		Value = (Value + 1);
	}
	xil_printf("\r\n--- Initialized AXIMASTERIP_TXRX_Ptr --- \r\n");

	for(Index = 0; Index < Tries; Index++) {
		xil_printf("\r\n--- Trying %d --- \r\n",Index);

		while (!XExample_IsReady(&AXIMasterIP_Instance)) {
			/* Wait */
		}
		xil_printf("\r\n--- AXIMasterIP Ready --- \r\n");

		XExample_Set_a(&AXIMasterIP_Instance, (u64)AXIMASTERIP_TXRX_Ptr);
		xil_printf("\r\n--- Set a input address --- \r\n");

		XExample_Set_value_r(&AXIMasterIP_Instance, (u32)VALUE_TO_ADD);
		xil_printf("\r\n--- Set value to add--- \r\n");

		while (!XExample_IsReady(&AXIMasterIP_Instance)) {
			/* Wait */
		}
		xil_printf("\r\n--- AXIMasterIP Ready --- \r\n");

		XExample_Start(&AXIMasterIP_Instance);
		xil_printf("\r\n--- Started AXIMASTERIP --- \r\n",Index);

		xil_printf("\r\n--- Waiting for AXIMasterIP to actually start --- \r\n");
		while (XExample_IsReady(&AXIMasterIP_Instance)) {
			/* Wait */
		}
		xil_printf("\r\n--- AXIMasterIP has started --- \r\n");

		while (!XExample_IsIdle(&AXIMasterIP_Instance)) {
			/* Wait */
		}
		xil_printf("\r\n--- AXIMasterIP idle --- \r\n");

		while (!XExample_IsDone(&AXIMasterIP_Instance)) {
			/* Wait */
		}
		xil_printf("\r\n--- AXIMasterIP done --- \r\n");

		Status = CheckData();
		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}
		else {
			xil_printf("\r\n--- Success try --- \r\n");
		}
	}

	xil_printf("\r\n--- Exited test for loop --- \r\n");

	/* Test finishes successfully
	 */

	return XST_SUCCESS;
}

static int CheckData(void) {
	int Index;
	u64 *AXIMASTERIP_TXRX_Ptr;
	u64 Value;

	AXIMASTERIP_TXRX_Ptr = (u64 *)AXIMASTERIP_TXRX_ADDR;

	Value = TEST_START_VALUE;

	for(Index = 0; Index < MAX_PKT_LEN; Index ++) {
		if (AXIMASTERIP_TXRX_Ptr[Index] == (Value + VALUE_TO_ADD)) {
			//xil_printf("Data: %d = %d == %d \r\n", Index, AXIMASTERIP_TXRX_Ptr[Index], (Value + VALUE_TO_ADD));
		}
		else {
			xil_printf("Data: %d = %d == %d -- Error \r\n", Index, AXIMASTERIP_TXRX_Ptr[Index], (Value + VALUE_TO_ADD));
			return XST_FAILURE;
		}

		Value = (Value + 1);
	}
	return XST_SUCCESS;
}
