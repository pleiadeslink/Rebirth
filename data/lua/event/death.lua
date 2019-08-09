if(isPlayer(emitter)) then
    message("You die!")
    updateGamelog()
    gameOver()
else
    message("The " .. getName(emitter) .. " dies.")
    kill(emitter)
end