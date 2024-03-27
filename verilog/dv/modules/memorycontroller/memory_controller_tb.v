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
        .clk(clock),
        .adc_clock(),
        .record(),
        .loop(),
        .off_chip_mem(),
        .off_chip_mem_ready(),
        .delay_reverb(),
        .gain(),
        .impulses(),
        .data_in(),
        .memory_we(),
        .address_out(),
        .data_out()
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
