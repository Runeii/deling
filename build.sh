#!/bin/bash

echo "Killing any running instance of deling..."
pkill -f deling

# Directory containing .ts files
TS_DIR="./translations"
# Build directory
BUILD_DIR="./build"

# Iterate over all .ts files with the naming pattern deling_[lang].ts
for ts_file in ${TS_DIR}/deling_*.ts; do
    # Check if any .ts files are found
    if [ -f "$ts_file" ]; then
        # Generate the corresponding .qm file
        echo "Processing $ts_file"
        lrelease "$ts_file"
        qm_file="${ts_file%.ts}.qm"
    else
        echo "No .ts files found matching the pattern."
        exit 1
    fi
done

# Create the build directory if it does not exist
if [ ! -d "$BUILD_DIR" ]; then
    mkdir -p "$BUILD_DIR"
fi

# Change to the build directory
cd "$BUILD_DIR"

# Run qmake and make
echo "Running qmake and make..."
qmake ../Deling.pro
make

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build completed successfully."
else
    echo "Build failed."
    exit 1
fi

ls
# Run the newly built application
echo "Running deling.app..."
open ./deling.app &

echo "Done."