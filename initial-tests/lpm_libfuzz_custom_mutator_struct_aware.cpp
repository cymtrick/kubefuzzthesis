#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "staging_src_k8s.io_api_core_v1_generated.pb.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stddef.h>  
#include "libpodfuzzermock.h"  


DEFINE_PROTO_FUZZER(const k8s::io::api::core::v1::Pod& test_proto) {
    try {
        // Check if all required fields are present
        if (test_proto.has_metadata() && 
            test_proto.has_spec() && 
            test_proto.has_status()) {
            
            // Get the size of the protobuf message
            size_t size = test_proto.ByteSizeLong();
            // Allocate memory to hold the raw binary data
            std::unique_ptr<unsigned char[]> data(new unsigned char[size]);
            // Serialize the protobuf message to raw binary data
            test_proto.SerializeToArray(data.get(), size);
            // Call the FuzzUnknownObjectMutator Go function passing the raw binary data and its size
            FuzzUnknownObjectMutator(data.get(), size);
            
        } else {
            std::cerr << "Error: One or more required fields are missing." << std::endl;
        }
    } catch (const std::exception& e) {
        // Exceptions thrown during fuzzing
        std::cerr << "Exception caught during fuzzing: " << e.what() << std::endl;
    }
}
