
import csv

from scipy.io import wavfile
import numpy as np
from scipy.signal import resample

class MemoryController:
    def __init__(self) -> None:

        self.bits = 16;

        self.loop = 0;
        self.impulses = 100;
        self.record = 1;
        self.off_chip_mem = 1;
        self.off_chip_mem_ready = 0;
        self.data_in = 0;
        
        pass
    def step():
        #step one clock cycle given
        pass
    def saveauido(self):
        norm = (self.data.astype(np.float32) / self.maxvalue) * (self.max_data - self.min_data) + self.min_data
        wavfile.write(self.output_file, self.samplerate, norm.astype('int16'))
        
    def createDataFromAudio(self,outputfile,audiofile,impulsefile,samplerate = 10000):
        with open(outputfile, 'w', newline='') as file:
            writer = csv.writer(file)

            #resample data
            samrate, data = wavfile.read(audiofile)
            resample_ratio = float(samplerate) / samrate
            resampled_data = resample(data, int(len(data) * resample_ratio))
            #convert to moono audio
            mono = resampled_data.sum(axis=1) / 2
            min_data = np.min(abs(mono))
            max_data = np.max(abs(mono))
            #normalize
            norm = (mono - min_data) / (max_data - min_data)
            #convert to 16 bit
            maxvalue = 2**(self.bits-1) #2 to the bits power divided by 2 for signed/unsigned
            data = (norm * maxvalue).astype(np.int16)
            
            header = ["Data", "Impulses", "Loop","record","off_chip_mem","off_chip_mem_ready"]
            writer.writerow(header)

            for datum in data:
                #print(datum);
                field = [datum, self.impulses, self.loop,self.record,self.off_chip_mem,self.off_chip_mem_ready];
    
                writer.writerow(field);
            