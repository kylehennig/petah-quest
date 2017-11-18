package game


type World struct{
	worldMap WorldMap
	entities []Entity

}

func GetAvailableID() int{
	return 1
}


func CreateWorld() World{
	var myWorld World
	return myWorld
}
