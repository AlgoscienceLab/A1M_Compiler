#!/bin/bash
# Build and run A1M Console

cd "$(dirname "$0")"

echo "Building A1M Console..."
make -C gui-console

if [ $? -eq 0 ]; then
    echo ""
    echo "Starting A1M Console..."
    echo "Press F1 for help, F9 to run, F10 to quit"
    echo ""
    sleep 1
    ./gui-console/a1m-console "$@"
else
    echo "Build failed!"
    exit 1
fi
