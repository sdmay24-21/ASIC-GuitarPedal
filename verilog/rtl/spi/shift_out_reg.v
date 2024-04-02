module shift_out_reg #(
    parameter DATA_WIDTH = 32 //number of bits for i_D
    ) (
    input i_CLK, //Clock
    input i_RST, //Asynchronous reset
    input i_START, //When i_START asserted to 1, load contents of i_D into reg, begin shifting out
    input [DATA_WIDTH-1:0] i_D, //LSB input 
    output o_Q //Output to MISO
    );

    reg [DATA_WIDTH - 1 : 0] s_DATA; //Holds data to be shifted out, written when i_START asserted
    reg [7:0] s_CNT; //Internal reg to shift along enable with data out. Could also make a counter
    reg s_RUNNING;

    always @(posedge i_CLK, posedge i_RST) begin
        if(i_RST) begin //Asynch reset
            s_DATA <= 0; //LSB = 1 to stop enable when in MSB
            s_CNT <= 0;
            s_RUNNING <= 1'b0;
        end 
        else if(i_START == 1'b1 && s_RUNNING == 1'b0) begin //When starting, load and send out first bit
            s_DATA <= i_D;
            s_RUNNING <= 1'b1;
            s_DATA <= i_D;
            s_CNT <= 1;
        end
        else if((s_CNT <= DATA_WIDTH - 1) && s_RUNNING == 1'b1) begin //every other bit, just shift, NO LOAD
            s_DATA <= {s_DATA[DATA_WIDTH - 2 : 0], 1'b0};
            s_CNT <= s_CNT + 1;
        end
    end

    assign o_Q = s_DATA[DATA_WIDTH - 1];

endmodule
`default_nettype wire
