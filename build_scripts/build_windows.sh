#!/bin/bash

# anAntaSound Windows Build Script
set -e

echo "=== Building anAntaSound for Windows ==="

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build/windows"
INSTALL_DIR="${PROJECT_ROOT}/install/windows"

# Detect host platform
HOST_PLATFORM=$(uname -s)
echo "Host platform: ${HOST_PLATFORM}"

# Clean previous build
echo "Cleaning previous build..."
rm -rf "${BUILD_DIR}"
rm -rf "${INSTALL_DIR}"

if [[ "${HOST_PLATFORM}" == "MINGW"* ]] || [[ "${HOST_PLATFORM}" == "MSYS"* ]]; then
    # Native Windows build with MinGW
    echo "Building natively on Windows with MinGW..."
    
    mkdir -p "${BUILD_DIR}"
    cd "${BUILD_DIR}"
    
    cmake "${PROJECT_ROOT}" \
        -G "MinGW Makefiles" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=ON \
        -DBUILD_EXAMPLES=ON \
        -DENABLE_QUANTUM_FEEDBACK=ON \
        -DENABLE_MECHANICAL_DEVICES=ON \
        -DENABLE_QRD_INTEGRATION=ON
    
    mingw32-make -j$(nproc 2>/dev/null || echo 4)
    mingw32-make install
    
elif [[ "${HOST_PLATFORM}" == "Linux"* ]] || [[ "${HOST_PLATFORM}" == "Darwin"* ]]; then
    # Cross-compile from Linux/macOS using MinGW
    if command -v x86_64-w64-mingw32-gcc >/dev/null 2>&1; then
        echo "Cross-compiling for Windows using MinGW..."
        
        mkdir -p "${BUILD_DIR}"
        cd "${BUILD_DIR}"
        
        cmake "${PROJECT_ROOT}" \
            -DCMAKE_SYSTEM_NAME=Windows \
            -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
            -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ \
            -DCMAKE_RC_COMPILER=x86_64-w64-mingw32-windres \
            -DCMAKE_BUILD_TYPE=Release \
            -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" \
            -DBUILD_SHARED_LIBS=ON \
            -DBUILD_TESTS=OFF \
            -DBUILD_EXAMPLES=OFF \
            -DENABLE_QUANTUM_FEEDBACK=ON \
            -DENABLE_MECHANICAL_DEVICES=ON \
            -DENABLE_QRD_INTEGRATION=ON
        
        make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
        make install
        
    else
        echo "❌ MinGW cross-compiler not found."
        echo "Please install MinGW-w64:"
        echo "  Ubuntu/Debian: sudo apt-get install mingw-w64"
        echo "  macOS: brew install mingw-w64"
        echo "  Or download from: https://www.mingw-w64.org/"
        exit 1
    fi
else
    echo "❌ Unsupported host platform: ${HOST_PLATFORM}"
    exit 1
fi

echo "✓ Windows build completed successfully!"
echo "Installation directory: ${INSTALL_DIR}"

# Create distribution archive
cd "${PROJECT_ROOT}/install"
tar -czf "anantasound-windows-x64.tar.gz" "windows"

echo "✓ Distribution archive created: anantasound-windows-x64.tar.gz"
