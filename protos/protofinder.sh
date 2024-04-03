#!/bin/bash

source_dir="../libs/kubernetes"
destination_dir="./proto_defs"

# Create the destination directory if it doesn't exist
mkdir -p "$destination_dir"

# Use find to locate all .proto files in the source directory and its subdirectories
find "$source_dir" -type f -name "*.proto" | while read -r file; do
    relative_path="${file#$source_dir/}"
    new_relative_path="${relative_path//\//_}"
    merged_path="${new_relative_path#*_libs_}"
    cp "$file" "$destination_dir/${merged_path}"
done

echo "Proto files copied successfully to $destination_dir"
