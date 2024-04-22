from memorycontroller import MemoryController
from pedal import pedal

input_filename = "python/audio/test1.wav"
impulse_filename = "python/impulses/Rocksta Reactions Fender Twin Reverb SM57 A 2 3 3 45.wav"
outputfile = "python/data/memorycontroller"
memCtrlr = MemoryController();
memCtrlr.createDataFromAudio(outputfile,input_filename,impulse_filename,);

# print("start impulse")
# output_filename = "python/audiotests/test3_impulse.wav"
# impulse_filename = "python/impulses/DAMPEDCAVE.wav"
# test3 = pedal(input_filename,output_filename,data_bits= 16) #no change
# test3.setimpulse(impulse_filename)
# test3.FIR(1000,1,1) 
