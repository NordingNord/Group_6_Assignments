// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// AXI_CPU
// 0x0000 : Control signals
//          bit 0  - ap_start (Read/Write/COH)
//          bit 1  - ap_done (Read/COR)
//          bit 2  - ap_idle (Read)
//          bit 3  - ap_ready (Read)
//          bit 7  - auto_restart (Read/Write)
//          others - reserved
// 0x0004 : Global Interrupt Enable Register
//          bit 0  - Global Interrupt Enable (Read/Write)
//          others - reserved
// 0x0008 : IP Interrupt Enable Register (Read/Write)
//          bit 0  - enable ap_done interrupt (Read/Write)
//          bit 1  - enable ap_ready interrupt (Read/Write)
//          others - reserved
// 0x000c : IP Interrupt Status Register (Read/TOW)
//          bit 0  - ap_done (COR/TOW)
//          bit 1  - ap_ready (COR/TOW)
//          others - reserved
// 0x1000 ~
// 0x1fff : Memory 'in1' (1000 * 32b)
//          Word n : bit [31:0] - in1[n]
// 0x2000 ~
// 0x2fff : Memory 'in2' (1000 * 32b)
//          Word n : bit [31:0] - in2[n]
// 0x3000 ~
// 0x3fff : Memory 'out_r' (1000 * 32b)
//          Word n : bit [31:0] - out_r[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XEXAMPLE_AXI_CPU_ADDR_AP_CTRL    0x0000
#define XEXAMPLE_AXI_CPU_ADDR_GIE        0x0004
#define XEXAMPLE_AXI_CPU_ADDR_IER        0x0008
#define XEXAMPLE_AXI_CPU_ADDR_ISR        0x000c
#define XEXAMPLE_AXI_CPU_ADDR_IN1_BASE   0x1000
#define XEXAMPLE_AXI_CPU_ADDR_IN1_HIGH   0x1fff
#define XEXAMPLE_AXI_CPU_WIDTH_IN1       32
#define XEXAMPLE_AXI_CPU_DEPTH_IN1       1000
#define XEXAMPLE_AXI_CPU_ADDR_IN2_BASE   0x2000
#define XEXAMPLE_AXI_CPU_ADDR_IN2_HIGH   0x2fff
#define XEXAMPLE_AXI_CPU_WIDTH_IN2       32
#define XEXAMPLE_AXI_CPU_DEPTH_IN2       1000
#define XEXAMPLE_AXI_CPU_ADDR_OUT_R_BASE 0x3000
#define XEXAMPLE_AXI_CPU_ADDR_OUT_R_HIGH 0x3fff
#define XEXAMPLE_AXI_CPU_WIDTH_OUT_R     32
#define XEXAMPLE_AXI_CPU_DEPTH_OUT_R     1000

