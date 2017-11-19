package network

import (
	"fmt"
	"net"

	"github.com/kylehennig/petah-quest/server/game"
	"time"
)

type PlayerConnection struct {
	player     game.Entity
	connection net.Conn
}

func CreateServer() net.Listener {

	ln, err := net.Listen("tcp", ":8888")
	if err != nil {
		fmt.Println("Error listening on port 8888.")
		fmt.Println(err)
	}

	return ln
}

// CheckForNewPlayers allows players to join
func CheckForNewPlayers(ln net.Listener, connections []PlayerConnection) {
	conn, err := ln.Accept()
	if err != nil {
		fmt.Println("Failed to accept incoming connection.")
		fmt.Println(err)
	}
	go addPlayer(conn, connections)
}

func addPlayer(conn net.Conn, connections []PlayerConnection) {
	// add a new playerConnection to connection list
	b := make([]byte, 1)
	conn.Read(b)
	newEntity := game.NewPlayer(b[0])
	newConnection := PlayerConnection{newEntity, conn}
	connections = append(connections, newConnection)
	sendMap(conn, game.GetMap())
	conn.SetReadDeadline(time.Now().Add(time.Second*5))
	fmt.Println(readConnection(conn))
	sendPlayerHealth(conn, 65)
}
