#include <iostream>
#include "libprotobuf-mutator/src/mutator.h"
#include "libfuzzstruct.h"
#include "test-struct.pb.h"
#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"

using namespace protobuf_mutator;

struct testStruct {
  char charValue=2;
  
};

// DEFINE_PROTO_FUZZER(const teststruct::test& input) {
 
//   std::cout << "Mutated Message Before: " << input.charvalue() << std::endl;
// }


void mutateStruct(const char* data, size_t size) {
  protobuf_mutator::Mutator mutator;
  teststruct::test getdata;
  teststruct::test::Message* message;
  
  getdata.set_charvalue(data);
  std::cout << "Mutated Message before: " << getdata.DebugString();
  mutator.Mutate(&getdata, 200);
  // std::string mutatedData = getmessage->SerializeAsString();
  std::cout << "Mutated Message After: " << getdata.DebugString() << std::endl;
  
}



int main() {
  testStruct input;
  teststruct::test charvalue;
  teststruct::test::Message* getmessage;

  for (int i = 37; i < 200; ++i) {
      charvalue.set_charvalue("sadasd"+std::to_string(i));
      std::string data = charvalue.SerializeAsString();  
      
      mutateStruct(reinterpret_cast<const char*>(data.data()), data.size());
    
    // FuzzStruct(reinterpret_cast<char*>(&input), sizeof(testStruct));
  }

  return 0;
}

//g++ -o protomutator -L/usr/local/lib/ -I/usr/local/include/libprotobuf-mutator -L../libs/libprotobuf-mutator/src/libfuzzer/ -I../libs/libprotobuf-mutator/src/libfuzzer/ -L. -I. direct-protobuf-mutator.cpp test-struct.pb.cc  -lfuzzstruct -lpthread -lprotobuf-mutator -lprotobuf 