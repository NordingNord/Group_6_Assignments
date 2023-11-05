// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XINVERT_H
#define XINVERT_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xinvert_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XInvert_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XInvert;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XInvert_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XInvert_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XInvert_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XInvert_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XInvert_Initialize(XInvert *InstancePtr, u16 DeviceId);
XInvert_Config* XInvert_LookupConfig(u16 DeviceId);
int XInvert_CfgInitialize(XInvert *InstancePtr, XInvert_Config *ConfigPtr);
#else
int XInvert_Initialize(XInvert *InstancePtr, const char* InstanceName);
int XInvert_Release(XInvert *InstancePtr);
#endif

void XInvert_Start(XInvert *InstancePtr);
u32 XInvert_IsDone(XInvert *InstancePtr);
u32 XInvert_IsIdle(XInvert *InstancePtr);
u32 XInvert_IsReady(XInvert *InstancePtr);
void XInvert_EnableAutoRestart(XInvert *InstancePtr);
void XInvert_DisableAutoRestart(XInvert *InstancePtr);


void XInvert_InterruptGlobalEnable(XInvert *InstancePtr);
void XInvert_InterruptGlobalDisable(XInvert *InstancePtr);
void XInvert_InterruptEnable(XInvert *InstancePtr, u32 Mask);
void XInvert_InterruptDisable(XInvert *InstancePtr, u32 Mask);
void XInvert_InterruptClear(XInvert *InstancePtr, u32 Mask);
u32 XInvert_InterruptGetEnabled(XInvert *InstancePtr);
u32 XInvert_InterruptGetStatus(XInvert *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
