############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Sobel_Filter
set_top Sobel
add_files SobelTest.cpp
add_files -tb Sobel_Test_tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "SobelSolution" -flow_target vivado
set_part {xczu3eg-sbva484-1-e}
create_clock -period 10 -name default
source "./Sobel_Filter/SobelSolution/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl vhdl -format ip_catalog
