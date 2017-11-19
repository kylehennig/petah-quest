package game

import "fmt"

type Projectile struct {
	x          int32
	y          int32
	drawChar   byte
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

	fmt.Println(p.timePassed)

	if p.timePassed > 1000000000/p.speed {
		p.timePassed %= 1000000000/p.speed
		if p.drawChar == '<' {
			p.x--
		} else if p.drawChar == '>' {
			p.x++
		} else if p.drawChar == '^' {
			p.y--
		} else if p.drawChar == 'v' {
			p.y++
		}

		tile := world.worldMap.tiles[p.x+p.y*world.worldMap.width]
		isAboutToCrash := false
		switch tile {
		case 'W':
			isAboutToCrash = true
		case '#':
			isAboutToCrash = true
		case 't':
			isAboutToCrash = true
		}
		if isAboutToCrash{
			p.killMeNow = true
		}
		moveEntity(world, p.id, p.x, p.y)
	}
}

func arrow(x int32, y int32, ch byte, world *World) Projectile {
	return Projectile{x, y, ch, COLOUR_WHT, 5, 0, 5, GetAvailableID(world), false}
}

func arrowLeft(x int32, y int32, world *World) Projectile {
	return arrow(x, y, '<', world)
}

func arrowRight(x int32, y int32, world *World) Projectile {
	return arrow(x, y, '>', world)
}

func arrowUp(x int32, y int32, world *World) Projectile {
	return arrow(x, y, '^', world)
}

func arrowDown(x int32, y int32, world *World) Projectile {
	return arrow(x, y, 'v', world)
}

func addArrow(world *World, arrow Projectile) {
	world.projectiles = append(world.projectiles, arrow)
}
