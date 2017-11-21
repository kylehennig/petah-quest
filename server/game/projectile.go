package game


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
	// Move the projectile one tile in the direction it's facing if enough time has lapsed.
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

		// Check if the projectile has exited the world.
		if p.x < 0 || p.x >= world.worldMap.width || p.y < 0 || p.y >= world.worldMap.height {
			p.killMeNow = true
			return
		}
		// Check if the projectile is about to crash into a solid tile.
		tile := world.worldMap.tiles[p.x+p.y*world.worldMap.width]
		isAboutToCrash := false
		switch tile {
		case '#':
			isAboutToCrash = true
		case 't':
			isAboutToCrash = true
		}
		// Check if the projectile is about to crash into an entity.
		for i := 0; i < len(world.entities); i++ {
			entity := world.entities[i]
			if p.x == entity.x && p.y == entity.y {
				isAboutToCrash = true
				// Damage the entity.
				if entity.gameType.health <= int(p.damage) {
					deleteEntity(world, entity.id)
					world.entities = append(world.entities[:i], world.entities[i+1:]...)
				} else {
					entity.gameType.health -= int(p.damage)
				}
			}
		}
		for i,pl := range world.players{
			if p.x == pl.entity.x && p.y == pl.entity.y {
				isAboutToCrash = true
				// Damage the entity.
				if world.players[i].entity.gameType.health <= int(p.damage) {
					world.players[i].entity.isDead = true
				} else {
					world.players[i].entity.gameType.health -= int(p.damage)
				}
				updateHealth(world.players[i])
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
	return Projectile{x, y, ch, ch, COLOUR_WHT, 10, 0, byte(damage), GetAvailableID(world), false}
}
func AddNinjaStars(x int32, y int32, move byte, world *World, damage int) Projectile {
	return Projectile{x, y, '*', move, COLOUR_WHT, 15, 0, byte(255), GetAvailableID(world), false}
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
