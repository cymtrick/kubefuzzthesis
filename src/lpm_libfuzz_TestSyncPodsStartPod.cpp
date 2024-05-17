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
    // std::int32_t MutateInt32(const std::int &value) override
    // {
    //     return protobuf_mutator::Mutator::MutateInt32(value);
    // }
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
            // MutatePodMetadataNameAndNamespace(&test_proto, 123);
            //  EnsureConsistentContainerNames(&test_proto);

            size_t size = test_proto.ByteSizeLong();
            std::vector<uint8_t> data(size);
            test_proto.SerializeToArray(data.data(), size);
            std::cout << "Mutated name: " << test_proto.metadata().name()
                      << "Mutated uid: " << test_proto.metadata().uid()
                      << ", Mutated namespace: " << test_proto.metadata().namespace_() << std::endl;
            DoesNotDeletePodDirsIfContainerIsRunning(data.data(), size);
            std::cout << "Fuzzing Pod with mutated metadata." << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception caught during fuzzing: " << e.what() << std::endl;
    }
}
