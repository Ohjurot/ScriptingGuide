-- Word to guess
word = getRandomWord()
keepRunning = true

-- Clear and print word
clearBuffer()
putString(0, 0, "The word is " .. word)
present()

-- Key event
function keyEvent(key)
    if key == "X" then
        keepRunning = false
    end
end

-- Tick Function
function tick()
    return keepRunning
end
