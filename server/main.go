package main

import (
	"fmt"

	"github.com/kylehennig/petah-quest/server/network"
	"github.com/kylehennig/petah-quest/server/game"
)

func main() {
	fmt.Println("hello world")
	ln := network.CreateServer()
	world := game.CreateWorld()
	for {
		network.CheckForNewPlayers(ln)
		game.UpdateWorld(world)
	}
}
