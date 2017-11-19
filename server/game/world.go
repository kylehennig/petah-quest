package game

import (
	"net"
	"time"
)

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

func GetAvailableID(world *World) int32 {
	for i, b := range world.availableID {
		if b {
			return int32(i)
		}
	}
	return -1 // TODO: don't limit entity size
}

func CreateWorld() World {
	var myWorld World

	myWorld.availableID = make([]bool, 10000)
	for i := 0; i < 10000; i++ {
		myWorld.availableID[i] = true
	}

	myWorld.worldMap = loadMap()
	for x := int32(0); x < myWorld.worldMap.width; x++ {
		for y := int32(0); y < myWorld.worldMap.height; y++ {
			var entity Entity
			entity.x = x
			entity.y = y
			entity.id = GetAvailableID(&myWorld)
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
			}
			newEntity(&myWorld, entity.id, entity.gameType.drawChar, entity.gameType.colour, entity.x, entity.y)
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
