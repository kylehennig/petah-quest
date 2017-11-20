package main

import (
	"fmt"
	"os"
	"strconv"

	"time"

	"github.com/kylehennig/petah-quest/server/game"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Please specify a port.")
		os.Exit(1)
	}

	// Check that the specified port is valid.
	port, err := strconv.Atoi(os.Args[1])
	if port < 0 || port > 65535 || err != nil {
		fmt.Println("Port should be a number between 0 and 65535.")
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
