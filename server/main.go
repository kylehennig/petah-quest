package main

import (
	"fmt"

	"github.com/kylehennig/petah-quest/server/network"
)

func main() {
	fmt.Println("hello world")
	ln := network.CreateServer()
	world := CreateWorld()
	for {
		network.CheckForNewPlayers(ln)
	}

}
