#include <iostream>
#include "libprotobuf-mutator/src/mutator.h"
#include "libfuzzstruct.h"
#include "test-struct.pb.h"

struct testStruct {
  teststruct::testStruct protoMessage;

  std::string& CharValue() { return *protoMessage.mutable_charvalue(); }
};

void mutateStruct(testStruct* sample) {
  
  std::cout << "Before mutation: " << sample->protoMessage.DebugString() << std::endl;

  
  protobuf_mutator::Mutator mutator;
  mutator.Seed(123);
  mutator.Mutate(&sample->protoMessage, 200);

  
  std::cout << "After mutation: " << sample->protoMessage.DebugString() << std::endl;
}

int main() {
  testStruct input;
  for (int i = 0; i < 1000; ++i) {
    mutateStruct(&input);

    FuzzStruct(reinterpret_cast<char*>(&input), sizeof(testStruct));
  }

  return 0;
}
