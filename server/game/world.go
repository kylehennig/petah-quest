package game

import "time"

type World struct {
	worldMap    WorldMap
	players     []player
	entities    []Entity
	projectiles []Projectile
}
type player struct {
	entity    Entity
	playerCon PlayerConnection
}

func GetAvailableID() int {
	return 1
}

func CreateWorld() World {
	var myWorld World
	return myWorld
}

func UpdateWorld(world World, deltaNano time.Duration) {
	for _, projectile := range world.projectiles {
		projectile.update(deltaNano)
	}
}
