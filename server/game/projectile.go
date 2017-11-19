package game

import (
	"time"
)

type Projectile struct {
	x          int
	y          int
	drawChar   byte
	colour     byte
	speed      byte
	timePassed time.Duration
	damage     byte
}

func (p *Projectile) update(deltaNano time.Duration) {
	p.timePassed += deltaNano
	// Move the projectile one tile in the direction it's facing every 1/speed seconds.
	if p.timePassed.Seconds() > 1/float64(p.speed) {
		p.timePassed = 0
		if p.drawChar == '<' {
			p.x--
		} else if p.drawChar == '>' {
			p.x++
		} else if p.drawChar == '^' {
			p.y--
		} else if p.drawChar == 'v' {
			p.y++
		}
	}
}

func arrow(x int, y int, ch byte) Projectile {
	return Projectile{x, y, ch, COLOUR_WHT, 5, 0, 25}
}

func arrowLeft(x int, y int) Projectile {
	return arrow(x, y, '<')
}

func arrowRight(x int, y int) Projectile {
	return arrow(x, y, '>')
}

func arrowUp(x int, y int) Projectile {
	return arrow(x, y, '^')
}

func arrowDown(x int, y int) Projectile {
	return arrow(x, y, 'v')
}
