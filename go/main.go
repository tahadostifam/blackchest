package main

import "fmt"

func main() {
	var a [3][3]int32

	a[0] = [3]int32{1, 2, 3}
	a[1] = [3]int32{3, 4, 5}
	a[2] = [3]int32{6, 7, 8}

	fmt.Println(a)
}
