package game

import (
	"fmt"
	"math"
)

//This is the file that will hold the entity controllers
func movePlayer(world *World, p *player, dir byte) {
	newX := p.entity.x
	newY := p.entity.y

	switch dir {
	case 0: // 0000   north
		newY--
	case 1: // 0001   east
		newX++
	case 2: // 0010   south
		newY++
	case 3: // 0011   west
		newX--
	}
	if newX < world.worldMap.width && newX >= 0 && newY < world.worldMap.height && newY >= 0 {
		tile := world.worldMap.tiles[newX+newY*world.worldMap.width]
		isAboutToCrash := false
		switch tile {
		case 'W':
			isAboutToCrash = true
		case '#':
			isAboutToCrash = true
		case 't':
			isAboutToCrash = true
		}

		for _, e := range world.entities {
			if e.x == newX && e.y == newY {
				isAboutToCrash = true
				break
			}
		}
		for i, e := range world.itemSpawners {
			if e.d.x == newX && e.d.y == newY {
				world.itemSpawners[i].d.isSpawned = false
				p.isWeaponUnlocked[getWeaponId(e.dropItem)] = true
				unlockWeapon(*p, getWeaponId(e.dropItem))
				deleteEntity(world, e.d.id)
				break
			}
		}
		for _, e := range world.players {
			if e.entity.x == newX && e.entity.y == newY {
				isAboutToCrash = true
				break
			}
		}
		if !isAboutToCrash {
			// move
			p.entity.x = newX
			p.entity.y = newY
		}
		moveEntity(world, p.entity.id, p.entity.x, p.entity.y)
		if len(world.players) != 0 {
			for i := 0; i < len(world.entities); i++ {
				MoveToPlayer(&world.entities[i], world.players, world)
			}
		}
	}

}

func interactPlayer(world *World, p *player, dir byte) {
	attackX := p.entity.x
	attackY := p.entity.y
	var ar Projectile
	switch dir {
	case 0: // 0000   north
		attackY--
		ar = arrowUp(p.entity.x, p.entity.y-1, world, int(p.entity.gameType.weapon.damage))
	case 1: // 0001   east
		attackX++
		ar = arrowRight(p.entity.x+1, p.entity.y, world, int(p.entity.gameType.weapon.damage))
	case 2: // 0010   south
		attackY++
		ar = arrowDown(p.entity.x, p.entity.y+1, world, int(p.entity.gameType.weapon.damage))
	case 3: // 0011   west
		attackX--
		ar = arrowLeft(p.entity.x-1, p.entity.y, world, int(p.entity.gameType.weapon.damage))
	}

	if p.isWeaponUnlocked[getWeaponId(p.entity.gameType.weapon)] {

		if p.entity.gameType.weapon.isRanged {
			if p.entity.gameType.weapon.damage == ninjaStar().damage {
				ar = AddNinjaStars(attackX, attackY, ar.moveChar, world, int(p.entity.gameType.weapon.damage))
			}
			addArrow(world, ar)
			newEntity(world, ar.id, ar.drawChar, ar.colour, ar.x, ar.y)
		} else {
			for i := len(world.entities) - 1; i != 0; i-- {
				e := world.entities[i]
				if e.x == attackX && e.y == attackY {
					flashAtPoint(world, e.x, e.y)
					isDead := false
					if world.entities[i].gameType.health < int(p.entity.gameType.weapon.damage) {
						isDead = true
						e.isDead = true
					}
					world.entities[i].gameType.health -= int(p.entity.gameType.weapon.damage)
					fmt.Print("Enemy: ")
					fmt.Println(e.gameType.health)

					if isDead {
						deleteEntity(world, e.id)
						world.entities = append(world.entities[:i], world.entities[i+1:]...)
					}
				}
			}
			for i, e := range world.players {
				if e.entity.x == attackX && e.entity.y == attackY {
					isDead := false
					if e.entity.gameType.health < int(p.entity.gameType.weapon.damage) {
						isDead = true
					}
					world.players[i].entity.gameType.health -= int(p.entity.gameType.weapon.damage)
					flashAtPoint(world, e.entity.x, e.entity.y)

					fmt.Print("Player: ")
					fmt.Println(e.entity.gameType.health)
					if isDead {
						world.players[i].entity.isDead = true
						world.players[i].entity.gameType.health = 0
					}

					updateHealth(e)
				}
			}
		}
	}

}

func MoveToPlayer(e *Entity, p []player, world *World) {
	var closest int
	closest = 0
	manDis := 99999.0 // good enough for now
	for i, pl := range p {

		dis := math.Abs(float64(pl.entity.x)-float64(e.x)) + math.Abs(float64(pl.entity.y)-float64(e.y))
		if dis < float64(manDis) {
			closest = i
			manDis = dis
		}

	}
	dx := p[closest].entity.x - e.x
	dy := p[closest].entity.y - e.y

	adx := dx
	ady := dy

	if dx < 0 {
		adx *= -1
	}
	if dy < 0 {
		ady *= -1
	}

	newX := e.x
	newY := e.y

	if (adx + ady) < 7 {
		if adx > ady {
			if dx > 0 {
				newX++
			} else {
				newX--
			}
		} else {
			if dy > 0 {
				newY++
			} else {
				newY--
			}
		}

		tile := world.worldMap.tiles[newX+newY*world.worldMap.width]
		isAboutToCrash := false
		switch tile {
		case 'W':
			isAboutToCrash = true
		case '#':
			isAboutToCrash = true
		case 't':
			isAboutToCrash = true
		}
		for _, e := range world.entities {
			if e.x == newX && e.y == newY {
				isAboutToCrash = true
			}
		}

		if p[closest].entity.x == newX && p[closest].entity.y == newY {
			isAboutToCrash = true
		}

		if !isAboutToCrash {
			e.x = newX
			e.y = newY
			moveEntity(world, e.id, e.x, e.y)
		}
	}
}
