#include <iostream>
#include "libprotobuf-mutator/src/mutator.h"
#include "libfuzzstruct.h"
#include "test-struct.pb.h"

struct testStruct {
  char charValue=2;
  
};

void mutateStruct(const uint8_t* data, size_t size) {
  protobuf_mutator::Mutator mutator;
  teststruct::test setcharvalue;
  setcharvalue.ParseFromArray(data, static_cast<int>(size));
  std::cout << "Mutated Message Before: " << setcharvalue.charvalue() << std::endl;
  mutator.Seed(99213129);
  mutator.Mutate(&setcharvalue, 9921);
  // std::string mutatedData = getmessage->SerializeAsString();
  std::cout << "Mutated Message After: " << setcharvalue.SerializeAsString() << std::endl;
  
}

int main() {
  testStruct input;
  teststruct::test charvalue;
  teststruct::test::Message* getmessage;

  for (int i = 37; i < 200; ++i) {
      charvalue.set_charvalue("sadasd");
      std::string data = charvalue.SerializeAsString();  
      
      mutateStruct(reinterpret_cast<const uint8_t*>(data.data()), data.size());
    
    // FuzzStruct(reinterpret_cast<char*>(&input), sizeof(testStruct));
  }

  return 0;
}
