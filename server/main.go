package main

import (
	"fmt"

	"github.com/kylehennig/petah-quest/server/game"
	"time"
)

func main() {
	fmt.Println("hello world")

	ln := game.CreateServer()
	world := game.CreateWorld()

	go game.CheckForNewPlayers(ln, &world)

	currentTime := time.Now()
	for {
		game.ListenToPlayers(&world)
		game.UpdateWorld(&world, time.Now().Sub(currentTime))
		currentTime = time.Now()

	}
}
