package game

import (
	"fmt"
	"net"
)

const (
	SEND_NEW byte = iota
	SEND_DELETE
	SEND_TEXT
	SEND_MOVE
	SEND_UPDATE
	SEND_HEALTH
	SEND_ACTION
)

// sendMap sends the map object to the client
func sendMap(conn net.TCPConn, worldMap WorldMap) {
	//conn.Write(byteToBytes(SEND_MAP))
	fmt.Println(worldMap.width)
	fmt.Println(worldMap.height)
	conn.Write(worldMap.ToBytes())
}

// sendNewEntity sends the new entity to all the clients for rendering
func sendNewEntity(conn net.TCPConn, id int32, character byte, colour byte, x int32, y int32) {
	conn.Write([]byte{SEND_NEW})
	conn.Write(Int32ToBytes(id))
	conn.Write(Int32ToBytes(x))
	conn.Write(Int32ToBytes(y))
	conn.Write([]byte{character, colour})

}

// sendDeleteEntity sends the entity to be deleted from the client
func sendDeleteEntity(conn net.TCPConn, id int32) {
	conn.Write([]byte{SEND_DELETE})

	conn.Write(Int32ToBytes(id))

}

// sendTextMessage sends a 'toast' to the client
func sendTextMessage(conn net.TCPConn, message string) {
	conn.Write([]byte{SEND_TEXT})

	size := len(message)
	b := make([]byte, size+1)

	conn.Write(Int32ToBytes(int32(len(message))))
	for i := 0; i < len(message); i++ {
		b[i] = message[i]
	}
	b[len(message)] = 0
	conn.Write(b)

}

// sendMoveEntity sends an entity to be moved
func sendMoveEntity(conn net.TCPConn, id int32, x int32, y int32) {
	conn.Write([]byte{SEND_MOVE})

	conn.Write(Int32ToBytes(id))
	conn.Write(Int32ToBytes(x))
	conn.Write(Int32ToBytes(y))
}

// sendUpdateEntity sends the entity to update it's display
func sendUpdateEntity(conn net.TCPConn, id int32, character byte, colour byte) {
	conn.Write([]byte{SEND_UPDATE})

	conn.Write(Int32ToBytes(id))
	conn.Write([]byte{character, colour})
}

// sendPlayerHealth sends the player his current health
func sendPlayerHealth(conn net.TCPConn, health byte) {
	conn.Write([]byte{SEND_HEALTH, health})
}

// sendActionLocation sends the client that an action has happened and it should
func sendActionLocation(conn net.TCPConn, x int32, y int32) {
	conn.Write([]byte{SEND_ACTION})

	conn.Write(Int32ToBytes(x))
	conn.Write(Int32ToBytes(y))

}

// readConnection returns 0 if no message, else the message
func readConnection(conn net.TCPConn) []byte {
	var data = make([]byte, 1)
	conn.Read(data)
	return data
}

func Int32ToBytes(n int32) []byte {
	bytes := make([]byte, 4)
	bytes[3] = (byte)((n >> 24) & 0xFF)
	bytes[2] = (byte)((n >> 16) & 0xFF)
	bytes[1] = (byte)((n >> 8) & 0xFF)
	bytes[0] = (byte)(n & 0xFF)
	return bytes
}
