package game

import "fmt"

type Projectile struct {
	x          int32
	y          int32
	drawChar   byte
	moveChar   byte
	colour     byte
	speed      uint64
	timePassed uint64
	damage     byte
	id         int32
	killMeNow  bool
}

func (p *Projectile) update(deltaNano uint64, world *World) {

	p.timePassed += deltaNano
	// Move the projectile one tile in the direction it's facing every 1/speed seconds.

	if p.timePassed > 1000000000/p.speed {
		p.timePassed %= 1000000000 / p.speed
		if p.moveChar == '<' {
			p.x--
		} else if p.moveChar == '>' {
			p.x++
		} else if p.moveChar == '^' {
			p.y--
		} else if p.moveChar == 'v' {
			p.y++
		}

		tile := world.worldMap.tiles[p.x+p.y*world.worldMap.width]
		isAboutToCrash := false
		switch tile {
		case '#':
			isAboutToCrash = true
		case 't':
			isAboutToCrash = true
		}


		for i := len(world.entities) - 1; i != 0; i-- {
			if world.entities[i].x == p.x && world.entities[i].y == p.y {
				isAboutToCrash = true
				isDead := false
				if world.entities[i].gameType.health < p.damage {
					isDead = true
					isAboutToCrash = true
				}
				world.entities[i].gameType.health -= p.damage
				fmt.Println(world.entities[i].gameType.health)

				if isDead {
					deleteEntity(world, world.entities[i].id)
					world.entities = append(world.entities[:i], world.entities[i+1:]...)
					isAboutToCrash = true
				}
				isAboutToCrash = true
				isAboutToCrash = true
			}

		}
		if isAboutToCrash {
			p.killMeNow = true
		} else {
			moveEntity(world, p.id, p.x, p.y)
		}

	}

}

func arrow(x int32, y int32, ch byte, world *World, damage int) Projectile {
	return Projectile{x, y, ch, ch,COLOUR_WHT, 5, 0, byte(damage), GetAvailableID(world), false}
}
func AddNinjaStars(x int32, y int32, move byte, world *World, damage int) Projectile {
	return Projectile{x, y, '*', move,COLOUR_WHT, 10, 0, byte(255), GetAvailableID(world), false}
}

func arrowLeft(x int32, y int32, world *World, damage int) Projectile {
	return arrow(x, y, '<', world, damage)
}

func arrowRight(x int32, y int32, world *World, damage int) Projectile {
	return arrow(x, y, '>', world, damage)
}

func arrowUp(x int32, y int32, world *World, damage int) Projectile {
	return arrow(x, y, '^', world, damage)
}

func arrowDown(x int32, y int32, world *World, damage int) Projectile {
	return arrow(x, y, 'v', world, damage)
}

func addArrow(world *World, arrow Projectile) {
	world.projectiles = append(world.projectiles, arrow)
}
