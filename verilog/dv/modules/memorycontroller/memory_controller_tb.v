/*
TOP LEVEL TESTING LEVEL 3
USES MCU FOR CONTROL
USES SPI TO COMMUNICATE

*/

`timescale 1 ns / 1 ps

module memory_controller_tb;

    reg clock;
    reg RSTB;
    reg CSB;


    always #15 clock <= (clock === 1'b0);

    reg record;
    reg loop;
    reg off_chip_mem;
    reg delay_reverb;
    reg [7:0] gain;
    reg [7:0] impulses;
    reg [7:0] thres;
    reg [7:0] slope;
    reg mem_to_comp;

    // Instantiate the pedal_top module with internal values set to regs
    memorycontroller uut (
    .wb_clk_i(wb_clk_i),
    .wb_rst_i(wb_rst_i),
    .wbs_stb_i(wbs_stb_i),
    .wbs_cyc_i(wbs_cyc_i),
    .wbs_we_i(wbs_we_i),
    .wbs_sel_i(wbs_sel_i),
    .wbs_dat_i(wbs_dat_i),
    .wbs_adr_i(wbs_adr_i),
    .wbs_ack_o(wbs_ack_o),
    .wbs_dat_o(wbs_dat_o),
    .la_data_in(la_data_in),
    .la_data_out(la_data_out),
    .la_oenb(la_oenb),
    .io_in(0), // Provide suitable values for other inputs
    .io_out(0), // Provide suitable values for other outputs
    .io_oeb(0),  // Provide suitable values for other outputs
    
    //set CLK?
    .clk(clk),
    );





    initial begin
        clock = 0;
    end
    file1=$fopen("te.csv","r");

    r = $fscanf(file1,"%d, %d, %d, %d", t[i], s1[i], s2[i], s3[i] );
    for (i=0; i<2^16; i=i+1) begin
        r = $fscanf(file1,"%d, %d, %d, %d", t[i], s1[i], s2[i], s3[i] );
    end

    $fclose(file1);
    

    function load_data();

    endfunction

    initial begin
    $display("Starting...");
    #20

    reg [255:0] filename; // Assuming maximum file path length of 256 characters
    reg [31:0] filehandle;

    // Specify the directory path where your files are located
    filename = "test_data/*.csv"; // Use the appropriate directory path and file extension
    
    // Open and read files in the specified directory
    filehandle = $fopen(filename, "r");
    
    if (filehandle == 0) begin
      $display("Error: Unable to open file.");
    end else begin
        r = $fscanf(file1,"%d, %d, %d, %d", t[i], s1[i], s2[i], s3[i] );
        while(r) begin //continue until r is blank

            r = $fscanf(file1,"%d, %d, %d, %d", t[i], s1[i], s2[i], s3[i] );
        end

      
      // Close the file after reading
      $fclose(filehandle);
    end
    end
    
    $display("Simulation finished... ");

endmodule
