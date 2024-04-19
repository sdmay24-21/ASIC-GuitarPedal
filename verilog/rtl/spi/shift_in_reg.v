module shift_in_reg #(
        parameter DATA_WIDTH = 32 //32 for data contents, extra holding bit NOT included
    ) (
    // Wishbone Slave ports (WB MI A)
    input wire i_CLK, //Clock
    input wire i_RST, //Asynchronous reset
    input wire i_EN,  //Enable to shift left by 1
    input wire i_D, //serial input, MSB first, LSB last of full data
    output reg [DATA_WIDTH:0] o_Q //parallel data output of full shifted value
    );

    always @(posedge i_CLK, posedge i_RST) begin
        if(i_RST) begin //Asynch reset
            o_Q <= 1; //LSB = 1 to stop enable when in MSB
        end 
        else if(i_EN) begin //if i_EN asserted, shift o_Q left 1 bit, and i_D into LSB
            o_Q <= {o_Q[DATA_WIDTH - 1: 0], i_D};
        end
        else 
            o_Q <= o_Q; //no shift if i_EN = '0', probably optimized out
    end

endmodule
`default_nettype wire
