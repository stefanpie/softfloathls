// ==============================================================
// Generated by Vitis HLS v2024.1.2
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// ==============================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="scaffold_fn_scaffold_fn,hls_ip_2024_1_2,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xczu9eg-ffvb1156-2-e,HLS_INPUT_CLOCK=5.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=4.020200,HLS_SYN_LAT=72,HLS_SYN_TPT=none,HLS_SYN_MEM=1,HLS_SYN_DSP=0,HLS_SYN_FF=2254,HLS_SYN_LUT=8323,HLS_VERSION=2024_1_2}" *)

module scaffold_fn (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        x,
        coeffs_address0,
        coeffs_ce0,
        coeffs_q0,
        ap_return
);

parameter    ap_ST_fsm_state1 = 2'd1;
parameter    ap_ST_fsm_state2 = 2'd2;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [31:0] x;
output  [2:0] coeffs_address0;
output   coeffs_ce0;
input  [31:0] coeffs_q0;
output  [31:0] ap_return;

reg ap_done;
reg ap_idle;
reg ap_ready;

(* fsm_encoding = "none" *) reg   [1:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
wire    grp_top_fu_36_ap_start;
wire    grp_top_fu_36_ap_done;
wire    grp_top_fu_36_ap_idle;
wire    grp_top_fu_36_ap_ready;
wire   [2:0] grp_top_fu_36_coeffs_address0;
wire    grp_top_fu_36_coeffs_ce0;
wire   [31:0] grp_top_fu_36_ap_return;
reg    grp_top_fu_36_ap_start_reg;
wire    ap_CS_fsm_state2;
reg   [1:0] ap_NS_fsm;
reg    ap_ST_fsm_state1_blk;
reg    ap_ST_fsm_state2_blk;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 2'd1;
#0 grp_top_fu_36_ap_start_reg = 1'b0;
end

scaffold_fn_top grp_top_fu_36(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(grp_top_fu_36_ap_start),
    .ap_done(grp_top_fu_36_ap_done),
    .ap_idle(grp_top_fu_36_ap_idle),
    .ap_ready(grp_top_fu_36_ap_ready),
    .x_val(x),
    .coeffs_address0(grp_top_fu_36_coeffs_address0),
    .coeffs_ce0(grp_top_fu_36_coeffs_ce0),
    .coeffs_q0(coeffs_q0),
    .ap_return(grp_top_fu_36_ap_return)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        grp_top_fu_36_ap_start_reg <= 1'b0;
    end else begin
        if (((ap_start == 1'b1) & (1'b1 == ap_CS_fsm_state1))) begin
            grp_top_fu_36_ap_start_reg <= 1'b1;
        end else if ((grp_top_fu_36_ap_ready == 1'b1)) begin
            grp_top_fu_36_ap_start_reg <= 1'b0;
        end
    end
end

always @ (*) begin
    if ((ap_start == 1'b0)) begin
        ap_ST_fsm_state1_blk = 1'b1;
    end else begin
        ap_ST_fsm_state1_blk = 1'b0;
    end
end

always @ (*) begin
    if ((grp_top_fu_36_ap_done == 1'b0)) begin
        ap_ST_fsm_state2_blk = 1'b1;
    end else begin
        ap_ST_fsm_state2_blk = 1'b0;
    end
end

always @ (*) begin
    if (((grp_top_fu_36_ap_done == 1'b1) & (1'b1 == ap_CS_fsm_state2))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((grp_top_fu_36_ap_done == 1'b1) & (1'b1 == ap_CS_fsm_state2))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((ap_start == 1'b1) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((grp_top_fu_36_ap_done == 1'b1) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_return = grp_top_fu_36_ap_return;

assign coeffs_address0 = grp_top_fu_36_coeffs_address0;

assign coeffs_ce0 = grp_top_fu_36_coeffs_ce0;

assign grp_top_fu_36_ap_start = grp_top_fu_36_ap_start_reg;

endmodule //scaffold_fn
