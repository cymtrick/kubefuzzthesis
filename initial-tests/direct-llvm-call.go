package main
import "C"
import (
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


//export LLVMFuzzerTestOneInput
func LLVMFuzzerTestOneInput(data *C.char, size C.size_t) C.int {
	// Cast the input data to the struct
	inputStruct := (*SampleStruct)(unsafe.Pointer(data))

	processFuzzedData(inputStruct)

	return 0
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
}
