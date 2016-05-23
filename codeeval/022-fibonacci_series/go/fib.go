package main

import "fmt"
import "log"
import "bufio"
import "os"
import "strconv"

func fib(n int) int {
    if n <= 0 {
        return 0
    }
    if n == 1 {
        return 1
    }
    return fib(n - 1) + fib(n - 2)
}

func main() {
    file, err := os.Open(os.Args[1])
    if err != nil {
        log.Fatal(err)
    }
    defer file.Close()
    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        i, err := strconv.Atoi(scanner.Text())
        if err == nil {
            fmt.Println(fib(i))
        }
    }
}
