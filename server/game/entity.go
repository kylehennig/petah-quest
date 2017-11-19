package game

const(
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
	id int
	x int
	y int
	health int

	gameType Type
}



type Type struct{
	colour byte
	drawChar byte

	weapon Weapon
	speed byte

}

func NewPlayer(ch byte) Entity {
	playerType := Type{COLOUR_WHT, ch,fist() ,5}
	return Entity{GetAvailableID(),0,0, 100, playerType}
}