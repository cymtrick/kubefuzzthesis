#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "libprotobuf-mutator/src/mutator.h"
#include "staging_src_k8s.io_api_core_v1_generated.pb.h"
#include <iostream>
#include <vector>
#include <string>
#include <google/protobuf/message.h>
#include "libpodfuzzermock.h"

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


DEFINE_PROTO_FUZZER(const k8s::io::api::core::v1::PodOrNode &test_proto_input)
{
    try
    {
        if (test_proto_input.has_pod())
        {
            k8s::io::api::core::v1::Pod test_proto = test_proto_input.pod();
            
                size_t size = test_proto.ByteSizeLong();
                std::vector<uint8_t> data(size);
                test_proto.SerializeToArray(data.data(), size);
                TestDispatchWorkOfActivePod(data.data(), size);
            
        }
        else if (test_proto_input.has_node() && test_proto_input.has_pod())
        {
            k8s::io::api::core::v1::Node test_proto_node = test_proto_input.node();
            k8s::io::api::core::v1::Pod test_proto_pod = test_proto_input.pod();
            if (test_proto_node.has_metadata() && test_proto_pod.has_metadata())
            {
                size_t size_node = test_proto_node.ByteSizeLong();
                size_t size_pod = test_proto_pod.ByteSizeLong();
                std::vector<uint8_t> data_node(size_node);
                std::vector<uint8_t> data_pod(size_pod);
                test_proto_node.SerializeToArray(data_node.data(), size_node);
                test_proto_pod.SerializeToArray(data_node.data(), size_pod);
                // TestHandlePluginResources(data_pod.data(),size_pod,data_node.data(),size_node);

            }
        }
        else
        {
            std::cerr << "Unsupported protobuf type: " << test_proto_input.GetTypeName() << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception caught during fuzzing: " << e.what() << std::endl;
    }
}
