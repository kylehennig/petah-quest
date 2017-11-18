package game

func loadMap() WorldMap {
	var loadedMap WorldMap

	loadedMap.width = 1
	loadedMap.height = 1
	loadedMap.tiles = []byte{0}

	return loadedMap
}
