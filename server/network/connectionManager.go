package network

import (
	"bufio"
	"net"

	"github.com/kylehennig/petah-quest/server/game"
)

var connections []playerConnection

type playerConnection struct {
	player     game.Entity
	connection net.Conn
}

func CreateServer() net.Listener {
	connections = make([]playerConnection, 0)

	ln, err := net.Listen("tcp", ":8888")
	if err != nil {
		// handle error
	}

	for {
		checkForNewPlayers(ln)
	}

	return ln
}
func checkForNewPlayers(ln net.Listener){
	conn, err := ln.Accept()
	if err != nil {
		// handle error
	}
	go addPlayer(conn)
}

func addPlayer(conn net.Conn) {
	// add a new playerConnection to connection list
	ch, _ := bufio.NewReader(conn).ReadByte()
	newEntity := game.NewPlayer(ch)
	newConnection := playerConnection{newEntity, conn}
	connections = append(connections, newConnection)
	sendMap(conn, game.GetMap())
}
