-- ==============================================================
-- RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
-- Version: 2020.2
-- Copyright (C) Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- 
-- ===========================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Invert is
generic (
    C_S_AXI_CONTROL_ADDR_WIDTH : INTEGER := 4;
    C_S_AXI_CONTROL_DATA_WIDTH : INTEGER := 32 );
port (
    ap_clk : IN STD_LOGIC;
    ap_rst_n : IN STD_LOGIC;
    Data_In_TDATA : IN STD_LOGIC_VECTOR (31 downto 0);
    Data_In_TVALID : IN STD_LOGIC;
    Data_In_TREADY : OUT STD_LOGIC;
    Data_In_TKEEP : IN STD_LOGIC_VECTOR (3 downto 0);
    Data_In_TSTRB : IN STD_LOGIC_VECTOR (3 downto 0);
    Data_In_TUSER : IN STD_LOGIC_VECTOR (1 downto 0);
    Data_In_TLAST : IN STD_LOGIC_VECTOR (0 downto 0);
    Data_In_TID : IN STD_LOGIC_VECTOR (4 downto 0);
    Data_In_TDEST : IN STD_LOGIC_VECTOR (5 downto 0);
    Data_Out_TDATA : OUT STD_LOGIC_VECTOR (31 downto 0);
    Data_Out_TVALID : OUT STD_LOGIC;
    Data_Out_TREADY : IN STD_LOGIC;
    Data_Out_TKEEP : OUT STD_LOGIC_VECTOR (3 downto 0);
    Data_Out_TSTRB : OUT STD_LOGIC_VECTOR (3 downto 0);
    Data_Out_TUSER : OUT STD_LOGIC_VECTOR (1 downto 0);
    Data_Out_TLAST : OUT STD_LOGIC_VECTOR (0 downto 0);
    Data_Out_TID : OUT STD_LOGIC_VECTOR (4 downto 0);
    Data_Out_TDEST : OUT STD_LOGIC_VECTOR (5 downto 0);
    s_axi_control_AWVALID : IN STD_LOGIC;
    s_axi_control_AWREADY : OUT STD_LOGIC;
    s_axi_control_AWADDR : IN STD_LOGIC_VECTOR (C_S_AXI_CONTROL_ADDR_WIDTH-1 downto 0);
    s_axi_control_WVALID : IN STD_LOGIC;
    s_axi_control_WREADY : OUT STD_LOGIC;
    s_axi_control_WDATA : IN STD_LOGIC_VECTOR (C_S_AXI_CONTROL_DATA_WIDTH-1 downto 0);
    s_axi_control_WSTRB : IN STD_LOGIC_VECTOR (C_S_AXI_CONTROL_DATA_WIDTH/8-1 downto 0);
    s_axi_control_ARVALID : IN STD_LOGIC;
    s_axi_control_ARREADY : OUT STD_LOGIC;
    s_axi_control_ARADDR : IN STD_LOGIC_VECTOR (C_S_AXI_CONTROL_ADDR_WIDTH-1 downto 0);
    s_axi_control_RVALID : OUT STD_LOGIC;
    s_axi_control_RREADY : IN STD_LOGIC;
    s_axi_control_RDATA : OUT STD_LOGIC_VECTOR (C_S_AXI_CONTROL_DATA_WIDTH-1 downto 0);
    s_axi_control_RRESP : OUT STD_LOGIC_VECTOR (1 downto 0);
    s_axi_control_BVALID : OUT STD_LOGIC;
    s_axi_control_BREADY : IN STD_LOGIC;
    s_axi_control_BRESP : OUT STD_LOGIC_VECTOR (1 downto 0);
    interrupt : OUT STD_LOGIC );
end;


