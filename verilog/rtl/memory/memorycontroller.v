/*
memory control module

Controls both SRAM on chip and ofchip memory

First 
*/
module memorycontroller /*(
//parameter IMPULSE_LENGTH = 15'h00FF,

);*/

    (
    input clk,
    input adc_clock,
    input record,
    //input loop,
    input off_chip_mem,
    input off_chip_mem_ready,
    //input [15:0] delay_reverb,
    //input [15:0] gain,
    input [15:0] impulses,
    input wire [15:0] data_in,
    output reg memory_we,
    //reg [15:0]  curr_adr,
    output [15:0] address_out,
    output [15:0] data_out
    );

    reg [15:0]  head_adr;
    reg [15:0]  tail_adr;

    reg [15:0]  curr_w_adr;

    reg [10:0]  curr_impulse; //max ~500

    reg[31:0] output_buffer; //stores the additions of multiplier and...
    //assign data_out = output_buffer[31:16]; // top 16 bits will become our output



    


    // always @(negedge adc_clock) begin //RESET ON ADC_CLOCK
    //     output_buffer <= 0; //clear buffer

        
    //     if(record == 1'b0) begin //recording inputs
    //         address_out <= curr_adr; //
    //         memory_we <= 1'b1; //set to write to memory
    //     end         
    //     if(curr_adr + 1 == 16'hFFFF) begin
    //         curr_adr <= impulses; //Handle Overflow and go past all impulses
    //     end else begin
    //         curr_adr <= curr_adr + 1;
    //     end
    // end 

/*
if impulse count is 0x10 or 16
_____________________
|0x0 IMPULSES        |
|--------------------|
|0x10 START OF MEMORY|
|                    |
|0xFFFF              |
|____________________|
*/
    reg [15:0]  curr_r_adr;

    //reg [15:0]  offset_adr;
    reg impulse_read;

    reg large_jump;
    reg[5:0] jump_value;
    reg[7:0] impulse_multiplier;
    reg ADC_RESET;
    //wire[15:0] impulse_offset;
    //assign impulse_offset = {5'b00000,top_offset,4'b00,bottom_offset}; //offset from next impulse defined in the current impulse responce
    reg record_buffer;
    always @(posedge clk) begin //clocked

        if(adc_clock == 1'b1) begin //RESET ON ADC_CLOCK
            data_out<= output_buffer[15:0]; //set data_out
            curr_impulse<= 0; //clear impulse counter
            ADC_RESET<=1;

            if(record == 1'b1) begin //recording inputs
                if(record_buffer) begin
                    head_adr <= curr_w_adr;
                    
                end
                address_out <= curr_w_adr; //
                memory_we <= 1'b1; //set to write to memory
                tail_adr <=curr_w_adr;
                record_buffer <= 1'b0;

                //OVERFLOW
                if(curr_w_adr + 1 == 16'hFFFF) begin
                    curr_w_adr <= impulses; //Handle Overflow and go past all impulses
                end
                else begin
                    curr_w_adr <= curr_w_adr + 1;
                end
            end
            else begin
                memory_we <= 1'b0;//dont edit the memory
                record_buffer <= 1'b1;


                
            //OVERFLOW
            if(curr_w_adr + 1 == tail_adr) begin
                curr_w_adr <= head_adr;
            end
            else begin
                curr_w_adr <= curr_w_adr + 1;
            end

            

            end
        end
        else begin

            memory_we <= 1'b0; //always disable write in reading portion of step

            if(ADC_RESET) begin
                output_buffer <=0;
                ADC_RESET<=0;
            end 
            else begin

           


            if(off_chip_mem_ready) begin
                if(impulse_read == 1'b1) begin //if in impulse read
                        address_out <= curr_r_adr;

                        large_jump <= data_in[15];
                        jump_value <= data_in[14:9];

                        //negative = data_in[8];
                        impulse_multiplier <= data_in[7:0];
                        
                        impulse_read<= 1'b0;
                        curr_impulse<= curr_impulse+1; //add one to impulse counter

                    end else begin //read the DATA specified by impulse
                        
                        if(off_chip_mem) begin //using off chip memory
                        
                        end
                        else begin

                        end

                        if(large_jump == 1'b1) begin
                            curr_r_adr <= curr_r_adr + jump_value*(2^6); //check if overflow TODO
                        end
                        else begin
                            curr_r_adr <= curr_r_adr +  {10'b0,jump_value}; //check if overflow TODO
                        end

                        address_out <= {5'b00000,curr_impulse};
                        output_buffer <= output_buffer + data_in*impulse_multiplier;
                        impulse_read <= 1'b1;
                    end
            end
            end
        end //ELSE WHEN NOT ADC CLOCKED
    end //ALWAYS

endmodule
