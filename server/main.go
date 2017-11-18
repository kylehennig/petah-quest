package main

import (
	"fmt"

	"github.com/kylehennig/petah-quest/server/network"
)

func main() {
	fmt.Println("hello world")
	ln := network.CreateServer()

	for {
		network.CheckForNewPlayers(ln)
	}

}
