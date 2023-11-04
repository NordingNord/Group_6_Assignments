#include "hls_design_meta.h"
const Port_Property HLS_Design_Meta::port_props[]={
	Port_Property("ap_clk", 1, hls_in, -1, "", "", 1),
	Port_Property("ap_rst_n", 1, hls_in, -1, "", "", 1),
	Port_Property("Data_In_TDATA", 32, hls_in, 0, "axis", "in_data", 1),
	Port_Property("Data_In_TVALID", 1, hls_in, 6, "axis", "in_vld", 1),
	Port_Property("Data_In_TREADY", 1, hls_out, 6, "axis", "in_acc", 1),
	Port_Property("Data_In_TKEEP", 4, hls_in, 1, "axis", "in_data", 1),
	Port_Property("Data_In_TSTRB", 4, hls_in, 2, "axis", "in_data", 1),
	Port_Property("Data_In_TUSER", 2, hls_in, 3, "axis", "in_data", 1),
	Port_Property("Data_In_TLAST", 1, hls_in, 4, "axis", "in_data", 1),
	Port_Property("Data_In_TID", 5, hls_in, 5, "axis", "in_data", 1),
	Port_Property("Data_In_TDEST", 6, hls_in, 6, "axis", "in_data", 1),
	Port_Property("Data_Out_TDATA", 32, hls_out, 7, "axis", "out_data", 1),
	Port_Property("Data_Out_TVALID", 1, hls_out, 13, "axis", "out_vld", 1),
	Port_Property("Data_Out_TREADY", 1, hls_in, 13, "axis", "out_acc", 1),
	Port_Property("Data_Out_TKEEP", 4, hls_out, 8, "axis", "out_data", 1),
	Port_Property("Data_Out_TSTRB", 4, hls_out, 9, "axis", "out_data", 1),
	Port_Property("Data_Out_TUSER", 2, hls_out, 10, "axis", "out_data", 1),
	Port_Property("Data_Out_TLAST", 1, hls_out, 11, "axis", "out_data", 1),
	Port_Property("Data_Out_TID", 5, hls_out, 12, "axis", "out_data", 1),
	Port_Property("Data_Out_TDEST", 6, hls_out, 13, "axis", "out_data", 1),
	Port_Property("s_axi_control_AWVALID", 1, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_AWREADY", 1, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_AWADDR", 4, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_WVALID", 1, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_WREADY", 1, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_WDATA", 32, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_WSTRB", 4, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_ARVALID", 1, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_ARREADY", 1, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_ARADDR", 4, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_RVALID", 1, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_RREADY", 1, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_RDATA", 32, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_RRESP", 2, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_BVALID", 1, hls_out, -1, "", "", 1),
	Port_Property("s_axi_control_BREADY", 1, hls_in, -1, "", "", 1),
	Port_Property("s_axi_control_BRESP", 2, hls_out, -1, "", "", 1),
	Port_Property("interrupt", 1, hls_out, -1, "", "", 1),
};
const char* HLS_Design_Meta::dut_name = "Invert";
