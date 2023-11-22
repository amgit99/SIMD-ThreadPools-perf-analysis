#!/bin/bash

# Path to the compiled C++ program
cpp_program="./bin/tiled_simd_thread"

# Loop through powers of 2 from 2^2 to 2^14
for ((i=2; i<12; i++)); do
    arg_value=$((2 ** i))
    echo "Running with argument: $arg_value"
    $cpp_program $arg_value
done
