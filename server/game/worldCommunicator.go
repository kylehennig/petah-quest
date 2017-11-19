package game

func moveEntity(world World, id int32,x int32,y int32){
	for _,p := range world.players{
		sendMoveEntity(p.playerCon.connection, id, x, y)
	}
}
func deleteEntity(world World, id int32){
	for _,p := range world.players{
		sendDeleteEntity(p.playerCon.connection, id)
	}
}
func newEntity(world World, id int32, character byte, colour byte, x int32, y int32){
	for _,p := range world.players{
		sendNewEntity(p.playerCon.connection, id, character, colour, x, y)
	}
}
func updateEntity(world World, id int32, character byte, colour byte){
	for _,p := range world.players{
		sendUpdateEntity(p.playerCon.connection, id,  character, colour)
	}
}
func flashAtPoint(world World, x int32,y int32){
	for _,p := range world.players{
		sendActionLocation(p.playerCon.connection, x, y)
	}
}

func setHealth(p player, health byte){
	sendPlayerHealth(p.playerCon.connection, health)
}

func sendToastToPlayer(p player, msg string){
	sendTextMessage(p.playerCon.connection, msg)
}