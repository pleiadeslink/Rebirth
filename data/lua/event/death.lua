stainTileWithBlood(getActorMapX(emitter), getActorMapY(emitter))
if(isPlayer(emitter)) then
    message("You die!")
    updateGamelog()
    gameOver()
else
    message("The " .. getName(emitter) .. " dies.")
    dropLoot(emitter)
    kill(emitter)
end