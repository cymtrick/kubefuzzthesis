#include <iostream>
#include "libprotobuf-mutator/src/mutator.h"
#include "libfuzzstruct.h"
#include <cstdint>
#include <cstddef>
#include <cstring>  
#include <cstdlib>  
#include <iostream>
#include "test-struct.pb.h" 


struct testStruct {
  int32_t IntValue;
  char CharValue;
  float FloatValue;
};

void mutateStruct(testStruct* sample) {
  // Convert SampleStruct to protobuf message
  teststruct::testStruct protoMessage;
  // Use protobuf_mutator::Mutator to mutate the protobuf message
  protobuf_mutator::Mutator mutator;
  mutator.Mutate(&protoMessage, protoMessage.ByteSizeLong());

  // Convert the mutated protobuf message back to SampleStruct
  sample->IntValue = protoMessage.intvalue();
  sample->CharValue = protoMessage.charvalue();
  sample->FloatValue = protoMessage.floatvalue();
}

int main() {
  testStruct input;
  for (int i = 0; i < 1000; ++i) {
    mutateStruct(&input);

    FuzzStruct(reinterpret_cast<char*>(&input), sizeof(testStruct));
  }

  return 0;
}
