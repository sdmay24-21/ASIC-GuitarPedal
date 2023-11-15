import sys, os, os.path
from scipy.io import wavfile
from scipy.signal import resample
import pandas as pd

#from audio import wavToCSV
from pedal import pedal


input_filename = "python/audio/test1.wav"

output_filename_compress = "python/audiotests/test1_compress.wav"

output_filename = "python/audiotests/test0_4bit.wav"
test0 = pedal(input_filename,output_filename,data_bits= 4) # change
test0.compression(1,1) 
test0.write()

output_filename = "python/audiotests/test1_8bit.wav"
test1 = pedal(input_filename,output_filename,data_bits= 8) # change
test1.compression(1,1) 
test1.write()

output_filename = "python/audiotests/test2_16bit.wav"
test2 = pedal(input_filename,output_filename,data_bits= 16) #no change
test2.compression(1,1) 
test2.write()

print("start impulse")
output_filename = "python/audiotests/test3_impulse.wav"
impulse_filename = "python/impulses/DAMPEDCAVE.wav"
test3 = pedal(input_filename,output_filename,data_bits= 16) #no change
test3.setimpulse(impulse_filename)
test3.FIR(1000,1,1) 
test3.write()

print("start impulse2")
output_filename = "python/audiotests/test4_impulse.wav"
impulse_filename = "python/impulses/WATER.wav"
test4 = pedal(input_filename,output_filename,data_bits= 16) #no change
test4.setimpulse(impulse_filename)
test4.FIR(10000,1,1) 
test4.write()


#output_sample_rate = 10000 #10k
#samrate, data = wavfile.read(input_filename)
#wavData = pd.DataFrame(data)
#resample_ratio = float(output_sample_rate) / samrate
#resampled_data = resample(data, int(len(data) * resample_ratio))
#mono = resampled_data.sum(axis=1) / 2

#wavfile.write(output_filename, output_sample_rate, mono.astype('int16'))


#wavToCSV(file)
#from playsound import playsound
#playsound(output_filename_compress)
#os.system("mpg123 " + output_filename_compress)