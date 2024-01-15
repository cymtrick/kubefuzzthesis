#include <cstdint>
#include <cstddef>
#include <iostream>

extern "C" int FuzzTEST(const uint8_t* data, size_t size) {
    if (data[0] == '\x01') {
        std::cout << "found: " << data[0] << std::endl;
    }
    return 0;
}
