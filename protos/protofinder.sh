#!/bin/bash

source_dir="../libs/kubernetes"
destination_dir="./proto_defs"

# Create the destination directory if it doesn't exist
mkdir -p "$destination_dir"

find "$source_dir" -type f -name "*.proto" | while read -r file; do
    relative_path="${file#$source_dir/}"
    mkdir -p "$destination_dir/$(dirname "$relative_path")"
    cp "$file" "$destination_dir/$relative_path"
done

echo "Proto files copied successfully to $destination_dir"
