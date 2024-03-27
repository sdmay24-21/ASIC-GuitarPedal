from memorycontroller import MemoryController

input_filename = "python/audio/test1.wav"
impulse_filename = "python/impulses/DAMPEDCAVE.wav"
outputfile = "python/data/memorycontroller.csv"
memCtrlr = MemoryController();
memCtrlr.createDataFromAudio(outputfile,input_filename,impulse_filename,);