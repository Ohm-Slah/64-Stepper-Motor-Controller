from MIDI import MIDIFile
from sys import argv

def parse(file):
    c=MIDIFile(file)
    c.parse()
    print(str(c))
    for idx, track in enumerate(c[0:100]):
        track.parse()
        print(f'Track {idx}:')
        print(str(track))

parse("C:\\Users\\34892\OneDrive - Samtec\\Documents\\GitHub\\64-Stepper-Motor-Controller\\CODE\\GUI\\VampireKillerCV1.mid")