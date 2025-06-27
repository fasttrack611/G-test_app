#!/bin/bash

# Exit on error
set -e

# Define paths
SAMPLE_PATH="/zephyrproject/zephyr/samples/gpio_test"
GCOV_SCRIPT="/zephyrproject/zephyr/scripts/gen_gcov_files.py"
GCOV_EXEC="/zephyrproject/zephyr-sdk-0.16.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcov"
REPORT_DIR="gcov_report"

# Build with coverage options
echo "Starting west build..."
west build -b qemu_x86 $SAMPLE_PATH -- -DCONFIG_COVERAGE=y -DCONFIG_COVERAGE_DUMP=y
echo "Finished west build."

# Check if log.log exists
if [ -f "log.log" ]; then
    echo "log.log exists. Skipping test run..."
else
    echo "Running test and capturing output..."
    ninja -C build run | tee log.log
fi

# Generate gcov files
echo "Generating gcov files..."
python3 $GCOV_SCRIPT -i log.log

# Create report directory
mkdir -p $REPORT_DIR

# Generate HTML coverage report
echo "Generating HTML coverage report..."
gcovr -r $ZEPHYR_BASE . \
  --html -o $REPORT_DIR/coverage.html \
  --html-details \
  --gcov-executable $GCOV_EXEC

# Open report directory
cd $REPORT_DIR

