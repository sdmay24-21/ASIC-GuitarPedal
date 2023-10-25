import sys, os, os.path
import numpy as np
from scipy.io import wavfile
from scipy.signal import resample
import pandas as pd


class pedal:
    def __init__(self,input_file,output_file,samplerate = 10000) -> None:
        
        self.input_file = input_file
        self.output_file = output_file
        self.samplerate = samplerate
        #resample data
        samrate, data = wavfile.read(input_file)
        wavData = pd.DataFrame(data)
        resample_ratio = float(samplerate) / samrate
        resampled_data = resample(data, int(len(data) * resample_ratio))
        #convert to moono audio
        mono = resampled_data.sum(axis=1) / 2
        pd.DataFrame(data)
        
        
        self.min_data = np.min(abs(mono))
        self.max_data = np.max(abs(mono))
        #normalize
        self.data = (mono - self.min_data) / (self.max_data - self.min_data)
        
    def write(self):
        #un normalize
        output = self.data*(self.max_data - self.min_data) + self.min_data
        wavfile.write(self.output_file, self.samplerate, output.astype('int16'))
    def compress(elem, thres, slope2):
        #compress code
        slope1 = (1 - (slope2*(1-thres)))/thres
        
        if(abs(elem) > thres):
            result = elem*slope2 + thres
        else:
            result = elem* slope1
        return result
    
    def compression(self,thres,slope):
        #self.thres = thres
        #self.slope = slope
        vcompress = np.vectorize(pedal.compress)
        compressedData = vcompress(self.data,thres,slope)
        self.data = compressedData

        