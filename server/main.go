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

	startTime := int64(time.Now().Nanosecond())
	for {
		game.ListenToPlayers(&world)
		game.UpdateWorld(&world, uint64(time.Now().Nanosecond()) - uint64(startTime))
		startTime = int64(time.Now().Nanosecond())

	}
}
