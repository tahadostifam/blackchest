if [ $# -ne 1 ]; then
    echo "Usage: $0 <assembly_file.asm>"
    exit 1
fi

asm_file="$1"
base_name="${asm_file%.*}"
obj_file="${base_name}.o"
exe_file="${base_name}.out"

# Assemble
nasm -f elf "$asm_file" -o "$obj_file"
if [ $? -ne 0 ]; then
    echo "Assembly failed."
    exit 1
fi

# Link
ld -m elf_i386 -s -o "$exe_file" "$obj_file"
if [ $? -ne 0 ]; then
    echo "Linking failed."
    rm -f "$obj_file"
    exit 1
fi

# Run
"./$exe_file"

# Cleanup
rm -f "$obj_file" "$exe_file"