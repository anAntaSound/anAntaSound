#!/bin/bash

# anAntaSound Android Build Script
set -e

echo "=== Building anAntaSound for Android ==="

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build/android"
INSTALL_DIR="${PROJECT_ROOT}/install/android"

# Check Android NDK
if [[ -z "${ANDROID_NDK_ROOT}" ]] && [[ -z "${ANDROID_NDK}" ]]; then
    echo "❌ ANDROID_NDK_ROOT or ANDROID_NDK environment variable not set."
    echo "Please set one of these variables to point to your Android NDK installation."
    exit 1
fi

NDK_PATH="${ANDROID_NDK_ROOT:-${ANDROID_NDK}}"
echo "Using Android NDK: ${NDK_PATH}"

# Clean previous build
echo "Cleaning previous build..."
rm -rf "${BUILD_DIR}"
rm -rf "${INSTALL_DIR}"

# Android ABIs to build for
ABIS=("arm64-v8a" "armeabi-v7a" "x86_64" "x86")

for ABI in "${ABIS[@]}"; do
    echo "Building for Android ${ABI}..."
    
    BUILD_DIR_ABI="${BUILD_DIR}/${ABI}"
    INSTALL_DIR_ABI="${INSTALL_DIR}/${ABI}"
    
    mkdir -p "${BUILD_DIR_ABI}"
    cd "${BUILD_DIR_ABI}"
    
    cmake "${PROJECT_ROOT}" \
        -DCMAKE_TOOLCHAIN_FILE="${NDK_PATH}/build/cmake/android.toolchain.cmake" \
        -DANDROID_ABI="${ABI}" \
        -DANDROID_PLATFORM=android-21 \
        -DANDROID_STL=c++_shared \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR_ABI}" \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DENABLE_QUANTUM_FEEDBACK=ON \
        -DENABLE_MECHANICAL_DEVICES=ON \
        -DENABLE_QRD_INTEGRATION=ON
    
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    make install
    
    echo "✓ Android ${ABI} build completed"
done

echo "✓ Android builds completed successfully!"
echo "Installation directory: ${INSTALL_DIR}"

# Create distribution archives
cd "${PROJECT_ROOT}/install"
for ABI in "${ABIS[@]}"; do
    tar -czf "anantasound-android-${ABI}.tar.gz" "android/${ABI}"
done

echo "✓ Distribution archives created:"
for ABI in "${ABIS[@]}"; do
    echo "  - anantasound-android-${ABI}.tar.gz"
done
