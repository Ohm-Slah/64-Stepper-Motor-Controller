from mido import MidiFile

file = "C:\\Users\\34892\OneDrive - Samtec\\Documents\\GitHub\\64-Stepper-Motor-Controller\\CODE\\GUI\\VampireKillerCV1.mid"
mid = MidiFile(file)

for msg in mid:
    #if not msg.is_meta:
    print(msg)