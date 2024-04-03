#!/bin/bash

# Check if protoc is installed
if ! command -v protoc &> /dev/null; then
    echo "Error: protoc is not installed. Please install Protocol Buffers compiler (protoc) first."
    exit 1
fi

# Check if no argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <path_to_proto_files>"
    exit 1
fi

# Check if provided path exists
if [ ! -d "$1" ]; then
    echo "Error: Directory '$1' does not exist."
    exit 1
fi

# Find all .proto files in the directory and its subdirectories
proto_files=$(find "$1" -type f -name "*.proto")

# Compile each .proto file
for proto_file in $proto_files; do
    echo "Compiling $proto_file..."
    protoc --go_out=. "$proto_file"
done

echo "Compilation completed."
