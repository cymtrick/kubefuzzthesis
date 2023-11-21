
#include <cstdint>
#include <cstddef>
#include <cstring>  
#include <cstdlib>  
#include <iostream>
#include "libgofuzzer.h"

using namespace std;

struct SampleStruct {
    int32_t intValue;
    char charValue;
    float floatValue;
};

int main(int argc, char** argv) {
    SampleStruct sample;

    if (argc > 1) {
        if (sizeof(SampleStruct) <= std::strtoul(argv[1], nullptr, 10)) {
            std::memcpy(&sample, argv[1], sizeof(sample));
            LLVMFuzzerTestOneInput(reinterpret_cast<char*>(&sample), sizeof(sample));
        }
    } else {
        // If no data is provided, assume it's random
        LLVMFuzzerTestOneInput(reinterpret_cast<char*>(&sample), sizeof(sample));
    }

    return 0;
}

