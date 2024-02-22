package main

import (
	"C"
	"fmt"
	"log"
	"math/rand"
	"runtime"
	"strings"
	"time"

	"k8s.io/apimachinery/pkg/apis/meta/v1/unstructured"
	"k8s.io/apimachinery/pkg/util/yaml"
)

//export FuzzPodMutator
func FuzzPodMutator(data *C.char, size C.size_t) {
	mutatedStrings := make([]string, 4)
	for i := 0; i < 4; i++ {
		// hexData := C.GoStringN(data, C.int(size))
		// asciiSafeData := mutateToASCIIRange(hexData)
		// randomString := generateRandomString(10) // Adjust the length as needed
		// mutatedStrings[i] = asciiSafeData + randomString
		mutatedStrings[i] = C.GoStringN(data, C.int(size))
	}
	yamlDataTemplate := generateYAMLWithRandomStrings(mutatedStrings)
	pods, err := generatePodsFromYAML(yamlDataTemplate)
	if err != nil {
		// Handle the error more gracefully
		log.Printf("Error generating pods from YAML: %v", err)
		return
	}

	for _, pod := range pods {
		processFuzzedPod(pod)
	}
}
func mutateToASCIIRange(hexData string) string {
	result := ""
	for i := 0; i < len(hexData); i += 2 {
		byteValue := hexData[i : i+2]
		asciiValue := uint8((byteValue[0]-'0')*16 + (byteValue[1] - '0'))
		if asciiValue < 32 {
			// Ensure that the ASCII value stays within the printable range
			asciiValue = 32
		} else if asciiValue > 126 {
			asciiValue = 126
		}
		result += string(asciiValue)
	}
	return result
}
func generateYAMLWithRandomStrings(randomStrings []string) string {
	yamlTemplate := `
apiVersion: v1
kind: Pod
metadata:
  name: pod-%s
  labels:
    app: %s
spec:
  containers:
  - name: container-%s
    image: nginx
`
	combinedYAML := ""
	for i := 0; i < 4; i++ {
		combinedYAML += fmt.Sprintf(yamlTemplate, randomStrings[i], randomStrings[i], randomStrings[i])
	}

	return combinedYAML
}

func generateRandomString(length int) string {
	rand.NewSource(time.Now().UnixNano())
	charset := "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
	result := make([]byte, length)
	for i := range result {
		result[i] = charset[rand.Intn(len(charset))]
	}
	return string(result)
}

func generatePodsFromYAML(yamlData string) ([]*unstructured.Unstructured, error) {
	decoder := yaml.NewYAMLOrJSONDecoder(strings.NewReader(yamlData), 4096)

	var pods []*unstructured.Unstructured

	for {
		pod := &unstructured.Unstructured{}
		err := decoder.Decode(pod)
		if err != nil {
			// Handle the end of the YAML stream

			break

		}

		pods = append(pods, pod)
	}

	return pods, nil
}

func processFuzzedPod(pod *unstructured.Unstructured) {
	defer catchPanics()

	fmt.Println("Fuzzing with Pod:")
	fmt.Printf("API Version: %s\n", pod.GetAPIVersion())
	fmt.Printf("Kind: %s\n", pod.GetKind())
	fmt.Printf("Metadata: %v\n", pod.Object["metadata"])
	fmt.Printf("Spec: %v\n", pod.Object["spec"])
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
