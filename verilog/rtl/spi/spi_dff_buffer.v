module spi_dff_buffer #(
        parameter BUFFER_WIDTH = 2 //N system clock cycles to buffer
    ) (
    // Wishbone Slave ports (WB MI A)
    input wire i_CLK, //Clock
    input wire i_RST, //Asynchronous reset
    input wire i_EN,  //Enable to shift left by 1
    input wire i_D, //serial input, MSB first, LSB last of full data
    output wire [1:0] o_Q //Two MSB DFF outputs
    );

    //Internal signals
    reg [BUFFER_WIDTH:0] s_buffer;

    always @(posedge i_CLK, posedge i_RST) begin
        if(i_RST) begin //Asynch reset
            s_buffer <= 0; //LSB = 1 to stop enable when in MSB
        end 
        else if(i_EN) begin //if i_EN asserted, shift o_Q left 1 bit, and i_D into LSB
            s_buffer <= {s_buffer[BUFFER_WIDTH - 1: 0], i_D};
        end
    end

    //Assign outputs
    assign o_Q = s_buffer[BUFFER_WIDTH: BUFFER_WIDTH - 1];

endmodule
`default_nettype wire
