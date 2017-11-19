package main

import (
	"fmt"

	"github.com/kylehennig/petah-quest/server/game"
)

func main() {
	fmt.Println("hello world")
	connections := make([]game.PlayerConnection, 0)

	ln := game.CreateServer()
	world := game.CreateWorld()

	for {
		game.CheckForNewPlayers(ln, connections)
		game.UpdateWorld(world)
	}
}
