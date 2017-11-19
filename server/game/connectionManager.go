package game

import (
	"bufio"
	"net"

)

type PlayerConnection struct {
	player     Entity
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
func CheckForNewPlayers(ln net.Listener, connections []PlayerConnection) {
	conn, err := ln.Accept()
	if err != nil {
		// handle error
	}
	go addPlayer(conn, connections)
}

func addPlayer(conn net.Conn, connections []PlayerConnection) {
	// add a new playerConnection to connection list
	ch, _ := bufio.NewReader(conn).ReadByte()
	newEntity := NewPlayer(ch)
	newConnection := PlayerConnection{newEntity, conn}
	connections = append(connections, newConnection)
	sendMap(conn, GetMap())
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

/*

action types
0000 nothing
0001 move
0010 interact
0011 switch weapons

action data
0000   north
0001   east
0010   south
0011   west


*/