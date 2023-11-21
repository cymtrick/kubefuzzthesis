// single-func-fuzzer.cpp
#include <cstdint>
#include <cstddef>
#include <iostream>
#include "google/protobuf/timestamp.pb.h"

extern "C" void ProcessTimestamp(const uint8_t* data, size_t size);

void GenerateTestFuzzData(uint8_t* data, size_t size) {
    google::protobuf::Timestamp message;
    message.set_seconds(1614141000);
    message.set_nanos(500000000);
    if (!message.SerializeToArray(data, size)) {
        // Handle serialization error
        std::cerr << "Error serializing Timestamp message" << std::endl;
    }
}

// Entry point for libFuzzer
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    google::protobuf::Timestamp timestamp;

    if (size != timestamp.ByteSizeLong()) {
        return 0;
    }
    uint8_t fuzzData[size];
    GenerateTestFuzzData(fuzzData, size);
    // ProcessTimestamp(fuzzData, size);

    return 0;
}


//g++ -std=c++14 -arch arm64 -fPIC -shared -o initial-tests/single-func.so initial-tests/single-func-fuzzer.cpp libs/protobuf-25.1/src/google/protobuf/timestamp.pb.cc -Ilibs/protobuf-25.1/src -L/opt/homebrew/lib -lprotobuf