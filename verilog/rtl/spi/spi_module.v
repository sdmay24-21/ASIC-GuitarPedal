module spicontroller(
    parameter ADDRESS_WIDTH = 8'd8,
        parameter DATA_WIDTH = 8'd32,
        parameter BUFFER_WIDTH = 8'd2
    ) (
        input i_SYSCLK, //System clock in user area
        input i_BCLK, //Serial Bus clock from external MCU (aka SPI Master)
        input i_SS, //Bus slave select, active high reset from Master
        input i_MOSI, //Bus Master Out Slave In
        input [DATA_WIDTH - 1:0] i_DATA_OUT, //Parallel Data to be sent TO external master SPI FROM user area modules

        output o_MISO, //Serial Bus Master In, Slave Out
        output [ADDRESS_WIDTH - 2:0] o_ADDR, //Address to determine where data should be sent/recieved. [6:3] for data address, [2:0] for which module
        output [DATA_WIDTH - 1:0] o_DATA_IN, //Parallel data to be sent TO user area modules, FROM external master SPI
        output o_DOUT_VALID //Flag asserted to 1 when i_DATA_OUT is ready to be read by submodules
    );

    //Internal signals: g_addr_shift_in 
    wire [ADDRESS_WIDTH:0] s_addr_shift_in_Q; //total output of shift reg
    wire s_READ; //If 0, write to user module. If 1, do nothing. Always read
    wire s_addr_shift_in_EN;

    //Internal signals: g_data_shift_in
    wire [DATA_WIDTH:0] s_data_shift_in_Q;
    wire s_data_shift_in_EN;

    //Internal signals: g_shift_in_dff_buffer
    wire [1:0] s_shift_in_dff_buffer_q;

    //Internal signals: g_shift_out_dff_buffer
    wire [1:0] s_shift_out_dff_buffer_q;

    //Shift in register for user area submodule address
    shift_in_reg 
    #(.DATA_WIDTH(ADDRESS_WIDTH)) //ADDRESS_WIDTH + READ/WRITE BIT
    g_addr_shift_in (
        .i_CLK  (i_BCLK), //bus clock from master SPI
        .i_RST  (i_SS), //Asynchronous reset from master SPI, active high reset
        .i_EN   (s_addr_shift_in_EN),  //Enable to shift right by 1
        .i_D    (i_MOSI), //LSB input of reg, other contents will be shifted right by 1
        .o_Q    (s_addr_shift_in_Q) //Parallel output of shift register. Includes module address, read flag, and enable bit
    );
    assign o_ADDR = s_addr_shift_in_Q[ADDRESS_WIDTH - 2:0]; //Address to determine what data/what user area module master wants
    assign s_READ = s_addr_shift_in_Q[ADDRESS_WIDTH - 1]; //First bit shifted in, if 0, then master is writing to submodule. If 1, no write occurs
    assign s_addr_shift_in_EN = ~s_addr_shift_in_Q[ADDRESS_WIDTH]; //If 1, then shift in will occur. Otherwise, no shift. Inverted since 0's reset for all bits but LSB for module

    //Shift in register for user area submodule data writes
    shift_in_reg 
    #(.DATA_WIDTH(DATA_WIDTH)) //32
    g_data_shift_in (
        .i_CLK  (i_BCLK), //bus clock from master SPI
        .i_RST  (i_SS), //Asynchronous reset from master SPI, active high reset
        .i_EN   (s_data_shift_in_EN),  //Enable to shift right by 1
        .i_D    (i_MOSI), //LSB input 
        .o_Q    (s_data_shift_in_Q) //Parallel output of shift register. Includes incoming data to submodules, and enable bit
    );
    assign o_DATA_IN = s_data_shift_in_Q[DATA_WIDTH - 1:0]; //Data shifted in from master on MOSI
    assign s_data_shift_in_EN = ~s_addr_shift_in_EN & (~s_data_shift_in_Q[DATA_WIDTH]); //Enabled if g_addr_shift_in is complete and g_data_shift_in is not complete

    //Shift in DFF clock synch buffer
    spi_module_dff_buffer
    #(.BUFFER_WIDTH(BUFFER_WIDTH)) //2
    g_shift_in_dff_buffer (
        .i_CLK  (i_SYSCLK), //system clock from user area
        .i_RST  (i_SS), //Asynchronous reset from master SPI, active high reset
        .i_EN   (1'b1),  //Always enabled
        .i_D    (s_data_shift_in_Q[DATA_WIDTH]), //Enable bit of shift in register
        .o_Q    (s_shift_in_dff_buffer_q) //part of flag conditions for s_DOUT_VALID
    );
    assign o_DOUT_VALID = (~s_READ) & (~s_shift_in_dff_buffer_q[1]) & s_shift_in_dff_buffer_q[0];

    //Shift out DFF clock synch buffer
    spi_module_dff_buffer
    #(.BUFFER_WIDTH(BUFFER_WIDTH)) //2
    g_shift_out_dff_buffer (
        .i_CLK  (i_SYSCLK), //system clock from user area
        .i_RST  (i_SS), //Asynchronous reset from master SPI, active high reset
        .i_EN   (1'b1),  //Always enabled
        .i_D    (s_addr_shift_in_Q[ADDRESS_WIDTH]), //Enable bit of shift in register
        .o_Q    (s_shift_out_dff_buffer_q) //part of flag conditions for s_DOUT_VALID
    );

    shift_out_reg 
    #(.DATA_WIDTH(DATA_WIDTH)) //32
    g_data_shift_out (
        .i_CLK   (i_BCLK), //bus clock from master SPI
        .i_RST   (i_SS), //Asynchronous reset from master SPI, active high reset
        .i_START (s_shift_out_dff_buffer_q[0]),  //Enable to shift right by 1
        .i_D     (i_DATA_OUT), //LSB input 
        .o_Q     (o_MISO) //Parallel output of shift register
    );

endmodule
`default_nettype wire
