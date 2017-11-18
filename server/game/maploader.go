package game

func loadMap() WorldMap{
	var loadedMap WorldMap

	loadedMap.height = 1
	loadedMap.tiles = []byte{0}
	loadedMap.width = 1

	return loadedMap
}
