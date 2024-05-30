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

void EnsureConsistentContainerNames(k8s::io::api::core::v1::PodStatus *status)
{
  
    MyProtobufMutator mutator;
    mutator.Seed(13435);

    std::cout << "Original name: " << status->containerstatuses(0).name() << std::endl;
    auto mutated_name = mutator.MutateString(status->containerstatuses(0).name(), 24923);
    std::cout << "Mutated name: " << status->containerstatuses(0).name() << std::endl;
    status->mutable_containerstatuses(0)->set_name(mutated_name);
    std::cout << "Updated name in status: " << status->containerstatuses(0).name() << std::endl;
    
    

}

void MutatePodMetadataNameAndNamespace(k8s::io::api::core::v1::Pod *pod, unsigned int seed)
{
    if (!pod->has_metadata())
    {
        pod->mutable_metadata();
    }

    MyProtobufMutator mutator;
    auto *metadata = pod->mutable_metadata();

    mutator.Seed(seed);

    if (metadata->name().empty())
    {
        metadata->set_name("123456");
        auto mutated_name = mutator.MutateString(metadata->name(), 200);
        metadata->set_name(mutated_name);
    }

    if (metadata->namespace_().empty())
    {
        metadata->set_namespace_("test");
        auto mutated_namespace = mutator.MutateString(metadata->namespace_(), 1000);
        if (mutated_namespace.empty())
        {
            mutated_namespace = "initial-namespace"; // Fallback value
        }
        metadata->set_namespace_(mutated_namespace);
    }
    // if (metadata->uid().empty())
    // {
    //     metadata->set_uid("12344");
    //     auto mutated_uid = mutator.MutateString(metadata->uid(), 2000);
    //     metadata->set_uid(mutated_uid);
    // }
    (*metadata->mutable_annotations())["new_key"] = "new_value";
}

void MutateNodeMetadataNameAndNamespace(k8s::io::api::core::v1::Node *node, unsigned int seed)
{
    if (!node->has_metadata())
    {
        node->mutable_metadata();
    }

    MyProtobufMutator mutator;
    auto *metadata = node->mutable_metadata();

    mutator.Seed(seed);

    if (metadata->name().empty())
    {
        metadata->set_name("node-123456");
        auto mutated_name = mutator.MutateString(metadata->name(), 200);
        metadata->set_name(mutated_name);
    }

    if (metadata->namespace_().empty())
    {
        metadata->set_namespace_("node-test");
        auto mutated_namespace = mutator.MutateString(metadata->namespace_(), 1000);
        if (mutated_namespace.empty())
        {
            mutated_namespace = "node-initial-namespace"; // Fallback value
        }
        metadata->set_namespace_(mutated_namespace);
    }
    if (metadata->uid().empty())
    {
        metadata->set_uid("node-12344");
        auto mutated_uid = mutator.MutateString(metadata->uid(), 200);
        metadata->set_uid(mutated_uid);
    }
    (*metadata->mutable_annotations())["node_new_key"] = "node_new_value";
}

DEFINE_PROTO_FUZZER(const k8s::io::api::core::v1::PodOrNode &test_proto_input)
{
    try
    {
        if (test_proto_input.has_pod())
        {
            k8s::io::api::core::v1::Pod test_proto = test_proto_input.pod();
            
            if (test_proto.has_metadata() &&
                test_proto.has_spec() &&
                test_proto.has_status())
            {
                size_t size = test_proto.ByteSizeLong();
                std::vector<uint8_t> data(size);
                test_proto.SerializeToArray(data.data(), size);
                TestGenerateAPIPodStatusWithDifferentRestartPolicies(data.data(), size);
            }
        }
        

                // size_t size = test_proto_input.ByteSizeLong();
                // std::vector<uint8_t> data(size);
                
                // test_proto_input.SerializeToArray(data.data(), size);
                // TestValidateContainerLogStatus(data.data(), size);
            
        // if (test_proto_input.has_pod() && test_proto_input.has_node())
        // {
        //     k8s::io::api::core::v1::Pod test_proto_pod = test_proto_input.pod();
        //     k8s::io::api::core::v1::Node test_proto_node = test_proto_input.node();

        //     if (test_proto_pod.has_metadata() && test_proto_node.has_metadata())
        //     {
        //         size_t sizePod = test_proto_pod.ByteSizeLong();
        //         std::vector<uint8_t> podData(sizePod);
        //         test_proto_pod.SerializeToArray(podData.data(), sizePod);
        //         size_t sizeNode = test_proto_node.ByteSizeLong();
        //         std::vector<uint8_t> nodeData(sizeNode);
        //         test_proto_node.SerializeToArray(nodeData.data(), sizeNode);
        //         TestPurgingObsoleteStatusMapEntries(podData.data(),sizePod,nodeData.data(),sizeNode);
        //     }
        // }

    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception caught during fuzzing: " << e.what() << std::endl;
    }
}
