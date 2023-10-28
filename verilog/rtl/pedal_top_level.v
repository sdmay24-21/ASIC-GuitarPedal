module pedal (
    `ifdef USE_POWER_PINS
        inout vccd1,	// User area 1 1.8V supply
        inout vssd1,	// User area 1 digital ground
    `endif

    input wb_clk_i,     //WishBone Clock 
    input wb_rst_i,     //WishBone Clock
    input wbs_stb_i,    //?
    input wbs_cyc_i,
    input wbs_we_i,     //WishBone Write Enabled
    input [3:0] wbs_sel_i,
    input [31:0] wbs_dat_i,
    input [31:0] wbs_adr_i,
    output wbs_ack_o,
    output [31:0] wbs_dat_o,

    // Logic Analyzer Signals
    input  [127:0] la_data_in,
    output [127:0] la_data_out,
    input  [127:0] la_oenb,


    // IOs
    input miso,
    output mosi,
    output sclk,
    

    // IRQ
    output [2:0] irq

);
    


    
endmodule