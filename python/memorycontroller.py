
import csv

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

    def createDataFromAudio(self,outputfile,audiofile,impulsefile):

        with open(outputfile+"impulse.csv", 'w', newline='') as file:
            writer = csv.writer(file)
            header = ["value", "multiplier int","Large Jump","Offset Value"]
            writer.writerow(header)

            data = self.convertAudio(impulsefile,10)
            data_list = list(data)
            #start after threshold met
            thresh = 0
            num = 0
            start = next(x[0] for x in enumerate(data_list) if x[1] > thresh)

            while num < start:
                offset = start - num;
                large_jump = 0

                
                if(offset > 2^10):
                    min(round(offset/(2^10)), 7)
                    large_jump = 1

                #add buffer
                field = [, 0, 
                writer.writerow(field);

            while num < len(data):
            #for num in range(len(data)):
                datum = data_list[num];
                #reduce to 8 bit numner
                #datareduced = datum>>8;
                result = datum
                field = [datum, datum,0,4];
                writer.writerow(field);
                #file.write(str(datum)+"\n")
                num+= 4

        with open(outputfile+".csv", 'w', newline='') as file:
            writer = csv.writer(file)
            
            data = self.convertAudio(audiofile,self.bits)
            
            header = ["Data", "Impulses", "Loop","record","off_chip_mem","off_chip_mem_ready"]
            writer.writerow(header)

            for datum in data:
                #print(datum);
                field = [datum, self.impulses, self.loop,self.record,self.off_chip_mem,self.off_chip_mem_ready];
    
                writer.writerow(field);
            