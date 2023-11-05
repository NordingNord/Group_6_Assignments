
/******************************************************************************
 * Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
 * SPDX-License-Identifier: MIT
 ******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file xaxidma_example_simple_poll.c
 *
 * This file demonstrates how to use the xaxidma driver on the Xilinx AXI
 * DMA core (AXIDMA) to transfer packets in polling mode when the AXI DMA core
 * is configured in simple mode.
 *
 * This code assumes a loopback hardware widget is connected to the AXI DMA
 * core for data packet loopback.
 *
 * To see the debug print, you need a Uart16550 or uartlite in your system,
 * and please set "-DDEBUG" in your compiler options. You need to rebuild your
 * software executable.
 *
 * Make sure that MEMORY_BASE is defined properly as per the HW system. The
 * h/w system built in Area mode has a maximum DDR memory limit of 64MB. In
 * throughput mode, it is 512MB.  These limits are need to ensured for
 * proper operation of this code.
 *
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- ---- -------- -------------------------------------------------------
 * 4.00a rkv  02/22/11 New example created for simple DMA, this example is for
 *       	       simple DMA
 * 5.00a srt  03/06/12 Added Flushing and Invalidation of Caches to fix CRs
 *		       648103, 648701.
 *		       Added V7 DDR Base Address to fix CR 649405.
 * 6.00a srt  03/27/12 Changed API calls to support MCDMA driver.
 * 7.00a srt  06/18/12 API calls are reverted back for backward compatibility.
 * 7.01a srt  11/02/12 Buffer sizes (Tx and Rx) are modified to meet maximum
 *		       DDR memory limit of the h/w system built with Area mode
 * 7.02a srt  03/01/13 Updated DDR base address for IPI designs (CR 703656).
 * 9.1   adk  01/07/16 Updated DDR base address for Ultrascale (CR 799532) and
 *		       removed the defines for S6/V6.
 * 9.3   ms   01/23/17 Modified xil_printf statement in main function to
 *                     ensure that "Successfully ran" and "Failed" strings are
 *                     available in all examples. This is a fix for CR-965028.
 *       ms   04/05/17 Modified Comment lines in functions to
 *                     recognize it as documentation block for doxygen
 *                     generation of examples.
 * 9.9   rsp  01/21/19 Fix use of #elif check in deriving DDR_BASE_ADDR.
 * 9.10  rsp  09/17/19 Fix cache maintenance ops for source and dest buffer.
 * </pre>
 *
 * ***************************************************************************

 */
/***************************** Include Files *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xaxidma.h"
#include "xparameters.h"
#include "xdebug.h"
#include "xinvert.h"

#if defined(XPAR_UARTNS550_0_BASEADDR)
#include "xuartns550_l.h"       /* to use uartns550 */
#endif

/******************** Constant Definitions **********************************/

/*
 * Device hardware build related constants.
 */

#define DMA_DEV_ID		XPAR_AXIDMA_0_DEVICE_ID
#define INVERT_DEV_ID	XPAR_XINVERT_0_DEVICE_ID

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

#define TX_BUFFER_BASE		(MEM_BASE_ADDR + 0x00100000)
#define RX_BUFFER_BASE		(MEM_BASE_ADDR + 0x00300000)
#define RX_BUFFER_HIGH		(MEM_BASE_ADDR + 0x004FFFFF)

#define MAX_PKT_LEN		60

#define TEST_START_VALUE	0x00

#define NUMBER_OF_TRANSFERS	1

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

#if (!defined(DEBUG))
extern void xil_printf(const char *format, ...);
#endif

int XAxiDma_SimplePollExample(u16 DMADeviceId, u16 InvertDeviceId);
static int CheckData(void);

/************************** Variable Definitions *****************************/
/*
 * Device instance definitions
 */
XAxiDma AxiDma;
XInvert InvertInstance;


