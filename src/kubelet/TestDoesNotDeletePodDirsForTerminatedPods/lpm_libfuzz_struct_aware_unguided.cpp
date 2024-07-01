#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "libprotobuf-mutator/src/mutator.h"
#include "staging_src_k8s.io_api_core_v1_generated.pb.h"
#include <iostream>
#include <vector>
#include <string>
#include <google/protobuf/message.h>
#include "../../libpodfuzzermock.h"

// Custom Protobuf mutator class
class MyProtobufMutator : public protobuf_mutator::Mutator
{
public:
    using protobuf_mutator::Mutator::Mutator;

    std::string MutateString(const std::string &value, int size_increase_hint) override
    {
        return protobuf_mutator::Mutator::MutateString(value, size_increase_hint);
    }

};


DEFINE_PROTO_FUZZER(const k8s::io::api::core::v1::Pod &test_proto_input)
{
    try
    {
        k8s::io::api::core::v1::Pod test_proto = test_proto_input;
        // Check if all required fields are present
        if (test_proto.has_metadata() &&
            test_proto.has_spec() &&
            test_proto.has_status())
        {

            size_t size = test_proto.ByteSizeLong();
            std::vector<uint8_t> data(size);
            test_proto.SerializeToArray(data.data(), size);
            TestDoesNotDeletePodDirsForTerminatedPods(data.data(), size);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception caught during fuzzing: " << e.what() << std::endl;
    }
}
