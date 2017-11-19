package game

import (
	"fmt"
	"math"
)

//This is the file that will hold the entity controllers
func movePlayer(world *World, p *player, dir byte) {
	newX := p.entity.x
	newY := p.entity.y
	fmt.Print("Moving: ")
	fmt.Println(p.entity.id)

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
			}
		}
		if !isAboutToCrash {
			// move
			p.entity.x = newX
			p.entity.y = newY
		}
		moveEntity(world, p.entity.id, p.entity.x, p.entity.y)
	}

}
func interactPlayer(world *World, p *player, dir byte) {
	// TODO: add attacking and basically everything
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

	if p.entity.gameType.weapon.isRanged {
		addArrow(world, ar)
		newEntity(world, ar.id, ar.drawChar, ar.colour, ar.x, ar.y)
	} else {
		for i := len(world.entities) - 1; i != 0; i-- {
			e := world.entities[i]
			if e.x == attackX && e.y == attackY {
				isDead := false
				if world.entities[i].gameType.health < p.entity.gameType.weapon.damage {
					isDead = true
				}
				world.entities[i].gameType.health -= p.entity.gameType.weapon.damage
				fmt.Println(e.gameType.health)

				if isDead {
					deleteEntity(world, e.id)
					world.entities = append(world.entities[:i], world.entities[i+1:]...)
				}
			}
		}
		for _, e := range world.players {
			if e.entity.x == attackX && e.entity.y == attackY {
				isDead := false
				if e.entity.gameType.health < p.entity.gameType.weapon.damage {
					isDead = true
				}
				e.entity.gameType.health -= p.entity.gameType.weapon.damage
				updateHealth(e)
				if isDead {
					// TODO: disconnect player and remove
				}
			}
		}
	}

}


func MoveToPlayer(e *Entity, p player) {
	dx := p.entity.x - e.x
	dy := p.entity.y - e.y
	if math.Abs(float64(dx)) > math.Abs(float64(dy)) {
		if dx > 0 {
			e.x += 1
		} else {
			e.x -= 1
		}
	} else {
		if dy > 0 {
			e.y += 1
		} else {
			e.y -= 1
		}
	}
}