/*****************************************************************************/
/**
 * The entry point for this example. It invokes the example function,
 * and reports the execution status.
 *
 * @param	None.
 *
 * @return
 *		- XST_SUCCESS if example finishes successfully
 *		- XST_FAILURE if example fails.
 *
 * @note		None.
 *
 ******************************************************************************/
int main()
{
	int Status;

	xil_printf("\r\n--- Entering main() --- \r\n");

	/* Run the poll example for simple transfer */
	Status = XAxiDma_SimplePollExample(DMA_DEV_ID, INVERT_DEV_ID);

	if (Status != XST_SUCCESS) {
		xil_printf("\r\n--- XAxiDma_SimplePoll Example Failed ---\r\n");
		return XST_FAILURE;
	}

	xil_printf("Successfully ran XAxiDma_SimplePoll Example\r\n");

	xil_printf("--- Exiting main() --- \r\n");

	return XST_SUCCESS;

}


/*****************************************************************************/
/**
 * The example to do the simple transfer through polling. The constant
 * NUMBER_OF_TRANSFERS defines how many times a simple transfer is repeated.
 *
 * @param	DeviceId is the Device Id of the XAxiDma instance
 *
 * @return
 *		- XST_SUCCESS if example finishes successfully
 *		- XST_FAILURE if error occurs
 *
 * @note		None
 *
 *
 ******************************************************************************/
