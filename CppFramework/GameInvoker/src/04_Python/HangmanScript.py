import CGL
import time

# Vars
randomWord = CGL.getRandomWord()
openKeys = [chr(ord('A') + k) for k in range(26)]
playtime = 0
failures = 0
keysLeft = len(randomWord)

# Print
def cgl_print():
    global randomWord, openKeys, playtime, failures, keysLeft

    # Compute time
    timeMin = int(playtime / 60)
    timeSec = int(playtime % 60)

    # -- Print --
    CGL.clearBuffer()

    # Time
    CGL.putString(0, 0, "Playtime: {:02d}:{:02d}".format(timeMin, timeSec))

    # Failures
    CGL.putString(20, 0, "Failures: {}/5".format(failures))

    # Open chars
    CGL.putString(8, 5, (" " * 3).join(openKeys))
    
    # Print word
    str = "Word to guess: "
    for c in randomWord:
        if c in openKeys:
            str = str + "_ "
        else:
            str = str + c + " "
    CGL.putString(10, 10, str)
            

    # -- End Print --
    CGL.present()

# Called every second
def tick():
    global randomWord, openKeys, playtime, failures, keysLeft

    # Check failes
    if failures > 5:
        CGL.clearBuffer();
        CGL.putString(20, 12, "You have LOST")
        CGL.putString(20, 13, "The word was: " + randomWord)
        CGL.present()
        time.sleep(4.0)
        return False

    # Check win
    if keysLeft == 0:
        CGL.clearBuffer();
        CGL.putString(20, 12, "You have WON")
        CGL.putString(20, 13, "The word was: " + randomWord)
        CGL.present()
        time.sleep(4.0)
        return False

    # Update prints
    cgl_print()

    # Increment time
    playtime = playtime + 1

    # Continue game
    return True

# Called when the user presses a key
def keyEvent(key):
    global randomWord, openKeys, playtime, failures, keysLeft

    # Check if key is in list
    if key in openKeys:
        # Replace with space
        openKeys = [k if k != key else ' ' for k in openKeys]
        
        # Count occurance
        numInWord = randomWord.count(key)
        keysLeft = keysLeft - numInWord

        # Increment failures
        if numInWord == 0:
            failures = failures + 1
