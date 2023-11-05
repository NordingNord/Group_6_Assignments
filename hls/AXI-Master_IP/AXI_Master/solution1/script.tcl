############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project AXI_Master
set_top example
add_files example.cpp
add_files -tb example_test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xczu3eg-sbva484-1-e}
create_clock -period 10 -name default
config_export -description {AXI-Master IP which adds data to each value in an image area of ram} -display_name {AXI-Master add value segments 4} -format ip_catalog -output /home/frank/Documents/Git/Group_6_Assignments/hls/AXI-Master_IP/example.zip -rtl vhdl
source "./AXI_Master/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl vhdl -format ip_catalog -description "AXI-Master IP which adds data to each value in an image area of ram and sets done variable" -display_name "AXI-Master add value segments 4 with done" -output /home/frank/Documents/Git/Group_6_Assignments/hls/AXI-Master_IP/example.zip
