package game

//This is the file that will hold the entity controllers
func movePlayer(world *World, p *player, dir byte) {
	newX := p.entity.x
	newY := p.entity.y

	switch dir {
	case 0: // 0000   north
		newY--
		break
	case 1: // 0001   east
		newX++
		break
	case 2: // 0010   south
		newY++
		break
	case 3: // 0011   west
		newX--
		break
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

	if !isAboutToCrash {
		// move
		p.entity.x = newX
		p.entity.y = newY
	}
	moveEntity(world, p.entity.id, p.entity.x, p.entity.y)
}
func interactPlayer(world *World, p *player, dir byte) {
	// TODO: add attacking and basically everything
	attackX := p.entity.x
	attackY := p.entity.y
	switch dir {
	case 0: // 0000   north
		attackY--
		break
	case 1: // 0001   east
		attackX++
		break
	case 2: // 0010   south
		attackY++
		break
	case 3: // 0011   west
		attackX--
		break
	}
	for i := len(world.entities); i != 0; i-- {
		e := world.entities[i]
		if e.x == attackX && e.y == attackY {
			e.gameType.health -= p.entity.gameType.weapon.damage
			if e.gameType.health < 0 {
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
