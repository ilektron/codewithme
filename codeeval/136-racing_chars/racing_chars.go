package main

import "fmt"
import "log"
import "bufio"
import "os"

func replace_byte(in string, pos int, c byte) string {
	return in[:pos] + string(c) + in[pos+1:]
}

// Find the starting point and return the position
func start_race(line string) int {
	ret := -1
	for i := 0; i < len(line); i++ {
		c := line[i]
		if c == '_' {
			ret = i
			fmt.Print("|")
		} else {
			fmt.Printf("%c", c)
		}
	}

	fmt.Println()

	return ret
}

func check_for_char(line string, pos int, char byte) int {
	ret := -1
	for cursor := pos - 1; cursor <= pos+1; cursor++ {
		//fmt.Println("checking pos", cursor)
		if cursor >= 0 && cursor <= len(line)-1 && line[cursor] == char {
			if cursor < pos {
				line = replace_byte(line, cursor, '/')
			} else if cursor == pos {
				line = replace_byte(line, cursor, '|')
			} else {
				line = replace_byte(line, cursor, '\\')
			}
			ret = cursor
			fmt.Println(line)
		}
	}
	return ret
}

// Takes in the next line of the road and returns the new position
func race(line string, pos int) int {
	// Check for C
	new_pos := check_for_char(line, pos, 'C')
	if new_pos >= 0 {
		return new_pos
	}
	// Check for gate
	new_pos = check_for_char(line, pos, '_')
	return new_pos
}

func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)

	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	pos := -1
	if scanner.Scan() {
		pos = start_race(scanner.Text())
		//fmt.Println("Starting at", pos)
	}
	for scanner.Scan() {
		pos = race(scanner.Text(), pos)
		//fmt.Println("Next", pos)
	}

}
