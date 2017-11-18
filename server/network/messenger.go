package network

import (
	"net"
	"github.com/kylehennig/petah-quest/server/game"
)

// sendMap sends the map object to the client
func sendMap(conn net.Conn, worldMap game.WorldMap){
	conn.Write(worldMap.ToBytes())
}
// sendNewEntity sends the new entity to all the clients for rendering
func sendNewEntity(conn net.Conn, id int32, character byte, colour byte){
	conn.Write(int32ToBytes(id))
	conn.Write(byteToBytes(colour))
	conn.Write(byteToBytes(character))
}

// sendDeleteEntity sends the entity to be deleted from the client
func sendDeleteEntity(conn net.Conn, id int32){
	conn.Write(int32ToBytes(id))

}

// sendTextMessage sends a 'toast' to the client
func sendTextMessage(conn net.Conn, message string){
	conn.Write(int32ToBytes(int32(len(message))))
	for i := 0; i < len(message); i++ {
		conn.Write(byteToBytes(message[i]))
	}
	conn.Write(byteToBytes(0))
}

// sendMoveEntity sends an entity to be moved
func sendMoveEntity(conn net.Conn, id int32, x int32, y int32){
	conn.Write(int32ToBytes(id))
	conn.Write(int32ToBytes(x))
	conn.Write(int32ToBytes(y))
}

// sendUpdateEntity sends the entity to update it's display
func sendUpdateEntity(conn net.Conn, id int32, colour byte, character byte, ){
	conn.Write(int32ToBytes(id))
	conn.Write(byteToBytes(colour))
	conn.Write(byteToBytes(character))
}

// sendPlayerHealth sends the player his current health
func sendPlayerHealth(conn net.Conn, health byte){
	conn.Write(byteToBytes(health))
}

// sendActionLocation sends the client that an action has happened and it should
func sendActionLocation(conn net.Conn, x int32, y int32){
	conn.Write(int32ToBytes(x))
	conn.Write(int32ToBytes(y))

}

// readConnection returns 0 if no message, else the message
func readConnection(conn net.Conn) []byte{
	var data []byte
	conn.Read(data)
	return data
}

func byteToBytes(b byte) []byte {
	bytes := make([]byte, 1)
	bytes[0] = b
	return bytes
}

func int32ToBytes(n int32) []byte {
	bytes := make([]byte, 4)
	bytes[0] = (byte) ((n >> 24) & 0xFF)
	bytes[1] = (byte) ((n >> 16) & 0xFF)
	bytes[2] = (byte) ((n >> 8) & 0xFF)
	bytes[3] = (byte) (n & 0xFF)
	return bytes
}