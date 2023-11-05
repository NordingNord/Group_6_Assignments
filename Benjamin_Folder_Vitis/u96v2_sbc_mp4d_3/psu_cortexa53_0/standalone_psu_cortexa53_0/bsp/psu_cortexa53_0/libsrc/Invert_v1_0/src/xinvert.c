// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xinvert.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XInvert_CfgInitialize(XInvert *InstancePtr, XInvert_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XInvert_Start(XInvert *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XInvert_ReadReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_AP_CTRL) & 0x80;
    XInvert_WriteReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XInvert_IsDone(XInvert *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XInvert_ReadReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XInvert_IsIdle(XInvert *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XInvert_ReadReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XInvert_IsReady(XInvert *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XInvert_ReadReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XInvert_EnableAutoRestart(XInvert *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XInvert_WriteReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XInvert_DisableAutoRestart(XInvert *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XInvert_WriteReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_AP_CTRL, 0);
}

void XInvert_InterruptGlobalEnable(XInvert *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XInvert_WriteReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_GIE, 1);
}

void XInvert_InterruptGlobalDisable(XInvert *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XInvert_WriteReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_GIE, 0);
}

void XInvert_InterruptEnable(XInvert *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XInvert_ReadReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_IER);
    XInvert_WriteReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_IER, Register | Mask);
}

void XInvert_InterruptDisable(XInvert *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XInvert_ReadReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_IER);
    XInvert_WriteReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_IER, Register & (~Mask));
}

void XInvert_InterruptClear(XInvert *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XInvert_WriteReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_ISR, Mask);
}

u32 XInvert_InterruptGetEnabled(XInvert *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XInvert_ReadReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_IER);
}

u32 XInvert_InterruptGetStatus(XInvert *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XInvert_ReadReg(InstancePtr->Control_BaseAddress, XINVERT_CONTROL_ADDR_ISR);
}

