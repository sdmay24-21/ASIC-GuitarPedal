import sys, os, os.path
from scipy.io import wavfile
from scipy.signal import resample
import pandas as pd

#from audio import wavToCSV
from Pedal import pedal


input_filename = "python/audio/test1.wav"

output_filename_compress = "python/audiotests/test1_compress.wav"



# output_filename = "python/audiotests/test0_4bit.wav"
# test0 = pedal(input_filename,output_filename,data_bits= 4) # change
# test0.compression(1,1) 
# test0.write()

# output_filename = "python/audiotests/test1_8bit.wav"
# test1 = pedal(input_filename,output_filename,data_bits= 8) # change
# test1.compression(1,1) 
# test1.write()

# output_filename = "python/audiotests/test2_16bit.wav"
# test2 = pedal(input_filename,output_filename,data_bits= 16) #no change
# test2.compression(1,1) 
# test2.write()
print("start impulse")
output_filename = "python/audiotests/test0_impulse.wav"
impulse_filename = "python/impulses/Rocksta Reactions Fender Twin Reverb SM57 A 2 3 3 45.wav"
test0 = pedal(input_filename,output_filename,data_bits= 16) #no change
test0.setimpulse(impulse_filename)
number_of_impulses= 1000
test0.FIR(number_of_impulses)
test0.write() #gets
test0.createMemTestData("verilog/dv/modules/memorycontroller/testdata/test0impulse.csv","verilog/dv/modules/memorycontroller/testdata/test0.csv")

# print("start impulse2")
# output_filename = "python/audiotests/test4_impulse.wav"
# impulse_filename = "python/impulses/WATER.wav"
# test4 = pedal(input_filename,output_filename,data_bits= 16) #no change
# test4.setimpulse(impulse_filename)
# test4.FIR(10000,1,1) 
# test4.write()

# print("start compression")
# output_filename = "python/audiotests/test5_compression_T0.5_S0.5.wav"
# test4 = pedal(input_filename,output_filename,data_bits= 16) #no change
# test4.setimpulse(impulse_filename)
# test4.compression(1,1)
# test4.write()