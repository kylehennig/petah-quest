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

	game.CheckForNewPlayers(ln, connections, world)

	currentTime := time.Now()
	for {
		go game.ListenToPlayers(world)
		go game.UpdateWorld(world, time.Now().Sub(currentTime))
		currentTime = time.Now()

	}
}
