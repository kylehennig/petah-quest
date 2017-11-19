package game

import "fmt"

func moveEntity(world *World, id int32, x int32, y int32) {

	for _, p := range world.players {
		sendMoveEntity(p.playerCon, id, x, y)
		fmt.Print("Moving entity: ")
		fmt.Println(p.entity.id)
	}
}
func deleteEntity(world *World, id int32) {
	for _, p := range world.players {
		sendDeleteEntity(p.playerCon, id)
	}
}
func newEntity(world *World, id int32, character byte, colour byte, x int32, y int32) {
	for _, p := range world.players {
		sendNewEntity(p.playerCon, id, character, colour, x, y)
	}
}
func updateEntity(world *World, id int32, character byte, colour byte) {
	for _, p := range world.players {
		sendUpdateEntity(p.playerCon, id, character, colour)
	}
}
func flashAtPoint(world *World, x int32, y int32) {
	for _, p := range world.players {
		sendActionLocation(p.playerCon, x, y)
	}
}

func updateHealth(p player) {
	sendPlayerHealth(p.playerCon, p.entity.gameType.health)
}

func sendToastToPlayer(p player, msg string) {
	sendTextMessage(p.playerCon, msg)
}
