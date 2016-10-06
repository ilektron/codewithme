package main

import (
	"fmt"
)

type Point struct {
	x, y int
}

func (p *Point) IsMonkeyable() bool {
	sum := 0
	x := p.x
	if x < 0 {
		x = -x
	}
	y := p.y
	if y < 0 {
		y = -y
	}
	for (sum <= 19) && (x > 0 || y > 0) {
		sum += x % 10
		sum += y % 10
		x = x / 10
		y = y / 10
	}
	return sum <= 19
}

func check_point(p Point, search []Point, visited map[Point]Point) ([]Point, map[Point]Point) {
	if p.IsMonkeyable() {
		_, exists := visited[p]
		if !exists {
			search = append(search, p)
			visited[p] = p
		}
	}
	return search, visited
}

func main() {
	start := Point{0, 0}
	points := map[Point]Point{start: start}
	search := make([]Point, 0, 4096)
	search = append(search, start)
	for len(search) > 0 {
		p := search[len(search)-1]
		search = search[:len(search)-1]
		// Check above
		search, points = check_point(Point{p.x, p.y + 1}, search, points)
		// Check right
		search, points = check_point(Point{p.x + 1, p.y}, search, points)
		// Check below
		search, points = check_point(Point{p.x, p.y - 1}, search, points)
		// Check left
		search, points = check_point(Point{p.x - 1, p.y}, search, points)
	}
	fmt.Println(len(points))
}
