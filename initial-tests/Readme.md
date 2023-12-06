# Go Fuzzing with LibFuzzer and C++ Integration

## Objective
Demonstrate how to perform fuzz testing on a Go program with LibFuzzer and integrate it with C++.

## Steps

### 1. Writing a Go Program with Fuzzing Function

Write a Go program with a fuzzing function that takes a struct as input.

### 2. Integrating with LibFuzzer in C++
Write a C++ program that calls the Go fuzzing function using LibFuzzer.

### 3. Handling Multiple Definition and Linking Errors

When building the program, ensuring that there's no conflicting main function and resolve any undefined references.

### 4. Random Struct Generation

Modify the C++ program to generate random structs for fuzzing.

## Running the direct-protobuf-mutator.cpp
 
To run this protobuf mutator please download the release version of libprotobuf-mutator https://github.com/google/libprotobuf-mutator/releases/tag/v1.1 and install with `LIB_PROTO_MUTATOR_DOWNLOAD_PROTOBUF=ON`

please change the `-L` and `-I` depending on where these include and local libraries are installed

````
g++ -o protomutator -L/usr/local/lib/ -I/usr/local/include/libprotobuf-mutator -I/usr/local/include/libprotobuf-mutator/src/libfuzzer/ -L. -I. direct-protobuf-mutator.cpp test-struct.pb.cc  -lfuzzstruct -lpthread -lprotobuf-mutator -lprotobuf 
````

## Running the fuzzer

````
GOARCH={SYSTEM_ARCH} go build -o libgofuzzer.so -buildmode=c-shared FUZZ_TARGET.go
g++ -std=c++17 -L. fuzzer.cpp -lgofuzzer -o fuzzer -fsanitize=fuzzer
LD_LIBRARY_PATH=. ./fuzzer
````

## Things learnt during the implementation
1) //export on top of GO c-shared functions is requrired to export the header and binary files. This got me confused for a day until I read the https://pkg.go.dev/cmd/cgo

````
//export LLVMFuzzerTestOneInput
func LLVMFuzzerTestOneInput(data *C.char, size C.size_t) C.int {
	// Cast the input data to the struct
	inputStruct := (*SampleStruct)(unsafe.Pointer(data))

	processFuzzedData(inputStruct)

	return 0
}

````

2) Protobuf default proto internals are heavily dependent abseil which are causing issue when dynamically linking with the abseil binaries

For example these are the issue I faced

````
/usr/bin/ld: initial-tests/single-func-fuzzer.so: undefined reference to `absl::log_internal::CheckOpMessageBuilder::ForVar2()'
/usr/bin/ld: initial-tests/single-func-fuzzer.so: undefined reference to `absl::log_internal::CheckOpMessageBuilder::CheckOpMessageBuilder(char const*)'
/usr/bin/ld: initial-tests/single-func-fuzzer.so: undefined reference to `absl::log_internal::LogMessageFatal::LogMessageFatal(char const*, int, std::basic_string_view<char, std::char_traits<char> >)'
/usr/bin/ld: initial-tests/single-func-fuzzer.so: undefined reference to `absl::log_internal::LogMessageFatal::~LogMessageFatal()'
/usr/bin/ld: initial-tests/single-func-fuzzer.so: undefined reference to `absl::log_internal::CheckOpMessageBuilder::NewString[abi:cxx11]()'
````

even when I linked all the libraries which are mentioned it was still throwing the errors. For example I had to find each binary required by protobuf timestamp to work and store it as environmental variable. Below is the log of what i did

#### The libraries which required for the protobuf to link with the binary
````
ABSL_LIBS="-labsl_str_format_internal -labsl_strings -labsl_strings_internal -labsl_log_initialize -labsl_log_entry -labsl_log_flags -labsl_log_severity -labsl_log_internal_check_op -labsl_log_internal_conditions -labsl_log_internal_message -labsl_log_internal_nullguard -labsl_log_internal_proto -labsl_log_internal_format -labsl_log_internal_globals -labsl_log_internal_log_sink_set -labsl_log_sink -labsl_raw_logging_internal -labsl_log_globals -lutf8_validity -labsl_cord -labsl_cordz_info -labsl_cordz_handle -labsl_cordz_functions -labsl_cord_internal -labsl_crc_cord_state -labsl_crc32c -labsl_crc_internal -labsl_exponential_biased -labsl_synchronization -labsl_time -labsl_time_zone -labsl_int128 -labsl_examine_stack -labsl_stacktrace -labsl_symbolize -labsl_demangle_internal -labsl_debugging_internal -labsl_malloc_internal -labsl_throw_delegate -labsl_strerror -labsl_raw_hash_set -labsl_hash -labsl_city -labsl_low_level_hash -labsl_base -labsl_spinlock_wait"

````

#### Error generated

````
clang++ -fsanitize=fuzzer initial-tests/single-func.so -o initial-tests/fuzzer 
/usr/bin/ld: initial-tests/single-func.so: undefined reference to `absl::synchronization_internal::GraphCycles::UpdateStackTrace(absl::synchronization_internal::GraphId, int, int (*)(void**, int))'
/usr/bin/ld: initial-tests/single-func.so: undefined reference to `absl::synchronization_internal::KernelTimeout::MakeRelativeTimespec() const'
/usr/bin/ld: initial-tests/single-func.so: undefined reference to `absl::synchronization_internal::KernelTimeout::MakeAbsTimespec() const'
/usr/bin/ld: initial-tests/single-func.so: undefined reference to `absl::synchronization_internal::GraphCycles::GraphCycles()'
/usr/bin/ld: initial-tests/single-func.so: undefined reference to `absl::synchronization_internal::GraphCycles::InsertEdge(absl::synchronization_internal::GraphId, absl::synchronization_internal::GraphId)'
/usr/bin/ld: initial-tests/single-func.so: undefined reference to `absl::synchronization_internal::GraphCycles::GetId(void*)'
/usr/bin/ld: initial-tests/single-func.so: undefined reference to `absl::synchronization_internal::GraphCycles::RemoveNode(void*)'
/usr/bin/ld: initial-tests/single-func.so: undefined reference to `absl::synchronization_internal::GraphCycles::GetStackTrace(absl::synchronization_internal::GraphId, void***)'
/usr/bin/ld: initial-tests/single-func.so: undefined reference to `absl::synchronization_internal::GraphCycles::Ptr(absl::synchronization_internal::GraphId)'
/usr/bin/ld: initial-tests/single-func.so: undefined reference to `absl::synchronization_internal::GraphCycles::FindPath(absl::synchronization_internal::GraphId, absl::synchronization_internal::GraphId, int, absl::synchronization_internal::GraphId*) const'
clang: error: linker command failed with exit code 1 (use -v to see invocation)
````

Tried several times rebuild protobuf with abseil on Position independent code `-fPIC` and `SHARED_LIB=On` but still had the same issue.

Still working on this to successfully link to try the libprotobuf-mutator and the custom mutator on further tests