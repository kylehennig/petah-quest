package game

//This is the file that will hold the entity controllers
func movePlayer(p player, dir byte){
	switch dir {
	case 0: // 0000   north
		p.entity.y--
		break
	case 1: // 0001   east
		p.entity.x++
		break
	case 2: // 0010   south
		p.entity.y++
		break
	case 3: // 0011   west
		p.entity.x--
		break
	}
}
func interactPlayer(p player, dir byte){
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