package game

type World struct {
	worldMap WorldMap
	entities []Entity
	players  []Entity
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
