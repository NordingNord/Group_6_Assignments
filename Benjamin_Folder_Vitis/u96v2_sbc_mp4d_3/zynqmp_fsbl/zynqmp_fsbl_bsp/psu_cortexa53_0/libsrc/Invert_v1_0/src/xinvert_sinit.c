// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xinvert.h"

extern XInvert_Config XInvert_ConfigTable[];

XInvert_Config *XInvert_LookupConfig(u16 DeviceId) {
	XInvert_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XINVERT_NUM_INSTANCES; Index++) {
		if (XInvert_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XInvert_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XInvert_Initialize(XInvert *InstancePtr, u16 DeviceId) {
	XInvert_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XInvert_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XInvert_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

