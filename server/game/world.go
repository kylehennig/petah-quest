package game

import (
	"net"
)

const idLength int = 100000

type World struct {
	worldMap     WorldMap
	players      []player
	entities     []Entity
	itemSpawners []weaponDrop
	projectiles  []Projectile
	availableID  []bool
}
type player struct {
	entity           Entity
	playerCon        net.TCPConn
	isWeaponUnlocked [8]bool
}

func GetAvailableID(world *World) int32 { // TODO: recycle ID's
	for i := 0; i < idLength; i++ {
		b := world.availableID[i]
		if b {
			world.availableID[i] = false
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
			switch myWorld.worldMap.tiles[x+y*myWorld.worldMap.width] {
			case 'g':
				myWorld.entities = append(myWorld.entities, createEntityToken(&myWorld, goblin(), x, y))
			case 'w':
				myWorld.entities = append(myWorld.entities, createEntityToken(&myWorld, wolf(), x, y))
			case 'h':
				myWorld.entities = append(myWorld.entities, createEntityToken(&myWorld, goblinBoss(), x, y))
			case 'p':
				myWorld.entities = append(myWorld.entities, createEntityToken(&myWorld, piranhaPlant(), x, y))
			case 'e':
				myWorld.entities = append(myWorld.entities, createEntityToken(&myWorld, elf(), x, y))
			case 'n':
				myWorld.entities = append(myWorld.entities, createEntityToken(&myWorld, ninja(), x, y))
			case 'b':
				myWorld.entities = append(myWorld.entities, createEntityToken(&myWorld, finalBoss(), x, y))
			case ')':
				myWorld.itemSpawners = append(myWorld.itemSpawners, weaponDrop{getDropDefault(')', x, y, &myWorld), bow()})
			case '}':
				myWorld.itemSpawners = append(myWorld.itemSpawners, weaponDrop{getDropDefault('}', x, y, &myWorld), recurveBow()})
			case '/':
				myWorld.itemSpawners = append(myWorld.itemSpawners, weaponDrop{getDropDefault('/', x, y, &myWorld), sword()})
			case '-':
				myWorld.itemSpawners = append(myWorld.itemSpawners, weaponDrop{getDropDefault('-', x, y, &myWorld), dagger()})
			case '*':
				myWorld.itemSpawners = append(myWorld.itemSpawners, weaponDrop{getDropDefault('*', x, y, &myWorld), ninjaStar()})
			case '@':
				myWorld.itemSpawners = append(myWorld.itemSpawners, weaponDrop{getDropDefault('@', x, y, &myWorld), whip()})
			case '!':
				myWorld.itemSpawners = append(myWorld.itemSpawners, weaponDrop{getDropDefault('!', x, y, &myWorld), club()})
			}

		}
	}
	return myWorld
}

func UpdateWorld(world *World, deltaNano uint64) {
	for i := len(world.projectiles) - 1; i >= 0; i-- {
		if world.projectiles[i].killMeNow {
			deleteEntity(world, world.projectiles[i].id)
			world.projectiles = append(world.projectiles[:i], world.projectiles[i+1:]...)
		} else {
			world.projectiles[i].update(deltaNano, world)
		}
	}
	for i, s := range world.itemSpawners {
		if world.itemSpawners[i].spawn() {
			newEntity(world, s.d.id, s.d.drawChar, COLOUR_YLW, s.d.x, s.d.y)
		}
	}

}
