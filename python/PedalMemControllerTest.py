import sys, os, os.path
from scipy.io import wavfile
from scipy.signal import resample
import pandas as pd

#from audio import wavToCSV
from Pedal import pedal


input_filename = "python/audio/test1.wav"

output_filename_compress = "python/audiotests/test1_compress.wav"





# print("start impulse")
# output_filename = "python/audiotests/test0_impulse.wav"
# impulse_filename = "python/impulses/Rocksta Reactions Fender Twin Reverb SM57 A 2 3 3 45.wav"
# #impulse_filename = "python/impulses/ emt_140_bright_1emt_140_bright_1.wav";
# test0 = pedal(input_filename,output_filename,data_bits= 16) #no change
# test0.setimpulse(impulse_filename)
# number_of_impulses= 1000
# test0.FIR(number_of_impulses)
# test0.write() #gets
# test0.createMemTestData("verilog/dv/modules/memorycontroller/testdata/test0impulse.csv","verilog/dv/modules/memorycontroller/testdata/test0.csv")

# print("start impulse2")
# output_filename = "python/audiotests/test1_impulse.wav"
# #impulse_filename = "python/impulses/Rocksta Reactions Fender Twin Reverb SM57 A 2 3 3 45.wav"
# impulse_filename = "AKIR_DualSpringer_01.wav";
# impulse_filename= "python/impulses/" + impulse_filename;
# test1 = pedal(input_filename,output_filename,data_bits= 16) #no change
# number_of_impulses= 1000
# test1.setimpulse(impulse_filename,number_of_impulses,gain=0.1)
# test1.FIR()
# test1.write() #gets
# test1.createMemTestData("verilog/dv/modules/memorycontroller/testdata/test1impulse.csv","verilog/dv/modules/memorycontroller/testdata/test1.csv")

# print("start impulse3")
# output_filename = "python/audiotests/test2_impulse.wav"
# #impulse_filename = "python/impulses/Rocksta Reactions Fender Twin Reverb SM57 A 2 3 3 45.wav"
# impulse_filename = "emt_140_bright_1.wav";
# impulse_filename= "python/impulses/" + impulse_filename;
# test1 = pedal(input_filename,output_filename,data_bits= 16) #no change
# number_of_impulses= 1000
# test1.setimpulse(impulse_filename,number_of_impulses,gain=0.1)
# test1.FIR()
# test1.write() #gets
# test1.createMemTestData("verilog/dv/modules/memorycontroller/testdata/test2impulse.csv","verilog/dv/modules/memorycontroller/testdata/test2.csv")


print("start impulse2")
input_filename = "python/audio/sine.wav"
output_filename = "python/audiotests/sinewave_impulse.wav"
#impulse_filename = "python/impulses/Rocksta Reactions Fender Twin Reverb SM57 A 2 3 3 45.wav"
impulse_filename = "emt_140_bright_1.wav";
impulse_filename= "python/impulses/" + impulse_filename;
test1 = pedal(input_filename,data_bits= 16) #no change
test1.write("python/audiotests/sinewave_resampled.wav") #the resampled audio
number_of_impulses= 1000
test1.setimpulse(impulse_filename,number_of_impulses,gain=.1)
test1.FIR()
test1.write(output_filename) #gets
test1.createMemTestData("verilog/dv/modules/memorycontroller/testdata/test3impulse.csv","verilog/dv/modules/memorycontroller/testdata/test3.csv")
