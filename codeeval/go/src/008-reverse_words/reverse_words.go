package main

import "fmt"
import "log"
import "bufio"
import "os"
import "strings"

func main() {
    file, err := os.Open(os.Args[1])
    if err != nil {
        log.Fatal(err)
    }
    defer file.Close()
    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        tokens := strings.Split(scanner.Text(), " ")
        for i := len(tokens) - 1; i >= 0; i-- {
            fmt.Print(tokens[i])
            if i > 0 {
                fmt.Print(" ")
            }
        }
        fmt.Println()
    }
}
