package game

type World struct {
	worldMap WorldMap
	entities []Entity
	players  []player
}
type player struct {
	entity Entity
	playerCon PlayerConnection
}

func GetAvailableID() int {
	return 1
}

func CreateWorld() World {
	var myWorld World
	return myWorld
}

func UpdateWorld(world World) {


}
