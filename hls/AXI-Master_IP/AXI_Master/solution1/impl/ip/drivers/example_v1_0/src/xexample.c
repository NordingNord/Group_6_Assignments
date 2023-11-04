// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xexample.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XExample_CfgInitialize(XExample *InstancePtr, XExample_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XExample_Start(XExample *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XExample_ReadReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_AP_CTRL) & 0x80;
    XExample_WriteReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XExample_IsDone(XExample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XExample_ReadReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XExample_IsIdle(XExample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XExample_ReadReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XExample_IsReady(XExample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XExample_ReadReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XExample_EnableAutoRestart(XExample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XExample_WriteReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XExample_DisableAutoRestart(XExample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XExample_WriteReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_AP_CTRL, 0);
}

void XExample_Set_a(XExample *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XExample_WriteReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_A_DATA, (u32)(Data));
    XExample_WriteReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_A_DATA + 4, (u32)(Data >> 32));
}

u64 XExample_Get_a(XExample *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XExample_ReadReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_A_DATA);
    Data += (u64)XExample_ReadReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_A_DATA + 4) << 32;
    return Data;
}

void XExample_Set_value_r(XExample *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XExample_WriteReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_VALUE_R_DATA, Data);
}

u32 XExample_Get_value_r(XExample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XExample_ReadReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_VALUE_R_DATA);
    return Data;
}

void XExample_InterruptGlobalEnable(XExample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XExample_WriteReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_GIE, 1);
}

void XExample_InterruptGlobalDisable(XExample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XExample_WriteReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_GIE, 0);
}

void XExample_InterruptEnable(XExample *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XExample_ReadReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_IER);
    XExample_WriteReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_IER, Register | Mask);
}

void XExample_InterruptDisable(XExample *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XExample_ReadReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_IER);
    XExample_WriteReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_IER, Register & (~Mask));
}

void XExample_InterruptClear(XExample *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XExample_WriteReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_ISR, Mask);
}

u32 XExample_InterruptGetEnabled(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XExample_ReadReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_IER);
}

u32 XExample_InterruptGetStatus(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XExample_ReadReg(InstancePtr->Control_BaseAddress, XEXAMPLE_CONTROL_ADDR_ISR);
}

