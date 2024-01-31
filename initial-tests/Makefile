TARGET=lpm_libfuzz_custom_mutator
PB_SRC=./test.pb.cc

CXX=clang++
CXXFLAGS=-g -fsanitize=fuzzer,address -I./ 

PROTOBUF_DIR=$(HOME)/kubefuzzthesis/libs/libprotobuf-mutator/build/external.protobuf
LPM_DIR=$(HOME)/kubefuzzthesis/libs/libprotobuf-mutator
PROTOBUF_LIB=$(PROTOBUF_DIR)/lib/libprotobufd.a
LPM_LIB=$(LPM_DIR)/build/src/libfuzzer/libprotobuf-mutator-libfuzzer.a $(LPM_DIR)/build/src/libprotobuf-mutator.a
INC=-I$(PROTOBUF_DIR)/include -I$(LPM_DIR)
DFUZZ=-DLLVMFuzzerTestOneInput=FuzzTEST
GO_EXPORT_LIB=./libpodfuzzer.a


all: $(TARGET)

# for testing libprotobuf + libfuzzer
# compile harness first
# then link lpm_libfuzz with harness.o & static libraries

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(PB_SRC) $(LPM_LIB) $(PROTOBUF_LIB) $(INC) $(GO_EXPORT_LIB) # $(LPM_LIB) must be placed before $(PROTOBUF_LIB)

.PHONY: clean
clean: 
	rm $(TARGET) *.o