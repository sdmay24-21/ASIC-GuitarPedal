import csv
from math import floor
import sys, os, os.path
import numpy as np
from scipy.io import wavfile
from scipy.signal import resample
import pandas as pd


class pedal:
    def __init__(self,input_file,output_file,samplerate = 10000,data_bits= 16,control_bits = 8) -> None:
        
        self.input_file = input_file
        self.data = self.readWavFile(input_file, bits=data_bits,samplerate = samplerate,set=True); #get data from input file
        self.maxvalue = 2**(data_bits-1)
        
        self.output_file = output_file;
        self.samplerate = samplerate
        self.bits = data_bits
        self.control_bits = control_bits

        
        
    def readWavFile(self,filename, bits=16,samplerate=10000,set=False):
        samrate, data = wavfile.read(filename)
        #resample wav data
        resample_ratio = float(samplerate) / samrate
        resampled_data = resample(data, int(len(data) * resample_ratio))
        
        #convert to mono audio
        mono = resampled_data.sum(axis=1) / 2
        pd.DataFrame(data)
        #normalize to 0-1
        min_data = np.min(abs(mono))
        max_data = np.max(abs(mono))
        if(set):
            self.min_data = min_data
            self.max_data = max_data
        norm = (mono - min_data) / (max_data - min_data)
        
        #convert to int using the bit
        maxvalue = 2**(bits-1) #2 to the bits power divided by 2 for signed/unsigned
        data = (norm * maxvalue).astype(np.int16)
        
        return data;
        
    def importOutputFile(self,output):
        self.data = np.int16() #reset data

        with open(output) as file:
            for line in file:
                self.data = np.append(self.data,int(line.rstrip()))
        
    def write(self):
        #convert back to float and un normalize
        norm = (self.result.astype(np.float32) / self.maxvalue) * (self.max_data - self.min_data) + self.min_data
        
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
        self.result = compressedData
        
    def setimpulse(self,input_file):
        self.impulses = self.readWavFile(input_file,bits=8, samplerate=self.samplerate);
        
    def impulse(self,data,num_impulses):
        result = 0
        count = 0
        
        length = min(len(data),num_impulses)
        
        dataRes = np.array(data[:length])
        #impulseRes = np.array(np.flip(self.impulses[:length]))
        impulseRes = np.array(self.impulses[:length])
        result = floor(np.sum(np.multiply(dataRes,impulseRes))/(2**(8-1)))
        return result
    
    def impulseHW(self,data,num_impulses, gain,delay_reverb):
        
        for (impulse,datum) in zip(self.impulses,data):
            count+=1
            if(count>num_impulses):
                return result
            result+= impulse*self.maxvalue*datum
        return result
    
    def FIR(self,number_of_impulses):
        
        data = list(self.data)
        result = list()
        datum = data.pop(0)
        count = 0
        self.number_of_impulses = number_of_impulses
        
        for c in range(len(data)):
            count+=1
            result.append(self.impulse(data, number_of_impulses))
                    
            datum = data.pop(0)
        self.result =  np.array(result)
    def calculate_offset_field(large_jump,jump_value,multiplier):
        bits = 15;
        value = (large_jump<<bits)|(jump_value<<bits-(6+1))|(multiplier&0xFF<<0)
        field = [value,"{0:016b}".format(value), large_jump, jump_value,multiplier]

        return field;
    def createMemTestData(self,outputimpulsefile,outputfile,off_chip_mem=0,record=1):
        #IMPULSE CSV
        time = 0; #time used to create jumps
        with open(outputimpulsefile, 'w', newline='') as file:
            writer = csv.writer(file)
            header = ["value","expected value", "binary","large_jump", "jump_value","multiplier"]
            writer.writerow(header)

            data = self.impulses
            data_list = list(data)
            #start after threshold met
            thresh = 10
            jump_bits = 6 #there are 6 bits dedicated to jumping
            start_of_impulse = 0;
            impulse_count = 0;
            while(impulse_count < len(self.impulses) and (time+1) <len(data_list) ):
                
                #start_of_impulse = next(x[0] for x in enumerate(data_list[time:]) if abs(x[1]) > thresh) #find next value that goes over threshold (but removes delay)
                start_of_impulse = 0;
                
                #add big jump offsets
                large_jump = 1
                while (start_of_impulse) > pow(2,jump_bits-1):
                    jump_value = floor( (start_of_impulse )/ pow(2,jump_bits));
                    time+= jump_value*pow(2,jump_bits); #add to time
                    start_of_impulse-= jump_value*pow(2,jump_bits); #remove from start
                    #add buffer
                    field  = pedal.calculate_offset_field(large_jump,jump_value,0);
                    writer.writerow(field);
                    impulse_count+=1;
                    
                #add 1 small jump if needed (1 should be all thats needed?)
                #finally add data impulse
                large_jump = 0
                jump_value = start_of_impulse;
                time += start_of_impulse+1; #add to time
                multiplier  = data_list[time];

                field  = pedal.calculate_offset_field(large_jump,jump_value,multiplier);
                writer.writerow(field);
                impulse_count+=1;

        #AUDIO CSV
        with open(outputfile, 'w', newline='') as file:
            writer = csv.writer(file)
            data = self.data
            header = ["Expected","Data", "Number of Impulses","record","off_chip_mem"]
            writer.writerow(header)
            for (datum,result) in  zip(data,self.result):
                #print(datum);
                field = [result,datum, self.number_of_impulses,record,off_chip_mem];
                writer.writerow(field);