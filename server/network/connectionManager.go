package network

import (
	"github.com/kylehennig/petah-quest/server/game"
	"net"
	"bufio"
)

var connections []playerConnection

type playerConnection struct{
	player game.Entity
	connection net.Conn
}

func CreateServer(){
	connections = make([]playerConnection, 0)

	ln, err := net.Listen("tcp", ":8888")
	if err != nil {
		// handle error
	}
	for {
		conn, err := ln.Accept()
		if err != nil {
			// handle error
		}
		go addPlayer(conn)
	}
}

func addPlayer(conn net.Conn){
// add a new playerConnection to connection list
	ch, _ := bufio.NewReader(conn).ReadByte()
	newEntity := game.NewPlayer(ch)
	newConnection := playerConnection{newEntity, conn}
	connections = append(connections, newConnection)
	bufio.NewWriter(conn).Write(game.GetMap().ToBytes())
}
