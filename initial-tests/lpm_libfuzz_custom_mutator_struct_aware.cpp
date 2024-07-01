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

void EnsureConsistentContainerNames(k8s::io::api::core::v1::Pod *pod)
{
    if (!pod->has_spec() || !pod->has_status()) {
        return; 
    }

    auto* spec = pod->mutable_spec();
    auto* status = pod->mutable_status();
    if (!spec->containers().empty() && !status->containerstatuses().empty()) {
        auto& mutable_container_status = *status->mutable_containerstatuses()->Mutable(0);
        const auto& container_name = spec->containers(0).name();
        mutable_container_status.set_name(container_name);
    }
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
    if (metadata->uid().empty())
    {
        metadata->set_uid("12344");
        auto mutated_uid = mutator.MutateString(metadata->uid(), 200);
        metadata->set_uid(mutated_uid);
    }
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
            
                size_t size = test_proto.ByteSizeLong();
                std::vector<uint8_t> data(size);
                test_proto.SerializeToArray(data.data(), size);
                DoesNotDeletePodDirsIfContainerIsRunning(data.data(), size);
            
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
