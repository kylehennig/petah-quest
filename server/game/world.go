package game

import "github.com/kylehennig/petah-quest/server/network"

type World struct{
	worldMap WorldMap
	entities []Entity
	players []Entity

}

func GetAvailableID() int{
	return 1
}


func CreateWorld() World{
	var myWorld World
	return myWorld
}

func UpdateWorld(world World){

}
type Player struct {
	gameObject Entity
	connectionObject network.Connection
}