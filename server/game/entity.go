package game

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