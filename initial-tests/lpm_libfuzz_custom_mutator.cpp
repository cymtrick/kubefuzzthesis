#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "test.pb.h"
#include "libfuzzstruct.h"
#include "libpodfuzzermock.h"
#include <iostream>
#include <fstream>
#include <sstream>

extern "C" void FuzzStruct(char* data, size_t size);
bool hasRegister = false;

std::string ProtoToData(const TEST& test_proto) {
    std::stringstream all;
    const auto& aa = test_proto.a();
    const auto& bb = test_proto.b();
    // all.write(reinterpret_cast<const char*>(&aa), sizeof(aa));
    if (bb.size() != 0) {
        all.write(bb.c_str(), bb.size());
    }

    std::string res = all.str();
    if (bb.size() != 0 && res.size() != 0) {
        // set PROTO_FUZZER_DUMP_PATH env to dump the serialized protobuf
        if (const char* dump_path = std::getenv("PROTO_FUZZER_DUMP_PATH")) {
            std::ofstream of(dump_path);
            of.write(res.data(), res.size());
        }
    }

    // Print the serialized data to the standard output
    // std::cout << "Serialized Data: " << res << std::endl;
    return res;
}


DEFINE_PROTO_FUZZER(const TEST& test_proto) {
    /* Register post processor with our custom mutator method */
    if (!hasRegister) {
        protobuf_mutator::libfuzzer::RegisterPostProcessor(
            TEST::descriptor(),
            [](google::protobuf::Message* message, unsigned int seed) {
                TEST* t = static_cast<TEST*>(message);
                /* test.b will only be "THIS" or "SHIT" */
           
            });
        hasRegister = true;
        std::cerr << "Error: Initialization not performed." << std::endl;
        return;
    }

    auto s = ProtoToData(test_proto);
    if (s.empty()) {
        // Handle empty input error
        return;
    }

    try {
        FuzzPodMutator(reinterpret_cast<char*>(s.data()), s.size());
    } catch (const std::exception& e) {
        // Exceptions thrown during fuzzing
        std::cerr << "Exception caught during fuzzing: " << e.what() << std::endl;
    }
}
