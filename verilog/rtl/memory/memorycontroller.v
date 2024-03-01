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

    reg [10:0]  curr_impulse; //max ~500

    reg[31:0] output_buffer; //stores the additions of multiplier and ...
    assign data_out = output_buffer[31:16]; // top 16 bits will become our output



    always @(posedge adc_clock) begin //RESET ON ADC_CLOCK

        curr_impulse<= 0; //clear impulse counter

        if(record == 1'b0) begin //recording inputs
            address_out <= curr_adr; //
            memory_we <= 1'b1; //set to write to memory
        end 

        if(curr_adr + 1 == 16'hFFFF) begin
            curr_adr <= impulses; //Handle Overflow and go past all impulses
        end else begin
            r <= curr_adr + 1;
        end
    end 


    always @(negedge adc_clock) begin //RESET ON ADC_CLOCK
        output_buffer <= 0; //clear buffer

        
        if(record == 1'b0) begin //recording inputs
            address_out <= curr_adr; //
            memory_we <= 1'b1; //set to write to memory
        end         
        if(curr_adr + 1 == 16'hFFFF) begin
            curr_adr <= impulses; //Handle Overflow and go past all impulses
        end else begin
            r <= curr_adr + 1;
        end
    end 


    reg [15:0]  curr_r_adr;
    reg [15:0]  offset_adr;
    reg impulse_read;

    reg[2:0] top_offset;
    reg[2:0] bottom_offset;

    wire[15:0] impulse_offset;
    assign impulse_offset = {5'b00000,top_offset,4'b00,bottom_offset}; //offset from next impulse defined in the current impulse responce

    always @((posedge clk & not adc_clock) or negedge adc_clock) begin //after adc clock 

        memory_we <= 1'b0; //always disable write in reading portion
        if(off_chip_mem) begin //using off chip memory
            if(off_chip_mem_ready) begin
            
                if(impulse_read == 1'b1) begin //if in impulse read
                    
                    address_out <= curr_impulse;

                    impulse_read<= 1'b0;
                end else begin

                    address_out <= curr_w_adr - offset_adr;

                    impulse_read<= 1'b1;
                end
            
            end
        end else begin //Using on chip memory

            if(impulse_read == 1'b1) begin //if in impulse read
                    
                    address_out <= offset_adr;

                    impulse_read<= 1'b0;
                end else begin
                    curr_r_adr <= curr_r_adr + impulse_offset; //check if overflow
                    address_out <= curr_r_adr;

                    impulse_read<= 1'b1;
                end
            

        end
    end 




endmodule