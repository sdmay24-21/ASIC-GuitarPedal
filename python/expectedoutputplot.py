import matplotlib.pyplot as plt
import csv
from math import floor
import sys, os, os.path
import numpy as np
from scipy.io import wavfile
from scipy.signal import resample
import pandas as pd
from Pedal import pedal

num = 0;
output = "verilog/dv/modules/memorycontroller/outputs/test" + str(num) +"output.txt"
data = np.int16() #reset data
# output_filename = 
expected_data = pedal.readWavFile(None,"python/audiotests/test0_impulse.wav")

with open(output) as file:
    for line in file:
        data = np.append(data,int(line.rstrip()))
x= range(100);
plt.plot(x,expected_data[:100])
plt.plot(x,data[:100]);
plt.show()
plt.savefig('expected_output_example.png')