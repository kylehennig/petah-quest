package game

import (
	"fmt"
	"net"
	"os"
)

func CreateServer() net.TCPListener {
	service := ":8888"
	tcpAddr, err := net.ResolveTCPAddr("tcp4", service)
	checkError(err)
	listener, err := net.ListenTCP("tcp", tcpAddr)
	checkError(err)

	return *listener
}
func checkError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error: %s", err.Error())
		os.Exit(1)
	}
}

// CheckForNewPlayers allows players to join
func CheckForNewPlayers(ln net.TCPListener, world *World) {
	conn, err := ln.AcceptTCP()
	if err != nil {
		fmt.Println("Failed to accept incoming connection.")
		fmt.Println(err)
	}
	go addPlayer(*conn, world)
	CheckForNewPlayers(ln, world)
}

func addPlayer(conn net.TCPConn, world *World) {

	// add a new playerConnection to connection list
	b := make([]byte, 1)
	conn.Read(b)
	newEntity := NewPlayer(b[0], world)
	newConnection := player{newEntity, conn}

	world.players = append(world.players, newConnection)
	sendMap(conn, world.worldMap)
	conn.Write(Int32ToBytes(newEntity.id))
	sendNewEntity(conn, newEntity.id, newEntity.gameType.drawChar, newEntity.gameType.colour, newEntity.x, newEntity.y)
	sendPlayerHealth(conn, 100)

	for _, entity := range world.entities {
		sendNewEntity(conn, entity.id, entity.gameType.drawChar, entity.gameType.colour, entity.x, entity.y)
	}
	//runTests(conn)
}

func runTests(conn net.TCPConn) {
	sendNewEntity(conn, 0, 'C', COLOUR_RED, 1, 1)
	sendTextMessage(conn, "Text message.")
	sendMoveEntity(conn, 0, 10, 15)
	sendUpdateEntity(conn, 0, 'D', COLOUR_BLU)
	sendPlayerHealth(conn, 10)
	sendActionLocation(conn, 10, 20)
	sendDeleteEntity(conn, 0)
}
func ListenToPlayers(world *World) {
	for i := 0; i < len(world.players); i++  {

		b := readConnection(world.players[i].playerCon)[0]
		switch b & 0xF0 {
		case 0x00: // Nothing
		case 0x10: // Move
			movePlayer(world, &world.players[i], b&0x0F)
		case 0x20: // Interact
			interactPlayer(world, &world.players[i], b&0x0F)
		case 0x30: // Switch Weapons
			world.players[i].entity.gameType.weapon = getWeaponByID(b & 0x0F)
		}
	}

}
