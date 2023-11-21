// fuzzer.cpp
#include <cstdint>
#include <cstddef>
#include <iostream>

struct SampleStruct {
    int32_t intValue;
    char charValue;
    float floatValue;
};

extern "C" void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size);

int main() {
    SampleStruct sample = {42, 'A', 3.14};
    LLVMFuzzerTestOneInput(reinterpret_cast<const uint8_t*>(&sample), sizeof(sample));

    return 0;
}