int XAxiDma_SimplePollExample(u16 DMADeviceId, u16 InvertDeviceId)
{
	XAxiDma_Config *AXICfgPtr;
	XInvert_Config *InvertCfgPrt;
	int Status;
	int Tries = NUMBER_OF_TRANSFERS;
	int Index;
	u8 *TxBufferPtr;
	u8 *RxBufferPtr;

	TxBufferPtr = (u8 *)TX_BUFFER_BASE;
	RxBufferPtr = (u8 *)RX_BUFFER_BASE;

	/* Initialize the XAxiDma device.
	 */
	xil_printf("Initializing DMA");
	AXICfgPtr = XAxiDma_LookupConfig(DMADeviceId);
	if (!AXICfgPtr) {
		xil_printf("No config found for %d\r\n", DMADeviceId);
		return XST_FAILURE;
	}

	Status = XAxiDma_CfgInitialize(&AxiDma, AXICfgPtr);
	if (Status != XST_SUCCESS) {
		xil_printf("Initialization failed %d\r\n", Status);
		return XST_FAILURE;
	}

	if(XAxiDma_HasSg(&AxiDma)){
		xil_printf("Device configured as SG mode \r\n");
		return XST_FAILURE;
	}
	xil_printf("\r\n--- DMA Intialized --- \r\n");

	/* Initialize the XInvert device
	 */
	xil_printf("Initializing Invert");
	InvertCfgPrt = XInvert_LookupConfig(InvertDeviceId);
	if (!InvertCfgPrt) {
		xil_printf("No config found for %d\r\n", InvertDeviceId);
		return XST_FAILURE;
	}

	Status = XInvert_CfgInitialize(&InvertInstance, InvertCfgPrt);
	if (Status != XST_SUCCESS) {
		xil_printf("Initialization failed %d\r\n", Status);
		return XST_FAILURE;
	}
	xil_printf("\r\n--- Invert Intialized --- \r\n");

	/* Disable interrupts, we use polling mode
	 */
	XAxiDma_IntrDisable(&AxiDma, XAXIDMA_IRQ_ALL_MASK,
			XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(&AxiDma, XAXIDMA_IRQ_ALL_MASK,
			XAXIDMA_DMA_TO_DEVICE);

	// Read data
	FILE* ptr;
	char str[10];
	char *Cptr;
	u32 Val;
	u8 Val_tmp;
	ptr = fopen("RGB_array.txt","a+");

	if(NULL == ptr){
		xil_printf("File cant be opened \n");
	}
	Index = 0;
	while(fgets(str,10,ptr) != NULL){
		Val = strtoul(str,&Cptr,10);
		Val_tmp = Val & 0x000000ff;
		xil_printf("Send data: %u  \r\n", Val_tmp);
		TxBufferPtr[Index] = Val_tmp;
		Index++;
		Val_tmp = Val & 0x0000ff00 >> 8;
		xil_printf("Send data: %u  \r\n", Val_tmp);
		TxBufferPtr[Index] = Val_tmp;
		Index++;
		Val_tmp = Val & 0x00ff0000 >> 16;
		xil_printf("Send data: %u  \r\n", Val_tmp);
		TxBufferPtr[Index] = Val_tmp;
		Index++;
		Val_tmp = Val & 0xff000000 >> 24;
		xil_printf("Send data: %u  \r\n", Val_tmp);
		TxBufferPtr[Index] = Val_tmp;
		Index++;
	}
	fclose(ptr);


	//Value = TEST_START_VALUE;

	//for(Index = 0; Index < MAX_PKT_LEN; Index ++) {
	//	Value = (u8)(Index/3);
	//	xil_printf("Send data: %u  \r\n", Value);
	//	TxBufferPtr[Index] = Value;
		//xil_printf("Send data: %d = %d \r\n", Index, TxBufferPtr[Index]);

		//Value = (Value + 1) & 0xFF;
	//}
	xil_printf("\r\n--- Disabled interrupts and initialized TxBufferPtr --- \r\n");
	/* Flush the buffers before the DMA transfer, in case the Data Cache
	 * is enabled
	 */
	Xil_DCacheFlushRange((UINTPTR)TxBufferPtr, MAX_PKT_LEN);
	Xil_DCacheFlushRange((UINTPTR)RxBufferPtr, MAX_PKT_LEN/3);
	xil_printf("\r\n--- Flushed buffers --- \r\n");

	for(Index = 0; Index < Tries; Index ++) {
		xil_printf("\r\n--- Trying %d --- \r\n",Index);

		XInvert_Start(&InvertInstance);
		xil_printf("\r\n--- Started Invert --- \r\n");

		while (XInvert_IsReady(&InvertInstance)) {
			/* Wait */
		}
		xil_printf("\r\n--- Invert Ready --- \r\n");

		Status = XAxiDma_SimpleTransfer(&AxiDma,(UINTPTR) TxBufferPtr,
				MAX_PKT_LEN, XAXIDMA_DMA_TO_DEVICE);

		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}
		else {
			xil_printf("\r\n--- XAxiDma_SimpleTransfer TxBufferPtr Success --- \r\n");
		}

		while (XAxiDma_Busy(&AxiDma,XAXIDMA_DMA_TO_DEVICE)) {
			/* Wait */
		}
		xil_printf("\r\n--- DMA_TO_DEVICE done --- \r\n");

		while (XInvert_IsDone(&InvertInstance)) {
			/* Wait */
		}
		xil_printf("\r\n--- Invert Done --- \r\n");

		Status = XAxiDma_SimpleTransfer(&AxiDma,(UINTPTR) RxBufferPtr,
				MAX_PKT_LEN/3, XAXIDMA_DEVICE_TO_DMA);

		if (Status != XST_SUCCESS) {
			return XST_FAILURE;
		}
		else {
			xil_printf("\r\n--- XAxiDma_SimpleTransfer RxBufferPtr Success --- \r\n");
		}

		while (XAxiDma_Busy(&AxiDma,XAXIDMA_DEVICE_TO_DMA)) {
			xil_printf("\r\n--- IM STUCK. HELP --- \r\n");
		}
		xil_printf("\r\n--- DEVICE_TO_DMA done --- \r\n");

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



/*****************************************************************************/
/*
 *
 * This function checks data buffer after the DMA transfer is finished.
 *
 * @param	None
 *
 * @return
 *		- XST_SUCCESS if validation is successful.
 *		- XST_FAILURE otherwise.
 *
 * @note		None.
 *
 ******************************************************************************/
static int CheckData(void)
{
	// Read data again
	// Read data
	FILE* ptr2;
	char str[10];
	char *Cptr;
	u32 Val;
	u8 R;
	u8 G;
	u8 B;
	u8 Old_R;
	u8 Old_G;
	u8 Result_Buffer[480000];
	int Gray_Count = 0;
	int Inv_Count = 0;
	float R_Weight = 0.299;
	float G_Weight = 0.587;
	float B_Weight = 0.114;
	ptr2 = fopen("src\RGB_array.txt","a+");

	if(NULL == ptr2){
		xil_printf("File cant be opened \n");
	}

	while(fgets(str,10,ptr2) != NULL){
		Val = strtoul(str,&Cptr,10);
		// Grayscale and invert
		if(Gray_Count == 0){
			// The first 8 bits are R, then G, then B. But that is only 24 bits.
			R = Val & 0x000000ff;
			G = Val & 0x0000ff00 >> 8;
			B = Val & 0x00ff0000 >> 16;
			Old_R = Val & 0xff000000 >> 24;
			Gray_Count++;
			//Grayscale and invert
			Result_Buffer[Inv_Count] = 255-(R_Weight * R + G_Weight * G + B_Weight * B);
			Inv_Count++;
		}
		else if(Gray_Count == 1){
			R = Old_R;
			G = Val & 0x000000ff;
			B = Val & 0x0000ff00 >> 8;
			Old_R = Val & 0x00ff0000 >> 16;
			Old_G =  Val & 0xff000000 >> 24;
			Gray_Count ++;
			//Grayscale and invert
			Result_Buffer[Inv_Count] = 255-(R_Weight * R + G_Weight * G + B_Weight * B);
			Inv_Count++;
		}
		else if(Gray_Count == 2){
			R = Old_R;
			G = Old_G;
			B = Val & 0x000000ff;
			//Grayscale and invert
			Result_Buffer[Inv_Count]  = 255-(R_Weight * R + G_Weight * G + B_Weight * B);
			Inv_Count++;

			R =  Val & 0x0000ff00 >> 8;
			G = Val & 0x00ff0000 >> 16;
			B =  Val & 0xff000000 >> 24;
			Result_Buffer[Inv_Count] = 255-(R_Weight * R + G_Weight * G + B_Weight * B);
			Gray_Count = 0;
			Inv_Count++;
		}
	}
	fclose(ptr2);


	// Test

	u8 *RxPacket;
	int Index = 0;
	u8 Value = 0;

	//u32 IndexValue = 0;

	RxPacket = (u8 *) RX_BUFFER_BASE;

	//xil_printf("Grayscale: %u", (u8)(R_Weight* TEST_START_VALUE+ G_Weight*TEST_START_VALUE + B_Weight*TEST_START_VALUE));


	/* Invalidate the DestBuffer before receiving the data, in case the
	 * Data Cache is enabled
	 */
	Xil_DCacheInvalidateRange((UINTPTR)RxPacket, MAX_PKT_LEN/3);

	// Open file
	FILE *fptr;
	fptr = fopen("Results_Bare.txt","w");


	//int tempIndex = 0;
	for(Index = 0; Index < 480000; Index ++) {

		xil_printf("Received: %u \r\n",(u8)RxPacket[Index]);
		fprintf(fptr,"%u",(u8)RxPacket[Index]);

		if (RxPacket[Index] != Result_Buffer[Index]) {
			xil_printf("Data %u: %u/%u --Error\r\n",
					Index, (u8)RxPacket[Index],
					Value);
			return XST_FAILURE;
		}
		else {
			xil_printf("Data %u: %u/%u\r\n",
					Index, (u8)RxPacket[Index],
					Value);
		}
		//tempIndex = (tempIndex + 1) % 4;
	}
	fclose(fptr);

	return XST_SUCCESS;
}

