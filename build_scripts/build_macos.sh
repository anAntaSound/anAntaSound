#!/bin/bash

# anAntaSound macOS Build Script
set -e

echo "=== Building anAntaSound for macOS ==="

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build/macos"
INSTALL_DIR="${PROJECT_ROOT}/install/macos"

# Clean previous build
echo "Cleaning previous build..."
rm -rf "${BUILD_DIR}"
rm -rf "${INSTALL_DIR}"

# Build for x86_64
echo "Building for x86_64..."
BUILD_DIR_X64="${BUILD_DIR}/x64"
INSTALL_DIR_X64="${INSTALL_DIR}/x64"

mkdir -p "${BUILD_DIR_X64}"
cd "${BUILD_DIR_X64}"

cmake "${PROJECT_ROOT}" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR_X64}" \
    -DCMAKE_OSX_ARCHITECTURES=x86_64 \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_EXAMPLES=ON \
    -DENABLE_QUANTUM_FEEDBACK=ON \
    -DENABLE_MECHANICAL_DEVICES=ON \
    -DENABLE_QRD_INTEGRATION=ON

make -j$(sysctl -n hw.ncpu)
make install

# Build for ARM64
echo "Building for ARM64..."
BUILD_DIR_ARM64="${BUILD_DIR}/arm64"
INSTALL_DIR_ARM64="${INSTALL_DIR}/arm64"

mkdir -p "${BUILD_DIR_ARM64}"
cd "${BUILD_DIR_ARM64}"

cmake "${PROJECT_ROOT}" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR_ARM64}" \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_EXAMPLES=ON \
    -DENABLE_QUANTUM_FEEDBACK=ON \
    -DENABLE_MECHANICAL_DEVICES=ON \
    -DENABLE_QRD_INTEGRATION=ON

make -j$(sysctl -n hw.ncpu)
make install

# Create universal binary
echo "Creating universal binary..."
mkdir -p "${INSTALL_DIR}/universal/lib"

# Merge libraries
lipo -create \
    "${INSTALL_DIR_X64}/lib/libanantasound_core.dylib" \
    "${INSTALL_DIR_ARM64}/lib/libanantasound_core.dylib" \
    -output "${INSTALL_DIR}/universal/lib/libanantasound_core.dylib"

# Copy headers
cp -r "${INSTALL_DIR_X64}/include" "${INSTALL_DIR}/universal/"

echo "✓ macOS build completed successfully!"
echo "Installation directory: ${INSTALL_DIR}"

# Create distribution archives
cd "${PROJECT_ROOT}/install"
tar -czf "anantasound-macos-x64.tar.gz" "macos/x64"
tar -czf "anantasound-macos-arm64.tar.gz" "macos/arm64"
tar -czf "anantasound-macos-universal.tar.gz" "macos/universal"

echo "✓ Distribution archives created:"
echo "  - anantasound-macos-x64.tar.gz"
echo "  - anantasound-macos-arm64.tar.gz"
echo "  - anantasound-macos-universal.tar.gz"
