package game

type Weapon struct {
	isRanged   bool
	damage     byte
	ammunition int // -1 is infinite
}

func bow() Weapon {
	return Weapon{true, 5, -1}
}

func recurveBow() Weapon {
	return Weapon{true, 25, -1}
}

func sword() Weapon {
	return Weapon{false, 10, -1}
}

func dagger() Weapon {
	return Weapon{false, 5, -1}
}

func ninjaStar() Weapon {
	return Weapon{true, 255, 1}
}

func club() Weapon {
	return Weapon{false, 2, -1}
}

func whip() Weapon {
	return Weapon{false, 20, -1}
}

func fist() Weapon {
	return Weapon{false, 1, -1}
}

func getWeaponByID(id byte) Weapon {
	switch id {
	case 0:
		return bow()
	case 1:
		return recurveBow()
	case 2:
		return sword()
	case 3:
		return dagger()
	case 4:
		return ninjaStar()
	case 5:
		return club()
	case 6:
		return whip()
	case 7:
		return fist()
	default:
		panic("Invalid weapon id.")
	}
}
func getWeaponId(weapon Weapon) int {
	i := 7
	if weapon == fist() {
		i = 7
	} else if weapon == club() {
		i = 5
	} else if weapon == dagger() {
		i = 3
	} else if weapon == sword() {
		i = 2
	} else if weapon == whip() {
		i = 6
	} else if weapon == bow() {
		i = 0
	} else if weapon == recurveBow() {
		i = 1
	} else if weapon == ninjaStar() {
		i = 4
	}
	return i
}
