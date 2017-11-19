package main

import (
	"fmt"

	"github.com/kylehennig/petah-quest/server/game"
	"time"
)

func main() {
	fmt.Println("hello world")
	connections := make([]game.PlayerConnection, 0)

	ln := game.CreateServer()
	world := game.CreateWorld()

	currentTime := time.Now()
	for {
		game.CheckForNewPlayers(ln, connections)
		game.ListenToPlayers(world)
		game.UpdateWorld(world,time.Now().Sub(currentTime))
		currentTime = time.Now()

	}
}
