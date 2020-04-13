# program to find, slice and convert mp3 to wav
# in current working directory
# multiple snippets and random start optional
from pydub import AudioSegment
# use "pip3 install pydub" or "conda install -c conda-forge pydub"
# if you're working with conda environments
import os
import random

def find_and_convert_one(filename, start = 0, duration = 30, random_begin = False, snippets_per_song=3):
    if not filename.endswith(".mp3"):
        filename = filename + ".mp3"

    song = AudioSegment.from_mp3(os.getcwd() + "\\" + filename)

    if random_begin:
        max_start = len(song) - duration * 1000  # ms before song stops
        for i in range(snippets_per_song):
            start = random.randint(0, max_start)
            extract = song[start:start + duration*1000]
            extract.export("extract-" + filename[0:-4] + str(i) + ".wav", format="wav")
            print("snippet saved as: " + "extract-" + filename[0:-4] + str(i) + ".wav")
    else:
        extract = song[start:start + duration * 1000]
        extract.export(filename[0:-4] + ".wav", format="wav")
        print("WAV saved as: " + filename[0:-4] + ".wav")
        

if __name__ == "__main__":
    find_and_convert_one(filename="*.mp3", start=0, duration=20)
