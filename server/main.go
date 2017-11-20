package main

import (
	"fmt"
	"os"

	"time"

	"github.com/kylehennig/petah-quest/server/game"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Please specify a port.")
		os.Exit(1)
	}

	fmt.Println("Starting server...")
	ln := game.CreateServer(":" + os.Args[1])
	world := game.CreateWorld()

	go game.CheckForNewPlayers(ln, &world)

	startTime := int64(time.Now().Nanosecond())
	for {
		game.ListenToPlayers(&world)
		game.UpdateWorld(&world, uint64(time.Now().Nanosecond())-uint64(startTime))
		startTime = int64(time.Now().Nanosecond())

	}
}
