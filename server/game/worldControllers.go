package game

//This is the file that will hold the entity controllers
func movePlayer(world World, p player, dir byte) {
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
	tile := world.worldMap.tiles[newX + newY * world.worldMap.width]
	isAboutToCrash := false
	switch tile {
	case 'W':
		isAboutToCrash = true
	case '#':
		isAboutToCrash = true
	case 't':
		isAboutToCrash = true
	}

	if !isAboutToCrash{
		// move
		p.entity.x = newX
		p.entity.y = newY
	}
	moveEntity(world, p.entity.id, p.entity.x, p.entity.y)
}
func interactPlayer(p player, dir byte) {
	// TODO: add attacking and basically everything
	switch dir {
	case 0: // 0000   north

		break
	case 1: // 0001   east

		break
	case 2: // 0010   south

		break
	case 3: // 0011   west

		break
	}
}
