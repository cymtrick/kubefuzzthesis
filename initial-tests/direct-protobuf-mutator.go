package main

import (
	"C"
	"fmt"
	"runtime"
	"strings"
	"unsafe"
)

type SampleStruct struct {
	IntValue   int32
	CharValue  byte
	FloatValue float32
}

//export FuzzStruct
func FuzzStruct(data *C.char, size C.size_t) {
	inputStruct := (*SampleStruct)(unsafe.Pointer(data))
	processFuzzedData(inputStruct)
}

func processFuzzedData(data *SampleStruct) {
	defer catchPanics()

	fmt.Printf("Fuzzing with Struct: IntValue=%d, CharValue=%c, FloatValue=%.2f\n",
		data.IntValue, data.CharValue, data.FloatValue)
}

func catchPanics() {
	if r := recover(); r != nil {
		var err string
		switch r.(type) {
		case string:
			err = r.(string)
		case runtime.Error:
			err = r.(runtime.Error).Error()
		case error:
			err = r.(error).Error()
		}
		if strings.Contains(err, "GO-FUZZ-BUILD-PANIC") {
			return
		} else {
			panic(err)
		}
	}
}

func main() {
	// Keep this running or use a mechanism to keep it alive for fuzzing
	select {}
}

//go build -o libgofuzzer.so -buildmode=c-shared FUZZ_TARGET.go