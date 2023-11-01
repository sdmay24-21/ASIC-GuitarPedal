module pedal_top (
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

    input  [`MPRJ_IO_PADS-1:0] io_in,
    output [`MPRJ_IO_PADS-1:0] io_out,
    output [`MPRJ_IO_PADS-1:0] io_oeb
);
    // IOs
    //input miso,
    //output mosi,
    //output sclk,
    

    // IRQ
    //output [2:0] irq


    //GPIO wire assignments
    wire miso = io_in[0];
    wire mosi = io_out[0];
    wire sclk = io_out[1]
    wire cs = io_out[2];



    wire clk, adc_clock, [7:0] thres, [7:0]slope, [15:0] comp_in, [15:0] comp_out;


    //mux going to compression
    mux compressionmux(
        .signal(mem_to_comp),
        .data_in0(adc),
        .data_in1(adder_out),
        .data_out(ctrl_mux_out)
    );
    compression compress(
        .clk(clk),
        .adc_clock(adc_clock),
        .thres(thres),
        .slope(slope),
        .data_in(comp_in),
        .data_out(comp_out)
    );


    //wires for memory controller
    wire record, loop, off_chip_mem, delay_reverb, [7:0] gain, [15:0] impulses, [15:0] mem_in, [15:0] mem_out;
    memorycontroller memcontroller(
        .clk(clk),
        .adc_clock(adc_clock),
        .record(record),
        .loop(loop),
        .off_chip_mem(off_chip_mem),
        .delay_reverb(delay_reverb),
        .gain(gain),
        .impulses(impulses),
        .data_in(mem_in),
        .data_out(mem_out)
    );

    wire [7:0] trim1, [7:0] trim2, [7:0] trim3, [7:0] trim4, [15:0]adc, [15:0]dac, [1:0] trim_mux;
    spicontroller spi(
        //inputs
        .clk(clk),
        .adc_clock(adc_clock),
        .trim1(trim1),
        .trim2(trim2),
        .trim3(trim3),
        .trim4(trim4),
        .dac(dac),
        .miso(miso),
        .mosi(mosi),
        .sclk(sclk),
        .cs(cs),

        //outputs
        .adc(adc),
        .mux(trim_mux)
    );

    controller control(
        //inputs
        .clk(clk),
        .adc_clock(adc_clock),
        .trim1(trim1), 
        .trim2(trim2),
        .trim3(trim3),
        .trim4(trim4),
        //memory control
        .record(record),
        .loop(loop),
        .off_chip_mem(off_chip_mem),
        .delay_reverb(delay_reverb),
        .gain(gain),
        .impulses(impulses),
        //compression
        .thres(thres),
        .slope(slope),
        //top level
        .mem_to_comp(mem_to_comp)
    );
    


    //adder mux
    wire [15:0] adder_input0, [15:0] adder_out;
    mux adder_mux(
        .signal(mem_to_comp),
        .data_in0(comp_out),
        .data_in1(mem_out),
        .data_out(adder_input0)
    );

    adder add(
        .clk(clk),
        .adc_clock(adc_clock), //resets on adc_clock
        .data_in(adder_input0)
        //.data_in1(adder_input1) //dont need because it is add out
        .data_out(adder_out)
    );






endmodule