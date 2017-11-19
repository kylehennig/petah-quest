package network

import (
	"bufio"
	"net"

	"github.com/kylehennig/petah-quest/server/game"
)


type PlayerConnection struct {
	player     game.Entity
	connection net.Conn
}

func CreateServer() net.Listener {

	ln, err := net.Listen("tcp", ":8888")
	if err != nil {
		// handle error
	}

	return ln
}

// CheckForNewPlayers allows players to join
func CheckForNewPlayers(ln net.Listener, connections []PlayerConnection){
	conn, err := ln.Accept()
	if err != nil {
		// handle error
	}
	go addPlayer(conn, connections)
}

func addPlayer(conn net.Conn, connections []PlayerConnection) {
	// add a new playerConnection to connection list
	ch, _ := bufio.NewReader(conn).ReadByte()
	newEntity := game.NewPlayer(ch)
	newConnection := PlayerConnection{newEntity, conn}
	connections = append(connections, newConnection)
	sendMap(conn, game.GetMap())
}
