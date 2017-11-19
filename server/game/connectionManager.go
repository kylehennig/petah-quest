package game

import (
	"net"
	"fmt"
	"time"
)

type PlayerConnection struct {
	player     Entity
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
	newEntity := NewPlayer(b[0])
	newConnection := PlayerConnection{newEntity, conn}
	connections = append(connections, newConnection)
	conn.SetReadDeadline(time.Now().Add(time.Second*5))
	sendMap(conn, GetMap())
	time.Sleep(time.Second)
}

func ListenToPlayers(world World){
	for _, p := range world.players{
		b := readConnection(p.playerCon.connection)[0]
		switch b & 0xF0 {
		case 0x00: // Nothing
			break
		case 0x10: // Move
			movePlayer(p, b & 0x0F)
			// send new player position to all people
			break
		case 0x20: // Interact
			interactPlayer(p, b & 0x0F)
			break
		case 0x30: // Switch Weapons
			p.entity.gameType.weapon = getWeaponByID(b & 0x0F)
			break
		}
	}
}
