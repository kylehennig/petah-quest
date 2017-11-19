package game

import (
	"fmt"
	"net"
	"time"
)

const idLength int = 100000

type World struct {
	worldMap    WorldMap
	players     []player
	entities    []Entity
	projectiles []Projectile
	availableID []bool
}
type player struct {
	entity    Entity
	playerCon net.TCPConn
}

func GetAvailableID(world *World) int32 { // TODO: recycle ID's
	for i := 0; i < idLength; i++ {
		b := world.availableID[i]
		if b {
			world.availableID[i] = false
			fmt.Print("Allocating ID: ")
			fmt.Println(i)
			return int32(i)
		}
	}
	return -1 // TODO: don't limit entity size
}

func CreateWorld() World {
	var myWorld World

	myWorld.availableID = make([]bool, idLength)
	for i := 0; i < idLength; i++ {
		myWorld.availableID[i] = true
	}

	myWorld.worldMap = loadMap()
	for x := int32(0); x < myWorld.worldMap.width; x++ {
		for y := int32(0); y < myWorld.worldMap.height; y++ {
			var entity Entity
			shouldInit := true
			switch myWorld.worldMap.tiles[x+y*myWorld.worldMap.width] {
			case 'g':
				entity.gameType = getTypeByID(GOBLIN)
			case 'w':
				entity.gameType = getTypeByID(WOLF)
			case 'h':
				entity.gameType = getTypeByID(GOBLINBOSS)
			case 'p':
				entity.gameType = getTypeByID(PIRANHAPLANT)
			case 'e':
				entity.gameType = getTypeByID(ELF)
			case 'n':
				entity.gameType = getTypeByID(NINJA)
			case 'b':
				entity.gameType = getTypeByID(FINALBOSS)
			default:
				shouldInit = false
			}
			if shouldInit {
				entity.x = x
				entity.y = y
				entity.id = GetAvailableID(&myWorld)
				newEntity(&myWorld, entity.id, entity.gameType.drawChar, entity.gameType.colour, entity.x, entity.y)
			}
		}
	}
	return myWorld
}

func UpdateWorld(world *World, deltaNano time.Duration) {
	for _, projectile := range world.projectiles {
		projectile.update(deltaNano)
	}
	for _, entities := range world.projectiles {
		entities.update(deltaNano)
	}
}
