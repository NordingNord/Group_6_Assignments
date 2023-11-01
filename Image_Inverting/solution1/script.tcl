############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Image_Inverting
set_top example
add_files Downloads/example_hls.cpp
add_files -tb Downloads/example_hls_tb.cpp
open_solution "solution1" -flow_target vivado
set_part {xczu3eg-sbva484-1-e}
create_clock -period 10 -name default
#source "./Image_Inverting/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
