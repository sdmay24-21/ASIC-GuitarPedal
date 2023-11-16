import sys, os, os.path
import numpy as np
from scipy.io import wavfile
from scipy.signal import resample
import pandas as pd


class pedal:
    def __init__(self,input_file,output_file,samplerate = 10000,data_bits= 16,control_bits = 8) -> None:
        
        self.input_file = input_file
        self.output_file = output_file
        self.samplerate = samplerate
        self.bits = data_bits
        self.control_bits = control_bits
        #resample data
        samrate, data = wavfile.read(input_file)
        resample_ratio = float(samplerate) / samrate
        resampled_data = resample(data, int(len(data) * resample_ratio))
        #convert to moono audio
        mono = resampled_data.sum(axis=1) / 2
        pd.DataFrame(data)
        
        
        self.min_data = np.min(abs(mono))
        self.max_data = np.max(abs(mono))
        #normalize
        norm = (mono - self.min_data) / (self.max_data - self.min_data)
        #convert to 16 bit
        self.maxvalue = 2**(self.bits-1) #2 to the bits power divided by 2 for signed/unsigned
        self.data = (norm * self.maxvalue).astype(np.int16)
        
        
    def write(self):
        #convert back to float and
        #un normalize
        norm = (self.data.astype(np.float32) / self.maxvalue) * (self.max_data - self.min_data) + self.min_data
        
        wavfile.write(self.output_file, self.samplerate, norm.astype('int16'))
    def compress(elem, thres, slope2,maxvalue):
        #compress code
        slope1 = (1 - (slope2*(1-thres)))/thres
        if(abs(elem) > thres*maxvalue):
            result = elem*slope2 + thres*maxvalue
        else:
            result = elem* slope1
        return result
    
    def compression(self,thres,slope):
        #self.thres = thres
        #self.slope = slope
        vcompress = np.vectorize(pedal.compress)
        compressedData = vcompress(self.data,thres,slope,self.maxvalue)
        self.data = compressedData
        
    def setimpulse(self,input_file):
        #resample data
        samrate, data = wavfile.read(input_file)
        resample_ratio = float(self.samplerate) / samrate
        resampled_data = resample(data, int(len(data) * resample_ratio))
        mono = resampled_data.sum(axis=1) / 2
        self.impulses = mono #TODO bits?
        
    def impulse(self,data,num_impulses, gain,delay_reverb):
        result = 0
        count = 0
        
        length = min(len(data),num_impulses)
        
        dataRes = np.array(data[:length])
        impulseRes = np.array(self.impulses[:length])
        result = np.sum(np.multiply(dataRes,impulseRes*self.maxvalue))
        return result
    
        for (impulse,datum) in zip(self.impulses,data):
            count+=1
            if(count>num_impulses):
                return result
            result+= impulse*self.maxvalue*datum
        return result
    
    def FIR(self,impulses,gain,delay_reverb):
        
        data = list(self.data)
        result = list()
        datum = data.pop(0)
        count = 0
        for c in range(len(data)):
            count+=1
            result.append(self.impulse(data, impulses,gain,delay_reverb))
                    
            datum = data.pop(0)
        self.data =  np.array(result)

