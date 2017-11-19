package game

import (
	"fmt"
	"io/ioutil"
)

func loadMap() WorldMap {
	// Load the map as is from the file.
	dirtyTiles, err := ioutil.ReadFile("../map.txt")
	if err != nil {
		fmt.Println("Error: Could not read the map from disk.")
		panic(err)
	}

	// Calculate the width of the map by finding the first newline.
	width := 0
	for dirtyTiles[width] != '\n' {
		width++
	}

	// Calculate the height of the map by counting the number of newlines.
	height := 0
	for _, tile := range dirtyTiles {
		if tile == '\n' {
			height++
		}
	}

	// Filter all newline characters.
	cleanTiles := make([]byte, 0)
	for _, tile := range dirtyTiles {
		if tile != '\n' {
			cleanTiles = append(cleanTiles, tile)
		}
	}

	fmt.Println(width)
	fmt.Println(height)
	return WorldMap{width, height, cleanTiles}
}
