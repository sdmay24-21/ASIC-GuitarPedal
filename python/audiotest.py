import sys, os, os.path
from scipy.io import wavfile
from scipy.signal import resample
import pandas as pd

#from audio import wavToCSV
from pedal import pedal
input_filename = "python/audio/test1.wav"
output_filename = "python/audiotests/test1_resampled.wav"
output_filename_compress = "python/audiotests/test1_compress.wav"


test1 = pedal(input_filename,output_filename_compress)
test1.compression(.5,0)
test1.write()

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