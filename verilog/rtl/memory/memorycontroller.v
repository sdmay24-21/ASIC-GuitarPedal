/*
memory control module

Controls both SRAM on chip and ofchip memory

First 
*/
module memorycontroller (
parameter IMPULSE_LENGTH = 15'h00FF,

)(
    input clk,
    input adc_clock,
    input record,
    input loop,
    input off_chip_mem,
    input off_chip_mem_ready,
    input [15:0] delay_reverb,
    input [15:0] gain,
    input [15:0] impulses,
    input [15:0] data_in,
    output memory_we;
    output [15:0] address_out,
    output [15:0] data_out
    );

    reg [15:0]  head_adr;
    reg [15:0]  tail_adr;

    reg [15:0]  curr_w_adr;

    always @(posedge adc_clock) begin
        if(record == 1'b0) begin //recording inputs
            address_out <= curr_adr; //
            memory_we <= 1'b1; //set to write to memory
        end 
        
        
        if(curr_adr + 1 == 16'hFFFF) begin
            curr_adr <= IMPULSE_LENGTH; //Handle Overflow
        end else begin
            r <= curr_adr + 1;
        end
    end 


    reg [15:0]  curr_r_adr;
    reg [15:0]  offset_adr;
    reg impulse_read;
    always @((posedge clk & not adc_clock) or negedge adc_clock) begin //after adc clock 

        memory_we <= 1'b0; //always disable write in reading portion

        if(off_chip_mem_ready) begin
        
            if(impulse_read == 1'b1) begin //if in impulse read
                
                address_out <= offset_adr;

                impulse_read<= 1'b0;
            end else begin

                address_out <= curr_w_adr - offset_adr;

                impulse_read<= 1'b1;
            end
        
        end
    end 




endmodule