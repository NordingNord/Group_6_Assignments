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

    InstancePtr->Axi_cpu_BaseAddress = ConfigPtr->Axi_cpu_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XExample_Start(XExample *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XExample_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_AP_CTRL) & 0x80;
    XExample_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_AP_CTRL, Data | 0x01);
}

u32 XExample_IsDone(XExample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XExample_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XExample_IsIdle(XExample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XExample_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XExample_IsReady(XExample *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XExample_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XExample_EnableAutoRestart(XExample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XExample_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_AP_CTRL, 0x80);
}

void XExample_DisableAutoRestart(XExample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XExample_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_AP_CTRL, 0);
}

u32 XExample_Get_in1_BaseAddress(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_IN1_BASE);
}

u32 XExample_Get_in1_HighAddress(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_IN1_HIGH);
}

u32 XExample_Get_in1_TotalBytes(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XEXAMPLE_AXI_CPU_ADDR_IN1_HIGH - XEXAMPLE_AXI_CPU_ADDR_IN1_BASE + 1);
}

u32 XExample_Get_in1_BitWidth(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEXAMPLE_AXI_CPU_WIDTH_IN1;
}

u32 XExample_Get_in1_Depth(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEXAMPLE_AXI_CPU_DEPTH_IN1;
}

u32 XExample_Write_in1_Words(XExample *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XEXAMPLE_AXI_CPU_ADDR_IN1_HIGH - XEXAMPLE_AXI_CPU_ADDR_IN1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_IN1_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XExample_Read_in1_Words(XExample *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XEXAMPLE_AXI_CPU_ADDR_IN1_HIGH - XEXAMPLE_AXI_CPU_ADDR_IN1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_IN1_BASE + (offset + i)*4);
    }
    return length;
}

u32 XExample_Write_in1_Bytes(XExample *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XEXAMPLE_AXI_CPU_ADDR_IN1_HIGH - XEXAMPLE_AXI_CPU_ADDR_IN1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_IN1_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XExample_Read_in1_Bytes(XExample *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XEXAMPLE_AXI_CPU_ADDR_IN1_HIGH - XEXAMPLE_AXI_CPU_ADDR_IN1_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_IN1_BASE + offset + i);
    }
    return length;
}

u32 XExample_Get_in2_BaseAddress(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_IN2_BASE);
}

u32 XExample_Get_in2_HighAddress(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_IN2_HIGH);
}

u32 XExample_Get_in2_TotalBytes(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XEXAMPLE_AXI_CPU_ADDR_IN2_HIGH - XEXAMPLE_AXI_CPU_ADDR_IN2_BASE + 1);
}

u32 XExample_Get_in2_BitWidth(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEXAMPLE_AXI_CPU_WIDTH_IN2;
}

u32 XExample_Get_in2_Depth(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEXAMPLE_AXI_CPU_DEPTH_IN2;
}

u32 XExample_Write_in2_Words(XExample *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XEXAMPLE_AXI_CPU_ADDR_IN2_HIGH - XEXAMPLE_AXI_CPU_ADDR_IN2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_IN2_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XExample_Read_in2_Words(XExample *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XEXAMPLE_AXI_CPU_ADDR_IN2_HIGH - XEXAMPLE_AXI_CPU_ADDR_IN2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_IN2_BASE + (offset + i)*4);
    }
    return length;
}

u32 XExample_Write_in2_Bytes(XExample *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XEXAMPLE_AXI_CPU_ADDR_IN2_HIGH - XEXAMPLE_AXI_CPU_ADDR_IN2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_IN2_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XExample_Read_in2_Bytes(XExample *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XEXAMPLE_AXI_CPU_ADDR_IN2_HIGH - XEXAMPLE_AXI_CPU_ADDR_IN2_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_IN2_BASE + offset + i);
    }
    return length;
}

u32 XExample_Get_out_r_BaseAddress(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_OUT_R_BASE);
}

u32 XExample_Get_out_r_HighAddress(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_OUT_R_HIGH);
}

u32 XExample_Get_out_r_TotalBytes(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XEXAMPLE_AXI_CPU_ADDR_OUT_R_HIGH - XEXAMPLE_AXI_CPU_ADDR_OUT_R_BASE + 1);
}

u32 XExample_Get_out_r_BitWidth(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEXAMPLE_AXI_CPU_WIDTH_OUT_R;
}

u32 XExample_Get_out_r_Depth(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XEXAMPLE_AXI_CPU_DEPTH_OUT_R;
}

u32 XExample_Write_out_r_Words(XExample *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XEXAMPLE_AXI_CPU_ADDR_OUT_R_HIGH - XEXAMPLE_AXI_CPU_ADDR_OUT_R_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_OUT_R_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XExample_Read_out_r_Words(XExample *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XEXAMPLE_AXI_CPU_ADDR_OUT_R_HIGH - XEXAMPLE_AXI_CPU_ADDR_OUT_R_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_OUT_R_BASE + (offset + i)*4);
    }
    return length;
}

u32 XExample_Write_out_r_Bytes(XExample *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XEXAMPLE_AXI_CPU_ADDR_OUT_R_HIGH - XEXAMPLE_AXI_CPU_ADDR_OUT_R_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_OUT_R_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XExample_Read_out_r_Bytes(XExample *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XEXAMPLE_AXI_CPU_ADDR_OUT_R_HIGH - XEXAMPLE_AXI_CPU_ADDR_OUT_R_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Axi_cpu_BaseAddress + XEXAMPLE_AXI_CPU_ADDR_OUT_R_BASE + offset + i);
    }
    return length;
}

void XExample_InterruptGlobalEnable(XExample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XExample_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_GIE, 1);
}

void XExample_InterruptGlobalDisable(XExample *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XExample_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_GIE, 0);
}

void XExample_InterruptEnable(XExample *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XExample_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_IER);
    XExample_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_IER, Register | Mask);
}

void XExample_InterruptDisable(XExample *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XExample_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_IER);
    XExample_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_IER, Register & (~Mask));
}

void XExample_InterruptClear(XExample *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XExample_WriteReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_ISR, Mask);
}

u32 XExample_InterruptGetEnabled(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XExample_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_IER);
}

u32 XExample_InterruptGetStatus(XExample *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XExample_ReadReg(InstancePtr->Axi_cpu_BaseAddress, XEXAMPLE_AXI_CPU_ADDR_ISR);
}

