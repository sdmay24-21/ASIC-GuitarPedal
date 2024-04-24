from MemoryController import MemoryController


memControl = MemoryController();
outputfile = "python/output/memorycontroller/test1";
audiofile = "python/audio/test1.wav";
impulse_filename = "python/impulses/Rocksta Reactions Fender Twin Reverb SM57 A 2 3 3 45.wav"
memControl.createDataFromAudio(outputfile,audiofile,impulse_filename);