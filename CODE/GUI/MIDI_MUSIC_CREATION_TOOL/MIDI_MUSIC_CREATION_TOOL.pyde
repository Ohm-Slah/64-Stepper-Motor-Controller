# Stub definitions. Used only to aid in programming. Comment out only when running
#from Processing3 import *

def csv2list(csvString):
    rows = [row.split(",") for row in csvString.split("\n")]
    for i in rows:
        i[-1] = i[-1].replace("\r", "")
    return rows

def setup():
    try:
        f = open("D:/Github/64-Stepper-Motor-Controller/CODE/GUI/example_converted.csv", "rb")
    except:
        f = open("C:/Users/34892/OneDrive - Samtec/Documents/GitHub/64-Stepper-Motor-Controller/CODE/GUI/MIDI_MUSIC_CREATION_TOOL/example_converted.csv", "rb")
    lines = f.read()
    f.close()
    lines = csv2list(lines)

    size(1000,1100)
    stroke(255)
    fill(0)
    background(100,100,100)
    
def draw():
    clear()
    background(100,100,100)
    for i in range(10, 865, 122):
        for j in range(110, 965, 122):
            if (mouseX > i and mouseX < i+117) and (mouseY > j and mouseY < j+117):
                fill(100)
                if mousePressed:
                    fill(255)
            else:
                fill(0)
            rect(i, j, 117, 117, 7)
            
    for i in range(10, 990, 19):
        if (mouseX > i and mouseX < i+18) and (mouseY > 60 and mouseY < 100):
            fill(100)
            if mousePressed:
                fill(255)
        else:
            fill(0)
        rect(i, 60, 18, 40)
        
    for i in range(20, 990, 133):
        rect(i, 20, 15, 40)
        rect(i+19, 20, 15, 40)
        rect(i+57, 20, 15, 40)
        rect(i+76, 20, 15, 40)
        rect(i+95, 20, 15, 40)
