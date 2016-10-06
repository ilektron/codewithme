package main

import "fmt"
import "log"
import "bufio"
import "os"
import "strings"

func get_penultimate_word(line string) {
	tokens := strings.Split(line, " ")
	fmt.Println(tokens[len(tokens)-2])
}

func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		get_penultimate_word(scanner.Text())
	}
}
