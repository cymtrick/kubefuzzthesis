#include <iostream>
#include "libprotobuf-mutator/src/mutator.h"
#include "libfuzzstruct.h"
#include "test-struct.pb.h"
#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"

struct testStruct {
  char charValue=2;
  
};

DEFINE_PROTO_FUZZER(const teststruct::test& input) {
  // Code which needs to be fuzzed.
  std::cout << "Mutated Message Before: " << input.charvalue() << std::endl;
}
void mutateStruct(const uint8_t* data, size_t size) {
  protobuf_mutator::Mutator mutator;
  teststruct::test setcharvalue;
  setcharvalue.ParseFromArray(data, static_cast<int>(size));
  
  
  mutator.Seed(99213129);
  mutator.Fix(&setcharvalue);
  mutator.Mutate(&setcharvalue, setcharvalue.ByteSizeLong());
  // std::string mutatedData = getmessage->SerializeAsString();
  std::cout << "Mutated Message After: " << setcharvalue.charvalue() << std::endl;
  
}

int main() {
  testStruct input;
  teststruct::test charvalue;
  teststruct::test::Message* getmessage;

  for (int i = 37; i < 200; ++i) {
      charvalue.set_charvalue("sadasd"+std::to_string(i));
      std::string data = charvalue.SerializeAsString();  
      
      mutateStruct(reinterpret_cast<const uint8_t*>(data.data()), data.size());
    
    // FuzzStruct(reinterpret_cast<char*>(&input), sizeof(testStruct));
  }

  return 0;
}

//g++ -o protomutator -L/usr/local/lib/ -I/usr/local/include/libprotobuf-mutator -L-I../libs/libprotobuf-mutator/src/libfuzzer/ -L. -I. direct-protobuf-mutator.cpp test-struct.pb.cc  -lfuzzstruct -lpthread -lprotobuf-mutator -lprotobuf 