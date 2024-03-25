source_dir="../libs/kubernetes"
destination_dir="./proto_defs"
mkdir -p "$destination_dir"

proto_files=$(find "$source_dir" -type f -name "*.proto")
for file in $proto_files; do
    cp "$file" "$destination_dir"
done

echo "Proto files copied successfully to $destination_dir"
