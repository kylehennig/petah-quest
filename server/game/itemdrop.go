package game

import (
	"fmt"
	"time"
)

type spawner interface {
	spawn() bool
}
type drop struct {
	drawChar               byte
	coolDownInMilliseconds int
	lastTimeNano           int64
	isSpawned              bool
	id                     int32
	x                      int32
	y                      int32
}

type weaponDrop struct {
	d        drop
	dropItem Weapon
}

type armourDrop struct {
	d drop
}

func (d *drop) shouldSpawn() bool {
	if !d.isSpawned {
		fmt.Print("time: ")
		fmt.Print(time.Now().UnixNano() - d.lastTimeNano)
		fmt.Print(" ")
		fmt.Println(d.coolDownInMilliseconds * 1000000)
		if time.Now().UnixNano()-d.lastTimeNano > int64(d.coolDownInMilliseconds*1000000) {
			d.lastTimeNano = time.Now().UnixNano()
			d.isSpawned = true
			return true
		}
	}
	return false
}
func (p *weaponDrop) spawn() bool {
	if p.d.shouldSpawn() {

		return true
	}
	return false

}
func (p *armourDrop) spawn() bool {
	if p.d.shouldSpawn() {
		return true
	}
	return false

}
func getDropDefault(drawChar byte, x int32, y int32, world *World) drop {
	return drop{drawChar, 5 * 1000, 0, false, GetAvailableID(world), x, y}
}
