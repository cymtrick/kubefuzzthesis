// main.go
package main

import (
	"C"
	"fmt"
	"unsafe"

	"github.com/golang/protobuf/proto"
	timestamp "github.com/golang/protobuf/ptypes/timestamp"
)

func ProcessTimestamp(data *C.uchar, size C.size_t) {
	byteSlice := C.GoBytes(unsafe.Pointer(data), C.int(size))

	message := &timestamp.Timestamp{}

	if err := proto.Unmarshal(byteSlice, message); err != nil {
		fmt.Println("Error unmarshaling Timestamp message:", err)
		return
	}

	fmt.Printf("Processing Timestamp Message: %+v\n", message)
}

func main() {
}
