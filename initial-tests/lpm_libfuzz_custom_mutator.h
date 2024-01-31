#ifndef MY_MUTATOR_H
#define MY_MUTATOR_H

#include "libprotobuf-mutator/src/mutator.h"
#include "test.pb.h"
#include <cstdint>
#include <cstddef>
#include <vector>

/**
custom_mutator state structure
Reference: https://github.com/airbus-seclab/AFLplusplus-blogpost/blob/b0cfc7016bd60cf998969d79a78eabd8471c78eb/src/mutator/custom_mutator.cpp#L29
*/
typedef struct custom_mutator {
    unsigned int seed;
    uint8_t *mutated_out_buf;
    size_t mutated_out_buf_size;
} custom_mutator_t;

extern "C" size_t custom_fuzz(custom_mutator_t *data, uint8_t *buf, size_t buf_size, uint8_t **out_buf, uint8_t *add_buf, size_t add_buf_size, size_t max_size);

class MyMutator : public protobuf_mutator::Mutator {
public:
    friend size_t custom_fuzz(custom_mutator_t *data, uint8_t *buf, size_t buf_size, uint8_t **out_buf, uint8_t *add_buf, size_t add_buf_size, size_t max_size);
};

#endif // MY_MUTATOR_H
