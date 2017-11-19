package game


const (
	COLOUR_BLK byte = iota
	COLOUR_RED
	COLOUR_GRN
	COLOUR_YLW
	COLOUR_BLU
	COLOUR_MAG
	COLOUR_CYN
	COLOUR_WHT
)

type Entity struct {
	id     int
	x      int
	y      int
	health int

	gameType Type
}

type Type struct {
	drawChar byte
	colour   byte
	health   byte
	speed    byte
	fov      byte
	weapon   Weapon
}

func goblin() Type {
	return Type{'g', COLOUR_GRN, 10, 5, 5, Weapon{false, 10, -1}}
}

func wolf() Type {
	return Type{'w', COLOUR_WHT, 10, 7, 20, Weapon{false, 10, -1}}
}

func goblinBoss() Type {
	return Type{'h', COLOUR_YLW, 100, 3, 5, Weapon{false, 50, -1}}
}

func piranhaPlant() Type {
	return Type{'p', COLOUR_RED, 50, 0, 1, Weapon{false, 50, -1}}
}

func elf() Type {
	return Type{'e', COLOUR_BLU, 120, 5, 20, Weapon{true, 50, -1}}
}

func ninja() Type {
	return Type{'n', COLOUR_BLK, 100, 6, 10, Weapon{false, 75, -1}}
}

func finalBoss() Type {
	// Should have 500 health.
	return Type{'b', COLOUR_YLW, 255, 6, 10, Weapon{false, 100, -1}}
}

func getTypeByID(id byte) Type {
	switch id {
	case 0:
		return goblin()
	case 1:
		return wolf()
	case 2:
		return goblinBoss()
	case 3:
		return piranhaPlant()
	case 4:
		return elf()
	case 5:
		return ninja()
	case 6:
		return finalBoss()
	default:
		panic("Invalid type id.")
	}
}

func NewPlayer(ch byte) Entity {
	playerType := Type{ch, COLOUR_WHT, 100, 5, 255, fist()}
	return Entity{GetAvailableID(), 0, 0, 100, playerType}
}
