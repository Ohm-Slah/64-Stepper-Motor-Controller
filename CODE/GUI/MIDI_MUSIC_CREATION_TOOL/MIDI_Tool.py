from tkinter import *
from tkinter import ttk
from mido import MidiFile
import mido
import time

#!https://github.com/vishnubob/python-midi
#https://tkdocs.com/tutorial/firstexample.html

pitches = {
    "B0" : 23,
    "C1" : 24,
    "CS1" : 25,
    "D1" : 26,
    "DS1" : 27,
    "E1" : 28,
    "F1" : 29,
    "FS1" : 30,
    "G1" : 31,
    "GS1" : 32,
    "A1" : 33,
    "AS1" : 34,
    "B1" : 35,
    "C2" : 36,
    "CS2" : 37,
    "D2" : 38,
    "DS2" : 39,
    "E2" : 40,
    "F2" : 41,
    "FS2" : 42,
    "G2" : 43,
    "GS2" : 44,
    "A2" : 45,
    "AS2" : 46,
    "B2" : 47,
    "C3" : 48,
    "CS3" : 49,
    "D3" : 50,
    "DS3" : 51,
    "E3" : 52,
    "F3" : 53,
    "FS3" : 54,
    "G3" : 55,
    "GS3" : 56,
    "A3" : 57,
    "AS3" : 58,
    "B3" : 59,
    "C4" : 60,
    "CS4" : 61,
    "D4" : 62,
    "DS4" : 63,
    "E4" : 64,
    "F4" : 65,
    "FS4" : 66,
    "G4" : 67,
    "GS4" : 68,
    "A4" : 69,
    "AS4" : 70,
    "B4" : 71,
    "C5" : 72,
    "CS5" : 73,
    "D5" : 74,
    "DS5" : 75,
    "E5" : 76,
    "F5" : 77,
    "FS5" : 78,
    "G5" : 79,
    "GS5" : 80,
    "A5" : 81,
    "AS5" : 82,
    "B5" : 83,
    "C6" : 84,
    "CS6" : 85,
    "D6" : 86,
    "DS6" : 87,
    "E6" : 88,
    "F6" : 89,
    "FS6" : 90,
    "G6" : 91,
    "GS6" : 92,
    "A6" : 93,
    "AS6" : 94,
    "B6" : 95,
    "C7" : 96,
    "CS7" : 97,
    "D7" : 98,
    "DS7" : 99,
    "E7" : 100,
    "F7" : 101,
    "FS7" : 102,
    "G7" : 103,
    "GS7" : 104,
    "A7" : 105,
    "AS7" : 106,
    "B7" : 107,
    "C8" : 108,
    "CS8" : 109,
    "D8" : 110,
    "DS8" : 111
}


class Application: 
    def __init__(self, root):
        #tk.Frame.__init__(self, master) 
        #self.grid() 
        self.root = root

        root.title('Motor Music Creation Tool')

        self.motors = []

        self.mainFrame = Frame(root).grid()

        self.motorFrame = Frame(self.mainFrame)
        self.motorFrame.grid(column=2, row=0)

        self.playerFrame = Frame(self.mainFrame, relief=SUNKEN)
        self.playerFrame.grid(column=1, row=0)

        self.createWidgets()

    def createWidgets(self):
        for i in range(8):
            for j in range(8):
                self.motors.append(Button(self.motorFrame, text=str(j+(8*i)+1), command=self.root.destroy, width=10, height=5).grid(column=j, row=i))

        self.canvas = Canvas(self.playerFrame, width=400, height=650, background='gray75', scrollregion=(0, 0, 1000, 1000))
        self.canvas.grid(column=0, row=0, sticky=(N,S))
        self.scrollBarX = Scrollbar(self.mainFrame, orient=HORIZONTAL, command=self.canvas.xview)
        self.scrollBarY = Scrollbar(self.mainFrame, orient=VERTICAL, command=self.canvas.yview)
        self.scrollBarX.grid(column=0, row=1, columnspan=3, sticky="ew")
        self.scrollBarY.grid(column=0, row=0, sticky="ns")

        # link scrollbars to canvas
        self.canvas.config(xscrollcommand=self.scrollBarX.set)
        self.canvas.config(yscrollcommand=self.scrollBarY.set)

        self.canvas.bind("<MouseWheel>", self._on_mousewheel_canvas)

        # Get x-axis width of the canvas
        #print(self.canvas.config()['scrollregion'][-1].split(" ")[2])

        #print(pitches.keys())

        self.snapRegions = []
        for i, pitch in enumerate(pitches):
            x1 = 0
            y1 = int(1000/len(pitches)) * i
            x2 = self.canvas['scrollregion'].split(" ")[2]
            y2 = y1 + 10
            self.snapRegions.append(y1)
            self.canvas.create_rectangle(x1, y1, x2, y2, fill='white' if 'S' not in pitch else 'grey')

    def _on_mousewheel_canvas(self, event):
        #print(event.delta)
        self.canvas.xview_scroll(int(-1*(event.delta/120)), "units")

root = Tk()
Application(root)
#root.geometry('800x700')
#mid = MidiFile("C:\\Users\\34892\OneDrive - Samtec\\Documents\\GitHub\\64-Stepper-Motor-Controller\\CODE\\GUI\\MIDI_MUSIC_CREATION_TOOL\\test.mid")
mid = MidiFile("D:\\Github\\64-Stepper-Motor-Controller\\CODE\\GUI\\MIDI_MUSIC_CREATION_TOOL\\test.mid")

# nothing = input("")
root.resizable(False, False)

currentTime = 0
channels = [{}]*16
print(channels)

for msg in mid:
    if not msg.is_meta and not msg.is_cc():
        try:
            currentTime += msg.time
            print({msg.note: currentTime}, msg.velocity)
            if msg.velocity > 0:
                channels[msg.channel][msg.note] = currentTime
                #pause = input("PAUSE")
                print(channels[msg.channel])
                print("---------------------------------------------------------------------------")
            else:
                print(channels[msg.channel], "\n\n\n\n")
                del channels[msg.channel][msg.note]

                #print(f"Channel {msg.channel}")#: {currentTime-channels[msg.channel]}")
                #channels[msg.channel] = 0
            #print(msg.channel, msg.velocity, msg.time)
            time.sleep(0.1)
        except AttributeError:
            pass

print(channels)
print(currentTime)

#root.mainloop()
