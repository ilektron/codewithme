package main

import (
    "fmt"
    "log"
    "bufio"
    "os"
    "strconv"
)

func calc_possibilities(val int) int {
    if val > 50 {
        return calc_possibilities(50) * calc_possibilities(val - 50)
    }
    if val > 10 {
        return calc_possibilities(10) * calc_possibilities(val - 10)
    }
    if val > 5 {
        return calc_possibilities(5) * calc_possibilities(val - 5)
    }

    return 1
}

func main() {
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
        num, err := strconv.Atoi(scanner.Text())
        if err != nil {
            fmt.Println(num)
            log.Fatal(err)
        }

        fmt.Println(calc_possibilities(num))

	}
}
