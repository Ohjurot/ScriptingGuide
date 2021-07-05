import CGL

# Vars
global keepRunning
keepRunning = True

# Print
CGL.clearBuffer()
CGL.putString(0, 0, "The word is " + CGL.getRandomWord())
CGL.present()

# Called every second
def tick():
    global keepRunning
    return keepRunning

# Called when the user presses a key
def keyEvent(key):
    global keepRunning
    if key == 'X':
        keepRunning = False
