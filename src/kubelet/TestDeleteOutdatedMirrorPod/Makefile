# Paths and file locations
PROTODEFS_DIR=$(HOME)/kubefuzzthesis/protos/proto_defs
PROTOBUF_LIB_DIR=$(HOME)/kubefuzzthesis/libs/libprotobuf-mutator/build/external.protobuf/lib
LPM_LIB_DIR=$(HOME)/kubefuzzthesis/libs/libprotobuf-mutator/build/src
INC_DIRS=-I$(HOME)/kubefuzzthesis/libs/libprotobuf-mutator/build/external.protobuf/include -I$(HOME)/kubefuzzthesis/libs/libprotobuf-mutator -I$(PROTODEFS_DIR)
GO_EXPORT_LIB=../../libpodfuzzermock.a
# Compiler settings
CXX=clang++
CXXFLAGS=-g -fsanitize=fuzzer,address $(INC_DIRS)
AR=ar

# Libraries
PROTOBUF_LIB=$(PROTOBUF_LIB_DIR)/libprotobuf.a
LPM_LIBS=$(LPM_LIB_DIR)/libfuzzer/libprotobuf-mutator-libfuzzer.a $(LPM_LIB_DIR)/libprotobuf-mutator.a

# Target
TARGET=lpm_libfuzz_struct_aware_unguided

# Source files
PB_SOURCES=$(wildcard $(PROTODEFS_DIR)/*.pb.cc)
PB_OBJECTS=$(PB_SOURCES:.cc=.o)

all: $(TARGET)

# Rule to compile Protocol Buffer source files into object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create a static library from all Protocol Buffer object files
libprotos.a: $(PB_OBJECTS)
	$(AR) rcs $@ $(PB_OBJECTS)

# Main target
$(TARGET): $(TARGET).cpp libprotos.a
	$(CXX) $(CXXFLAGS) -o $@ $(TARGET).cpp libprotos.a $(LPM_LIBS) $(GO_EXPORT_LIB) $(PROTOBUF_LIB) 

clean:
	rm -f $(TARGET) $(PB_OBJECTS) libprotos.a
