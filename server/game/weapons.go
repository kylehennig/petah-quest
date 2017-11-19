package game

type Weapon struct {
	isRanged   bool
	damage     byte
	ammunition int // -1 is infinite
}

func fist() Weapon {
	return Weapon{false, 1, -1}
}
