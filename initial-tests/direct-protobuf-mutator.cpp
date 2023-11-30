#include <iostream>
#include "libprotobuf-mutator/src/mutator.h"
#include "libfuzzstruct.h"

// Define the protobuf message structure
struct SampleStruct {
  int32_t IntValue;
  char CharValue;
  float FloatValue;
};
extern "C" void FuzzStruct(const uint8_t* data, size_t size);

void mutateStruct(SampleStruct* sample) {
  protobuf_mutator::SimpleMutator mutator;

  mutator.Mutate(sample, sizeof(SampleStruct));
}

int main() {
  SampleStruct input;
  for (int i = 0; i < 1000; ++i) {
    mutateSampleStruct(&input);

    FuzzSampleStruct(reinterpret_cast<const uint8_t*>(&input), sizeof(SampleStruct));
  }

  return 0;
}
