#!/bin/bash

# anAntaSound iOS Build Script
set -e

echo "=== Building anAntaSound for iOS ==="

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build/ios"
INSTALL_DIR="${PROJECT_ROOT}/install/ios"

# Check if Xcode is available
if ! command -v xcodebuild >/dev/null 2>&1; then
    echo "❌ Xcode not found. iOS build requires Xcode to be installed."
    exit 1
fi

# Clean previous build
echo "Cleaning previous build..."
rm -rf "${BUILD_DIR}"
rm -rf "${INSTALL_DIR}"

# Build for iOS Simulator (x86_64)
echo "Building for iOS Simulator (x86_64)..."
BUILD_DIR_SIM_X64="${BUILD_DIR}/simulator-x64"
INSTALL_DIR_SIM_X64="${INSTALL_DIR}/simulator-x64"

mkdir -p "${BUILD_DIR_SIM_X64}"
cd "${BUILD_DIR_SIM_X64}"

cmake "${PROJECT_ROOT}" \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_SYSROOT=iphonesimulator \
    -DCMAKE_OSX_ARCHITECTURES=x86_64 \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=12.0 \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR_SIM_X64}" \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DENABLE_QUANTUM_FEEDBACK=ON \
    -DENABLE_MECHANICAL_DEVICES=ON \
    -DENABLE_QRD_INTEGRATION=ON

make -j$(sysctl -n hw.ncpu 2>/dev/null || echo 4)
make install

# Build for iOS Simulator (ARM64)
echo "Building for iOS Simulator (ARM64)..."
BUILD_DIR_SIM_ARM64="${BUILD_DIR}/simulator-arm64"
INSTALL_DIR_SIM_ARM64="${INSTALL_DIR}/simulator-arm64"

mkdir -p "${BUILD_DIR_SIM_ARM64}"
cd "${BUILD_DIR_SIM_ARM64}"

cmake "${PROJECT_ROOT}" \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_SYSROOT=iphonesimulator \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=12.0 \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR_SIM_ARM64}" \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DENABLE_QUANTUM_FEEDBACK=ON \
    -DENABLE_MECHANICAL_DEVICES=ON \
    -DENABLE_QRD_INTEGRATION=ON

make -j$(sysctl -n hw.ncpu 2>/dev/null || echo 4)
make install

# Build for iOS Device (ARM64)
echo "Building for iOS Device (ARM64)..."
BUILD_DIR_DEVICE="${BUILD_DIR}/device-arm64"
INSTALL_DIR_DEVICE="${INSTALL_DIR}/device-arm64"

mkdir -p "${BUILD_DIR_DEVICE}"
cd "${BUILD_DIR_DEVICE}"

cmake "${PROJECT_ROOT}" \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_SYSROOT=iphoneos \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=12.0 \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR_DEVICE}" \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DENABLE_QUANTUM_FEEDBACK=ON \
    -DENABLE_MECHANICAL_DEVICES=ON \
    -DENABLE_QRD_INTEGRATION=ON

make -j$(sysctl -n hw.ncpu 2>/dev/null || echo 4)
make install

# Create universal simulator library
echo "Creating universal simulator library..."
mkdir -p "${INSTALL_DIR}/simulator-universal/lib"

lipo -create \
    "${INSTALL_DIR_SIM_X64}/lib/libanantasound_core.a" \
    "${INSTALL_DIR_SIM_ARM64}/lib/libanantasound_core.a" \
    -output "${INSTALL_DIR}/simulator-universal/lib/libanantasound_core.a"

# Copy headers
cp -r "${INSTALL_DIR_SIM_X64}/include" "${INSTALL_DIR}/simulator-universal/"

echo "✓ iOS build completed successfully!"
echo "Installation directory: ${INSTALL_DIR}"

# Create distribution archives
cd "${PROJECT_ROOT}/install"
tar -czf "anantasound-ios-simulator-x64.tar.gz" "ios/simulator-x64"
tar -czf "anantasound-ios-simulator-arm64.tar.gz" "ios/simulator-arm64"
tar -czf "anantasound-ios-simulator-universal.tar.gz" "ios/simulator-universal"
tar -czf "anantasound-ios-device-arm64.tar.gz" "ios/device-arm64"

echo "✓ Distribution archives created:"
echo "  - anantasound-ios-simulator-x64.tar.gz"
echo "  - anantasound-ios-simulator-arm64.tar.gz"
echo "  - anantasound-ios-simulator-universal.tar.gz"
echo "  - anantasound-ios-device-arm64.tar.gz"
