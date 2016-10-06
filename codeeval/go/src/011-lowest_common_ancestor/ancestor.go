package main

import "fmt"
import "log"
import "bufio"
import "os"
import "strconv"
import "strings"

type Node struct {
	val   int
	left  *Node
	right *Node
}

type Tree struct {
	root *Node
}

func (n *Node) print() {
	if n != nil {
		n.left.print()
		n.right.print()
		fmt.Println(n.val)
	}
}

func (t *Tree) print() {
	fmt.Println("Tree:")
	t.root.print()
	fmt.Println("Done")
}

func (t *Tree) insert(val int) {
	n := new(Node)
	n.val = val
	if t.root == nil {
		t.root = n
	} else {
		p := &t.root
		for *p != nil {
			if val < (*p).val {
				p = &(*p).left
			} else {
				p = &(*p).right
			}
		}
		*p = n
	}
}

func (t *Tree) find(val int) bool {
	p := &t.root
	for *p != nil {
		if val == (*p).val {
			return true
		} else if val < (*p).val {
			p = &(*p).left
		} else {
			p = &(*p).right
		}
	}
	return false
}

func (t *Tree) get_common_ancestor(val1 int, val2 int) {
	p := &t.root
	for *p != nil {
		if val1 == (*p).val {
			fmt.Println(val1)
			return
		} else if val2 == (*p).val {
			fmt.Println(val2)
			return
		} else if val1 < (*p).val && val2 < (*p).val {
			p = &(*p).left
		} else if val1 > (*p).val && val2 > (*p).val {
			p = &(*p).right
		} else {
			fmt.Println((*p).val)
			return
		}
	}
}

func build_tree(t *Tree) {
	t.insert(30)
	t.insert(8)
	t.insert(52)
	t.insert(3)
	t.insert(20)
	t.insert(10)
	t.insert(29)
}

func main() {
	t := new(Tree)
	build_tree(t)
	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		children := strings.Split(scanner.Text(), " ")
		child1, _ := strconv.Atoi(children[0])
		child2, _ := strconv.Atoi(children[1])

		t.get_common_ancestor(child1, child2)
	}
}
