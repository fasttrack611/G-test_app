#!/bin/bash
set -e

# Define paths
SAMPLE_PATH="/zephyrproject/zephyr/samples/gpio_test"
GCOV_SCRIPT="/zephyrproject/zephyr/scripts/gen_gcov_files.py"
GCOV_EXEC="/zephyrproject/zephyr-sdk-0.16.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcov"
REPORT_DIR="gcov_report"
TIMEOUT=6

# Build the project
echo "Starting west build..."
west build -b qemu_x86 $SAMPLE_PATH -- -DCONFIG_COVERAGE=y -DCONFIG_COVERAGE_DUMP=y
echo "Finished west build."

# If log.log does not exist, run the test and capture output
if [ ! -f "log.log" ]; then
    echo "log.log not found. Running test and capturing output..."

    # Run ninja in the background and capture its PID
    ninja -C build run | tee log.log &
    NINJA_PID=$!

    echo "Waiting up to $TIMEOUT seconds for ninja to complete..."
    sleep $TIMEOUT

    # Check if ninja is still running
    if ps -p $NINJA_PID > /dev/null; then
        echo "ninja is still running. Sending SIGINT..."
        kill -SIGINT $NINJA_PID
        wait $NINJA_PID
    else
        echo "ninja completed within timeout."
    fi
else
    echo "log.log already exists. Skipping test run."
fi

# Proceed with coverage report generation
if [ -f "log.log" ]; then
    echo "Generating gcov files..."
    python3 $GCOV_SCRIPT -i log.log

    echo "Creating report directory..."
    mkdir -p $REPORT_DIR

    echo "Generating HTML coverage report..."
    gcovr -r $ZEPHYR_BASE . \
      --html -o $REPORT_DIR/coverage.html \
      --html-details \
      --gcov-executable $GCOV_EXEC

    echo "Coverage report generated at $REPORT_DIR/coverage.html"
else
    echo "log.log still not found. Cannot generate coverage report."
fi

