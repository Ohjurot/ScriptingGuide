-- Word to guess
word = getRandomWord()
keyset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
playtime = 0
failures = 0
keysLeft = #word
sleepTimer = nil

-- Print output
function print()
    -- Compute timings
    ptMins = math.floor(playtime / 60)
    ptSecs = playtime % 60

    -- Clear screen
    clearBuffer()

    -- playtime
    putString(0, 0, string.format("Playtime: %02d:%02d", ptMins, ptSecs))
    -- failures
    putString(100, 0, string.format("Failures: %d/5", failures))
    -- keyset
    str = ""
    for c in keyset:gmatch"." do
        str = str .. c .. "   "
    end
    putString(8, 5, str)
    -- Guess the word
    str = "Guessing the Word: "
    for c in word:gmatch"." do
        -- Find in keyset
        eql = false
        for c2 in keyset:gmatch"." do
            if c2 == c then
                eql = true
            end
        end

        -- print
        if eql then
            str = str .. "_ "
        else
            str = str .. c .. " "
        end
    end
    putString(0, 10, str)

    -- Present buffer
    present()
end

-- Key event
function keyEvent(key)
    -- Check key occurance    
    ocInKeySet = false
    for c in keyset:gmatch"." do
        if c == key then ocInKeySet = true end
    end
    
    -- Only when in keyset
    if ocInKeySet then
        -- Count numbers
        ocInWord = 0
        for c in word:gmatch"." do
            if c == key then ocInWord = ocInWord + 1 end
        end

        -- Check case
        if ocInWord > 0 then
            -- Decrement left
            keysLeft = keysLeft - ocInWord
        else
            -- Increment failure
            failures = failures + 1
        end

        -- Remove char
        keyset = keyset:gsub(key, " ")
    end
end

-- Tick Function
function tick()
    -- Check Sleep
    if not (sleepTimer == nil) then
        if sleepTimer > 0 then
            sleepTimer = sleepTimer - 1
            return true
        else
            return false
        end
    end

    -- Increment playtime
    playtime = playtime + 1

    -- Check loss
    if failures > 5 then
        -- Print
        clearBuffer()
        putString(5, 5, "You have LOST!")
        putString(5, 6, "The word was: " .. word)
        present()

        -- Sleep
        sleepTimer = 4

        -- End
        return true
    end

    -- Check  win
    if keysLeft <= 0 then
        -- Print
        clearBuffer()
        putString(5, 5, "You have WON!")
        putString(5, 6, "The word was: " .. word)
        present()
 
        -- Sleep
        sleepTimer = 4
 
        -- End
        return true
    end

    -- Print 
    print()

    -- Keep running
    return true
end
