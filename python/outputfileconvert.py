
from pedal import pedal


input_filename = "python/audio/test1.wav"
output_filename = "python/audiotests/test0_VERILOGOUTPUT.wav"
test0 = pedal(input_filename,output_filename,data_bits= 4) # change
test0.readoutputfile("verilog/dv/modules/memorycontroller/output.txt");
test0.write();