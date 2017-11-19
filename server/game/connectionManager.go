package game

import (
	"fmt"
	"net"
	"os"
)

type PlayerConnection struct {
	player     Entity
	connection net.TCPConn
}

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
func CheckForNewPlayers(ln net.TCPListener, connections []PlayerConnection) {
	conn, err := ln.AcceptTCP()
	if err != nil {
		fmt.Println("Failed to accept incoming connection.")
		fmt.Println(err)
	}
	go addPlayer(*conn, connections)
	CheckForNewPlayers(ln, connections)
}

func addPlayer(conn net.TCPConn, connections []PlayerConnection) {

	// add a new playerConnection to connection list
	b := make([]byte, 1)
	conn.Read(b)
	newEntity := NewPlayer(b[0])
	newConnection := PlayerConnection{newEntity, conn}
	connections = append(connections, newConnection)
	sendMap(conn, GetMap())
	sendPlayerHealth(conn, 100)
	runTests(conn)
}

func runTests(conn net.TCPConn) {
	sendNewEntity(conn, 0, 'C', COLOUR_RED,1,1)
	sendTextMessage(conn, "Text message.")
	sendMoveEntity(conn, 0, 10, 15)
	sendUpdateEntity(conn, 0, 'D', COLOUR_BLU)
	sendPlayerHealth(conn, 10)
	sendActionLocation(conn, 10, 20)
	sendDeleteEntity(conn, 0)
}

func ListenToPlayers(world World) {
	for _, p := range world.players {
		b := readConnection(p.playerCon.connection)[0]
		switch b & 0xF0 {
		case 0x00: // Nothing
			break
		case 0x10: // Move
			movePlayer(p, b&0x0F)
			// send new player position to all people
			break
		case 0x20: // Interact
			interactPlayer(p, b&0x0F)
			break
		case 0x30: // Switch Weapons
			p.entity.gameType.weapon = getWeaponByID(b & 0x0F)
			break
		}
	}
}