architecture behav of Invert is 
    attribute CORE_GENERATION_INFO : STRING;
    attribute CORE_GENERATION_INFO of behav : architecture is
    "Invert_Invert,hls_ip_2020_2,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xczu3eg-sbva484-1-e,HLS_INPUT_CLOCK=10.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=1.203000,HLS_SYN_LAT=-1,HLS_SYN_TPT=none,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=41,HLS_SYN_LUT=132,HLS_VERSION=2020_2}";
    constant ap_const_logic_1 : STD_LOGIC := '1';
    constant ap_const_logic_0 : STD_LOGIC := '0';
    constant ap_ST_fsm_state1 : STD_LOGIC_VECTOR (2 downto 0) := "001";
    constant ap_ST_fsm_pp0_stage0 : STD_LOGIC_VECTOR (2 downto 0) := "010";
    constant ap_ST_fsm_state4 : STD_LOGIC_VECTOR (2 downto 0) := "100";
    constant ap_const_lv32_0 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000000";
    constant ap_const_boolean_1 : BOOLEAN := true;
    constant ap_const_lv32_1 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000001";
    constant ap_const_boolean_0 : BOOLEAN := false;
    constant C_S_AXI_DATA_WIDTH : INTEGER range 63 downto 0 := 20;
    constant ap_const_lv1_1 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv32_5 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000101";
    constant ap_const_lv32_2 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000010";

    signal ap_rst_n_inv : STD_LOGIC;
    signal ap_start : STD_LOGIC;
    signal ap_done : STD_LOGIC;
    signal ap_idle : STD_LOGIC;
    signal ap_CS_fsm : STD_LOGIC_VECTOR (2 downto 0) := "001";
    attribute fsm_encoding : string;
    attribute fsm_encoding of ap_CS_fsm : signal is "none";
    signal ap_CS_fsm_state1 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state1 : signal is "none";
    signal ap_ready : STD_LOGIC;
    signal Data_In_TDATA_blk_n : STD_LOGIC;
    signal ap_CS_fsm_pp0_stage0 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_pp0_stage0 : signal is "none";
    signal ap_enable_reg_pp0_iter0 : STD_LOGIC := '0';
    signal ap_block_pp0_stage0 : BOOLEAN;
    signal Data_Out_TDATA_blk_n : STD_LOGIC;
    signal ap_enable_reg_pp0_iter1 : STD_LOGIC := '0';
    signal ap_block_state2_pp0_stage0_iter0 : BOOLEAN;
    signal ap_block_state3_pp0_stage0_iter1 : BOOLEAN;
    signal ap_block_pp0_stage0_11001 : BOOLEAN;
    signal tmp_last_V_fu_128_p1 : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_block_pp0_stage0_subdone : BOOLEAN;
    signal ap_condition_pp0_flush_enable : STD_LOGIC;
    signal ap_block_pp0_stage0_01001 : BOOLEAN;
    signal ap_CS_fsm_state4 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_state4 : signal is "none";
    signal regslice_both_Data_Out_V_data_V_U_apdone_blk : STD_LOGIC;
    signal ap_NS_fsm : STD_LOGIC_VECTOR (2 downto 0);
    signal ap_idle_pp0 : STD_LOGIC;
    signal ap_enable_pp0 : STD_LOGIC;
    signal regslice_both_Data_In_V_data_V_U_apdone_blk : STD_LOGIC;
    signal Data_In_TDATA_int_regslice : STD_LOGIC_VECTOR (31 downto 0);
    signal Data_In_TVALID_int_regslice : STD_LOGIC;
    signal Data_In_TREADY_int_regslice : STD_LOGIC;
    signal regslice_both_Data_In_V_data_V_U_ack_in : STD_LOGIC;
    signal regslice_both_Data_In_V_keep_V_U_apdone_blk : STD_LOGIC;
    signal Data_In_TKEEP_int_regslice : STD_LOGIC_VECTOR (3 downto 0);
    signal regslice_both_Data_In_V_keep_V_U_vld_out : STD_LOGIC;
    signal regslice_both_Data_In_V_keep_V_U_ack_in : STD_LOGIC;
    signal regslice_both_Data_In_V_strb_V_U_apdone_blk : STD_LOGIC;
    signal Data_In_TSTRB_int_regslice : STD_LOGIC_VECTOR (3 downto 0);
    signal regslice_both_Data_In_V_strb_V_U_vld_out : STD_LOGIC;
    signal regslice_both_Data_In_V_strb_V_U_ack_in : STD_LOGIC;
    signal regslice_both_Data_In_V_user_V_U_apdone_blk : STD_LOGIC;
    signal Data_In_TUSER_int_regslice : STD_LOGIC_VECTOR (1 downto 0);
    signal regslice_both_Data_In_V_user_V_U_vld_out : STD_LOGIC;
    signal regslice_both_Data_In_V_user_V_U_ack_in : STD_LOGIC;
    signal regslice_both_Data_In_V_last_V_U_apdone_blk : STD_LOGIC;
    signal Data_In_TLAST_int_regslice : STD_LOGIC_VECTOR (0 downto 0);
    signal regslice_both_Data_In_V_last_V_U_vld_out : STD_LOGIC;
    signal regslice_both_Data_In_V_last_V_U_ack_in : STD_LOGIC;
    signal regslice_both_Data_In_V_id_V_U_apdone_blk : STD_LOGIC;
    signal Data_In_TID_int_regslice : STD_LOGIC_VECTOR (4 downto 0);
    signal regslice_both_Data_In_V_id_V_U_vld_out : STD_LOGIC;
    signal regslice_both_Data_In_V_id_V_U_ack_in : STD_LOGIC;
    signal regslice_both_Data_In_V_dest_V_U_apdone_blk : STD_LOGIC;
    signal Data_In_TDEST_int_regslice : STD_LOGIC_VECTOR (5 downto 0);
    signal regslice_both_Data_In_V_dest_V_U_vld_out : STD_LOGIC;
    signal regslice_both_Data_In_V_dest_V_U_ack_in : STD_LOGIC;
    signal Data_Out_TDATA_int_regslice : STD_LOGIC_VECTOR (31 downto 0);
    signal Data_Out_TVALID_int_regslice : STD_LOGIC;
    signal Data_Out_TREADY_int_regslice : STD_LOGIC;
    signal regslice_both_Data_Out_V_data_V_U_vld_out : STD_LOGIC;
    signal regslice_both_Data_Out_V_keep_V_U_apdone_blk : STD_LOGIC;
    signal regslice_both_Data_Out_V_keep_V_U_ack_in_dummy : STD_LOGIC;
    signal regslice_both_Data_Out_V_keep_V_U_vld_out : STD_LOGIC;
    signal regslice_both_Data_Out_V_strb_V_U_apdone_blk : STD_LOGIC;
    signal regslice_both_Data_Out_V_strb_V_U_ack_in_dummy : STD_LOGIC;
    signal regslice_both_Data_Out_V_strb_V_U_vld_out : STD_LOGIC;
    signal regslice_both_Data_Out_V_user_V_U_apdone_blk : STD_LOGIC;
    signal regslice_both_Data_Out_V_user_V_U_ack_in_dummy : STD_LOGIC;
    signal regslice_both_Data_Out_V_user_V_U_vld_out : STD_LOGIC;
    signal regslice_both_Data_Out_V_last_V_U_apdone_blk : STD_LOGIC;
    signal regslice_both_Data_Out_V_last_V_U_ack_in_dummy : STD_LOGIC;
    signal regslice_both_Data_Out_V_last_V_U_vld_out : STD_LOGIC;
    signal regslice_both_Data_Out_V_id_V_U_apdone_blk : STD_LOGIC;
    signal regslice_both_Data_Out_V_id_V_U_ack_in_dummy : STD_LOGIC;
    signal regslice_both_Data_Out_V_id_V_U_vld_out : STD_LOGIC;
    signal regslice_both_Data_Out_V_dest_V_U_apdone_blk : STD_LOGIC;
    signal regslice_both_Data_Out_V_dest_V_U_ack_in_dummy : STD_LOGIC;
    signal regslice_both_Data_Out_V_dest_V_U_vld_out : STD_LOGIC;
    signal ap_ce_reg : STD_LOGIC;

    component Invert_control_s_axi IS
    generic (
        C_S_AXI_ADDR_WIDTH : INTEGER;
        C_S_AXI_DATA_WIDTH : INTEGER );
    port (
        AWVALID : IN STD_LOGIC;
        AWREADY : OUT STD_LOGIC;
        AWADDR : IN STD_LOGIC_VECTOR (C_S_AXI_ADDR_WIDTH-1 downto 0);
        WVALID : IN STD_LOGIC;
        WREADY : OUT STD_LOGIC;
        WDATA : IN STD_LOGIC_VECTOR (C_S_AXI_DATA_WIDTH-1 downto 0);
        WSTRB : IN STD_LOGIC_VECTOR (C_S_AXI_DATA_WIDTH/8-1 downto 0);
        ARVALID : IN STD_LOGIC;
        ARREADY : OUT STD_LOGIC;
        ARADDR : IN STD_LOGIC_VECTOR (C_S_AXI_ADDR_WIDTH-1 downto 0);
        RVALID : OUT STD_LOGIC;
        RREADY : IN STD_LOGIC;
        RDATA : OUT STD_LOGIC_VECTOR (C_S_AXI_DATA_WIDTH-1 downto 0);
        RRESP : OUT STD_LOGIC_VECTOR (1 downto 0);
        BVALID : OUT STD_LOGIC;
        BREADY : IN STD_LOGIC;
        BRESP : OUT STD_LOGIC_VECTOR (1 downto 0);
        ACLK : IN STD_LOGIC;
        ARESET : IN STD_LOGIC;
        ACLK_EN : IN STD_LOGIC;
        ap_start : OUT STD_LOGIC;
        interrupt : OUT STD_LOGIC;
        ap_ready : IN STD_LOGIC;
        ap_done : IN STD_LOGIC;
        ap_idle : IN STD_LOGIC );
    end component;


    component Invert_regslice_both IS
    generic (
        DataWidth : INTEGER );
    port (
        ap_clk : IN STD_LOGIC;
        ap_rst : IN STD_LOGIC;
        data_in : IN STD_LOGIC_VECTOR (DataWidth-1 downto 0);
        vld_in : IN STD_LOGIC;
        ack_in : OUT STD_LOGIC;
        data_out : OUT STD_LOGIC_VECTOR (DataWidth-1 downto 0);
        vld_out : OUT STD_LOGIC;
        ack_out : IN STD_LOGIC;
        apdone_blk : OUT STD_LOGIC );
    end component;



