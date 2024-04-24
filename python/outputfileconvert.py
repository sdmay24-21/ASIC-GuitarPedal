
from pedal import pedal
input_filename = "python/audio/test1.wav"

num = 0
output_filename = "python/audiotests/test"+ str(num)+"_VERILOGOUTPUT.wav"
test0 = pedal(input_filename,output_filename,data_bits= 4) # change
test0.readoutputfile("verilog/dv/modules/memorycontroller/outputs/test" + str(num) +"output.txt");
test0.write();

num = 1
output_filename = "python/audiotests/test"+str(num)+"_VERILOGOUTPUT.wav"
test0 = pedal(input_filename,output_filename,data_bits= 4) # change
test0.readoutputfile("verilog/dv/modules/memorycontroller/outputs/test" + str(num) +"output.txt");
test0.write();

num = 2
output_filename = "python/audiotests/test"+str(num)+"_VERILOGOUTPUT.wav"
test0 = pedal(input_filename,output_filename,data_bits= 4) # change
test0.readoutputfile("verilog/dv/modules/memorycontroller/outputs/test" + str(num) +"output.txt");
test0.write();