from MemoryController import MemoryController


memControl = MemoryController();
outputfile = "python/output/memorycontroller/test1";
audiofile = "python/audio/test1.wav";
impulsefile= "python/impulses/WATER.wav";
memControl.createDataFromAudio(outputfile,audiofile,impulsefile);