begin
    control_s_axi_U : component Invert_control_s_axi
    generic map (
        C_S_AXI_ADDR_WIDTH => C_S_AXI_CONTROL_ADDR_WIDTH,
        C_S_AXI_DATA_WIDTH => C_S_AXI_CONTROL_DATA_WIDTH)
    port map (
        AWVALID => s_axi_control_AWVALID,
        AWREADY => s_axi_control_AWREADY,
        AWADDR => s_axi_control_AWADDR,
        WVALID => s_axi_control_WVALID,
        WREADY => s_axi_control_WREADY,
        WDATA => s_axi_control_WDATA,
        WSTRB => s_axi_control_WSTRB,
        ARVALID => s_axi_control_ARVALID,
        ARREADY => s_axi_control_ARREADY,
        ARADDR => s_axi_control_ARADDR,
        RVALID => s_axi_control_RVALID,
        RREADY => s_axi_control_RREADY,
        RDATA => s_axi_control_RDATA,
        RRESP => s_axi_control_RRESP,
        BVALID => s_axi_control_BVALID,
        BREADY => s_axi_control_BREADY,
        BRESP => s_axi_control_BRESP,
        ACLK => ap_clk,
        ARESET => ap_rst_n_inv,
        ACLK_EN => ap_const_logic_1,
        ap_start => ap_start,
        interrupt => interrupt,
        ap_ready => ap_ready,
        ap_done => ap_done,
        ap_idle => ap_idle);

    regslice_both_Data_In_V_data_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 32)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TDATA,
        vld_in => Data_In_TVALID,
        ack_in => regslice_both_Data_In_V_data_V_U_ack_in,
        data_out => Data_In_TDATA_int_regslice,
        vld_out => Data_In_TVALID_int_regslice,
        ack_out => Data_In_TREADY_int_regslice,
        apdone_blk => regslice_both_Data_In_V_data_V_U_apdone_blk);

    regslice_both_Data_In_V_keep_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 4)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TKEEP,
        vld_in => Data_In_TVALID,
        ack_in => regslice_both_Data_In_V_keep_V_U_ack_in,
        data_out => Data_In_TKEEP_int_regslice,
        vld_out => regslice_both_Data_In_V_keep_V_U_vld_out,
        ack_out => Data_In_TREADY_int_regslice,
        apdone_blk => regslice_both_Data_In_V_keep_V_U_apdone_blk);

    regslice_both_Data_In_V_strb_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 4)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TSTRB,
        vld_in => Data_In_TVALID,
        ack_in => regslice_both_Data_In_V_strb_V_U_ack_in,
        data_out => Data_In_TSTRB_int_regslice,
        vld_out => regslice_both_Data_In_V_strb_V_U_vld_out,
        ack_out => Data_In_TREADY_int_regslice,
        apdone_blk => regslice_both_Data_In_V_strb_V_U_apdone_blk);

    regslice_both_Data_In_V_user_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 2)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TUSER,
        vld_in => Data_In_TVALID,
        ack_in => regslice_both_Data_In_V_user_V_U_ack_in,
        data_out => Data_In_TUSER_int_regslice,
        vld_out => regslice_both_Data_In_V_user_V_U_vld_out,
        ack_out => Data_In_TREADY_int_regslice,
        apdone_blk => regslice_both_Data_In_V_user_V_U_apdone_blk);

    regslice_both_Data_In_V_last_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 1)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TLAST,
        vld_in => Data_In_TVALID,
        ack_in => regslice_both_Data_In_V_last_V_U_ack_in,
        data_out => Data_In_TLAST_int_regslice,
        vld_out => regslice_both_Data_In_V_last_V_U_vld_out,
        ack_out => Data_In_TREADY_int_regslice,
        apdone_blk => regslice_both_Data_In_V_last_V_U_apdone_blk);

    regslice_both_Data_In_V_id_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 5)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TID,
        vld_in => Data_In_TVALID,
        ack_in => regslice_both_Data_In_V_id_V_U_ack_in,
        data_out => Data_In_TID_int_regslice,
        vld_out => regslice_both_Data_In_V_id_V_U_vld_out,
        ack_out => Data_In_TREADY_int_regslice,
        apdone_blk => regslice_both_Data_In_V_id_V_U_apdone_blk);

    regslice_both_Data_In_V_dest_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 6)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TDEST,
        vld_in => Data_In_TVALID,
        ack_in => regslice_both_Data_In_V_dest_V_U_ack_in,
        data_out => Data_In_TDEST_int_regslice,
        vld_out => regslice_both_Data_In_V_dest_V_U_vld_out,
        ack_out => Data_In_TREADY_int_regslice,
        apdone_blk => regslice_both_Data_In_V_dest_V_U_apdone_blk);

    regslice_both_Data_Out_V_data_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 32)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_Out_TDATA_int_regslice,
        vld_in => Data_Out_TVALID_int_regslice,
        ack_in => Data_Out_TREADY_int_regslice,
        data_out => Data_Out_TDATA,
        vld_out => regslice_both_Data_Out_V_data_V_U_vld_out,
        ack_out => Data_Out_TREADY,
        apdone_blk => regslice_both_Data_Out_V_data_V_U_apdone_blk);

    regslice_both_Data_Out_V_keep_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 4)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TKEEP_int_regslice,
        vld_in => Data_Out_TVALID_int_regslice,
        ack_in => regslice_both_Data_Out_V_keep_V_U_ack_in_dummy,
        data_out => Data_Out_TKEEP,
        vld_out => regslice_both_Data_Out_V_keep_V_U_vld_out,
        ack_out => Data_Out_TREADY,
        apdone_blk => regslice_both_Data_Out_V_keep_V_U_apdone_blk);

    regslice_both_Data_Out_V_strb_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 4)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TSTRB_int_regslice,
        vld_in => Data_Out_TVALID_int_regslice,
        ack_in => regslice_both_Data_Out_V_strb_V_U_ack_in_dummy,
        data_out => Data_Out_TSTRB,
        vld_out => regslice_both_Data_Out_V_strb_V_U_vld_out,
        ack_out => Data_Out_TREADY,
        apdone_blk => regslice_both_Data_Out_V_strb_V_U_apdone_blk);

    regslice_both_Data_Out_V_user_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 2)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TUSER_int_regslice,
        vld_in => Data_Out_TVALID_int_regslice,
        ack_in => regslice_both_Data_Out_V_user_V_U_ack_in_dummy,
        data_out => Data_Out_TUSER,
        vld_out => regslice_both_Data_Out_V_user_V_U_vld_out,
        ack_out => Data_Out_TREADY,
        apdone_blk => regslice_both_Data_Out_V_user_V_U_apdone_blk);

    regslice_both_Data_Out_V_last_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 1)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TLAST_int_regslice,
        vld_in => Data_Out_TVALID_int_regslice,
        ack_in => regslice_both_Data_Out_V_last_V_U_ack_in_dummy,
        data_out => Data_Out_TLAST,
        vld_out => regslice_both_Data_Out_V_last_V_U_vld_out,
        ack_out => Data_Out_TREADY,
        apdone_blk => regslice_both_Data_Out_V_last_V_U_apdone_blk);

    regslice_both_Data_Out_V_id_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 5)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TID_int_regslice,
        vld_in => Data_Out_TVALID_int_regslice,
        ack_in => regslice_both_Data_Out_V_id_V_U_ack_in_dummy,
        data_out => Data_Out_TID,
        vld_out => regslice_both_Data_Out_V_id_V_U_vld_out,
        ack_out => Data_Out_TREADY,
        apdone_blk => regslice_both_Data_Out_V_id_V_U_apdone_blk);

    regslice_both_Data_Out_V_dest_V_U : component Invert_regslice_both
    generic map (
        DataWidth => 6)
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst_n_inv,
        data_in => Data_In_TDEST_int_regslice,
        vld_in => Data_Out_TVALID_int_regslice,
        ack_in => regslice_both_Data_Out_V_dest_V_U_ack_in_dummy,
        data_out => Data_Out_TDEST,
        vld_out => regslice_both_Data_Out_V_dest_V_U_vld_out,
        ack_out => Data_Out_TREADY,
        apdone_blk => regslice_both_Data_Out_V_dest_V_U_apdone_blk);





    ap_CS_fsm_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst_n_inv = '1') then
                ap_CS_fsm <= ap_ST_fsm_state1;
            else
                ap_CS_fsm <= ap_NS_fsm;
            end if;
        end if;
    end process;


    ap_enable_reg_pp0_iter0_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst_n_inv = '1') then
                ap_enable_reg_pp0_iter0 <= ap_const_logic_0;
            else
                if ((ap_const_logic_1 = ap_condition_pp0_flush_enable)) then 
                    ap_enable_reg_pp0_iter0 <= ap_const_logic_0;
                elsif (((ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1))) then 
                    ap_enable_reg_pp0_iter0 <= ap_const_logic_1;
                end if; 
            end if;
        end if;
    end process;


    ap_enable_reg_pp0_iter1_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst_n_inv = '1') then
                ap_enable_reg_pp0_iter1 <= ap_const_logic_0;
            else
                if ((ap_const_boolean_0 = ap_block_pp0_stage0_subdone)) then 
                    ap_enable_reg_pp0_iter1 <= ap_enable_reg_pp0_iter0;
                elsif (((ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1))) then 
                    ap_enable_reg_pp0_iter1 <= ap_const_logic_0;
                end if; 
            end if;
        end if;
    end process;


    ap_NS_fsm_assign_proc : process (ap_start, ap_CS_fsm, ap_CS_fsm_state1, ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter0, ap_enable_reg_pp0_iter1, ap_block_pp0_stage0_subdone, ap_CS_fsm_state4, regslice_both_Data_Out_V_data_V_U_apdone_blk)
    begin
        case ap_CS_fsm is
            when ap_ST_fsm_state1 => 
                if (((ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_1))) then
                    ap_NS_fsm <= ap_ST_fsm_pp0_stage0;
                else
                    ap_NS_fsm <= ap_ST_fsm_state1;
                end if;
            when ap_ST_fsm_pp0_stage0 => 
                if (not(((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_enable_reg_pp0_iter0 = ap_const_logic_0) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0)))) then
                    ap_NS_fsm <= ap_ST_fsm_pp0_stage0;
                elsif (((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_enable_reg_pp0_iter0 = ap_const_logic_0) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then
                    ap_NS_fsm <= ap_ST_fsm_state4;
                else
                    ap_NS_fsm <= ap_ST_fsm_pp0_stage0;
                end if;
            when ap_ST_fsm_state4 => 
                if (((regslice_both_Data_Out_V_data_V_U_apdone_blk = ap_const_logic_0) and (ap_const_logic_1 = ap_CS_fsm_state4))) then
                    ap_NS_fsm <= ap_ST_fsm_state1;
                else
                    ap_NS_fsm <= ap_ST_fsm_state4;
                end if;
            when others =>  
                ap_NS_fsm <= "XXX";
        end case;
    end process;

    Data_In_TDATA_blk_n_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter0, ap_block_pp0_stage0, Data_In_TVALID_int_regslice)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            Data_In_TDATA_blk_n <= Data_In_TVALID_int_regslice;
        else 
            Data_In_TDATA_blk_n <= ap_const_logic_1;
        end if; 
    end process;

    Data_In_TREADY <= regslice_both_Data_In_V_data_V_U_ack_in;

    Data_In_TREADY_int_regslice_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter0, ap_block_pp0_stage0_11001)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            Data_In_TREADY_int_regslice <= ap_const_logic_1;
        else 
            Data_In_TREADY_int_regslice <= ap_const_logic_0;
        end if; 
    end process;


    Data_Out_TDATA_blk_n_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter0, ap_block_pp0_stage0, ap_enable_reg_pp0_iter1, Data_Out_TREADY_int_regslice)
    begin
        if ((((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0)) or ((ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0)))) then 
            Data_Out_TDATA_blk_n <= Data_Out_TREADY_int_regslice;
        else 
            Data_Out_TDATA_blk_n <= ap_const_logic_1;
        end if; 
    end process;

    Data_Out_TDATA_int_regslice <= std_logic_vector(unsigned(Data_In_TDATA_int_regslice) + unsigned(ap_const_lv32_5));
    Data_Out_TVALID <= regslice_both_Data_Out_V_data_V_U_vld_out;

    Data_Out_TVALID_int_regslice_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter0, ap_block_pp0_stage0_11001)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            Data_Out_TVALID_int_regslice <= ap_const_logic_1;
        else 
            Data_Out_TVALID_int_regslice <= ap_const_logic_0;
        end if; 
    end process;

    ap_CS_fsm_pp0_stage0 <= ap_CS_fsm(1);
    ap_CS_fsm_state1 <= ap_CS_fsm(0);
    ap_CS_fsm_state4 <= ap_CS_fsm(2);
        ap_block_pp0_stage0 <= not((ap_const_boolean_1 = ap_const_boolean_1));

    ap_block_pp0_stage0_01001_assign_proc : process(ap_enable_reg_pp0_iter0, ap_enable_reg_pp0_iter1, Data_In_TVALID_int_regslice, Data_Out_TREADY_int_regslice)
    begin
                ap_block_pp0_stage0_01001 <= (((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_0 = Data_Out_TREADY_int_regslice)) or ((ap_enable_reg_pp0_iter0 = ap_const_logic_1) and ((ap_const_logic_0 = Data_Out_TREADY_int_regslice) or (ap_const_logic_0 = Data_In_TVALID_int_regslice))));
    end process;


    ap_block_pp0_stage0_11001_assign_proc : process(ap_enable_reg_pp0_iter0, ap_enable_reg_pp0_iter1, Data_In_TVALID_int_regslice, Data_Out_TREADY_int_regslice)
    begin
                ap_block_pp0_stage0_11001 <= (((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_0 = Data_Out_TREADY_int_regslice)) or ((ap_enable_reg_pp0_iter0 = ap_const_logic_1) and ((ap_const_logic_0 = Data_Out_TREADY_int_regslice) or (ap_const_logic_0 = Data_In_TVALID_int_regslice))));
    end process;


    ap_block_pp0_stage0_subdone_assign_proc : process(ap_enable_reg_pp0_iter0, ap_enable_reg_pp0_iter1, Data_In_TVALID_int_regslice, Data_Out_TREADY_int_regslice)
    begin
                ap_block_pp0_stage0_subdone <= (((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_0 = Data_Out_TREADY_int_regslice)) or ((ap_enable_reg_pp0_iter0 = ap_const_logic_1) and ((ap_const_logic_0 = Data_Out_TREADY_int_regslice) or (ap_const_logic_0 = Data_In_TVALID_int_regslice))));
    end process;


    ap_block_state2_pp0_stage0_iter0_assign_proc : process(Data_In_TVALID_int_regslice, Data_Out_TREADY_int_regslice)
    begin
                ap_block_state2_pp0_stage0_iter0 <= ((ap_const_logic_0 = Data_Out_TREADY_int_regslice) or (ap_const_logic_0 = Data_In_TVALID_int_regslice));
    end process;


    ap_block_state3_pp0_stage0_iter1_assign_proc : process(Data_Out_TREADY_int_regslice)
    begin
                ap_block_state3_pp0_stage0_iter1 <= (ap_const_logic_0 = Data_Out_TREADY_int_regslice);
    end process;


    ap_condition_pp0_flush_enable_assign_proc : process(ap_CS_fsm_pp0_stage0, tmp_last_V_fu_128_p1, ap_block_pp0_stage0_subdone)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (tmp_last_V_fu_128_p1 = ap_const_lv1_1))) then 
            ap_condition_pp0_flush_enable <= ap_const_logic_1;
        else 
            ap_condition_pp0_flush_enable <= ap_const_logic_0;
        end if; 
    end process;


    ap_done_assign_proc : process(ap_CS_fsm_state4, regslice_both_Data_Out_V_data_V_U_apdone_blk)
    begin
        if (((regslice_both_Data_Out_V_data_V_U_apdone_blk = ap_const_logic_0) and (ap_const_logic_1 = ap_CS_fsm_state4))) then 
            ap_done <= ap_const_logic_1;
        else 
            ap_done <= ap_const_logic_0;
        end if; 
    end process;

    ap_enable_pp0 <= (ap_idle_pp0 xor ap_const_logic_1);

    ap_idle_assign_proc : process(ap_start, ap_CS_fsm_state1)
    begin
        if (((ap_const_logic_1 = ap_CS_fsm_state1) and (ap_start = ap_const_logic_0))) then 
            ap_idle <= ap_const_logic_1;
        else 
            ap_idle <= ap_const_logic_0;
        end if; 
    end process;


    ap_idle_pp0_assign_proc : process(ap_enable_reg_pp0_iter0, ap_enable_reg_pp0_iter1)
    begin
        if (((ap_enable_reg_pp0_iter1 = ap_const_logic_0) and (ap_enable_reg_pp0_iter0 = ap_const_logic_0))) then 
            ap_idle_pp0 <= ap_const_logic_1;
        else 
            ap_idle_pp0 <= ap_const_logic_0;
        end if; 
    end process;


    ap_ready_assign_proc : process(ap_CS_fsm_state4, regslice_both_Data_Out_V_data_V_U_apdone_blk)
    begin
        if (((regslice_both_Data_Out_V_data_V_U_apdone_blk = ap_const_logic_0) and (ap_const_logic_1 = ap_CS_fsm_state4))) then 
            ap_ready <= ap_const_logic_1;
        else 
            ap_ready <= ap_const_logic_0;
        end if; 
    end process;


    ap_rst_n_inv_assign_proc : process(ap_rst_n)
    begin
                ap_rst_n_inv <= not(ap_rst_n);
    end process;

    tmp_last_V_fu_128_p1 <= Data_In_TLAST_int_regslice;
end behav;
