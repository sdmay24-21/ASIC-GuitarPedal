import csv
from math import floor

from scipy.io import wavfile
import numpy as np
from scipy.signal import resample

class MemoryController:
    def __init__(self) -> None:

        self.bits = 16;

        self.loop = 0;
        self.impulses = 1000;
        self.record = 1;
        self.off_chip_mem = 1;
        self.off_chip_mem_ready = 0;
        self.data_in = 0;
        self.samplerate= 10000;
        
        pass
    def step():
        #step one clock cycle given
        pass
    def saveauido(self):
        norm = (self.data.astype(np.float32) / self.maxvalue) * (self.max_data - self.min_data) + self.min_data
        wavfile.write(self.output_file, self.samplerate, norm.astype('int16'))
    def convertAudio(self,audiofile,bits):
        samrate, data = wavfile.read(audiofile)
        resample_ratio = float(self.samplerate) / samrate
        resampled_data = resample(data, int(len(data) * resample_ratio))
        #convert to moono audio
        mono = resampled_data.sum(axis=1) / 2
        min_data = np.min(abs(mono))
        max_data = np.max(abs(mono))
        #normalize
        norm = (mono - min_data) / (max_data - min_data)
        #convert to 16 bit
        maxvalue = 2**(bits-1) #2 to the bits power divided by 2 for signed/unsigned
        data = (norm * maxvalue).astype(np.int16)
        return data;
    
    def calculate_offset_field(large_jump,jump_value,multiplier):
        bits = 15;
        value = (large_jump<<bits)|(jump_value<<bits-(6+1))|(multiplier&0xFF<<0)
        field = [value,"{0:016b}".format(value), large_jump, jump_value,multiplier]

        return field;
    def createDataFromAudio(self,outputfile,audiofile,impulsefile):
        
        
        
        
        #IMPULSE CSV
        time = 0; #time used to create jumps
        with open(outputfile+"impulse.csv", 'w', newline='') as file:
            writer = csv.writer(file)
            #header = ["value", "multiplier int","Large Jump","Offset Value"]
            header = ["value", "binary","large_jump", "jump_value","multiplier"]
            writer.writerow(header)

            data = self.convertAudio(impulsefile,10)
            data_list = list(data)
            #start after threshold met
            thresh = 50
            jump_bits = 6 #there are 6 bits dedicated to jumping
            start_of_impulse = 0;
            impulse_count = 0;
            while(impulse_count <self.impulses and (time+1) <len(data_list) ):
                
                start_of_impulse = next(x[0] for x in enumerate(data_list[time:]) if abs(x[1]) > thresh) #find next value that goes over threshold (but removes delay)
                
                
                #add big jump offsets
                while (start_of_impulse) > pow(2,jump_bits-1):
                    jump_value = floor( (start_of_impulse )/ pow(2,jump_bits));
                    time+= jump_value*pow(2,jump_bits); #add to time
                    
                    start_of_impulse-= jump_value*pow(2,jump_bits); #remove from start
                    
                    large_jump = 1
                    #add buffer
                    field  = MemoryController.calculate_offset_field(large_jump,jump_value,0);
                    
                    writer.writerow(field);
                    impulse_count+=1;
                    
                #add 1 small jump if needed (1 should be all thats needed?)
                #finally add data impulse
                large_jump = 0
                jump_value = start_of_impulse;
                time += start_of_impulse+1; #add to time
                multiplier  = data_list[time];

                field  = MemoryController.calculate_offset_field(large_jump,jump_value,multiplier);
                writer.writerow(field);
                impulse_count+=1;
            # while num < len(data):
            # #for num in range(len(data)):
            #     datum = data_list[num];
            #     #reduce to 8 bit numner
            #     #datareduced = datum>>8;
            #     result = datum
            #     field = [datum, datum,0,4];
            #     writer.writerow(field);
            #     #file.write(str(datum)+"\n")
            #     num+= 4
        
        #AUDIO CSV
        with open(outputfile+".csv", 'w', newline='') as file:
            writer = csv.writer(file)
            
            data = self.convertAudio(audiofile,self.bits)
            
            header = ["Data", "Impulses", "Loop","record","off_chip_mem","off_chip_mem_ready"]
            writer.writerow(header)

            for datum in data:
                #print(datum);
                field = [datum, self.impulses, self.loop,self.record,self.off_chip_mem,self.off_chip_mem_ready];
    
                writer.writerow(field);