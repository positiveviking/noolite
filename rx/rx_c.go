package main

// #cgo pkg-config: libusb-1.0
// #cgo LDFLAGS: -lusb-1.0
// #include "rx.h"
import "C"

import "fmt"

func main() {
	x := C.open_rx()
	fmt.Println(x)
}
