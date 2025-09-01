#!/bin/bash

# anAntaSound Aurora OS Build Script
set -e

echo "=== Building anAntaSound for Aurora OS ==="

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build/aurora"
INSTALL_DIR="${PROJECT_ROOT}/install/aurora"

# Check Aurora Platform SDK
AURORA_SDK_PATH="/opt/aurora-platform-sdk"
if [[ ! -d "${AURORA_SDK_PATH}" ]]; then
    echo "❌ Aurora Platform SDK not found at ${AURORA_SDK_PATH}"
    echo "Please install Aurora Platform SDK or update the path in this script."
    exit 1
fi

echo "Using Aurora Platform SDK: ${AURORA_SDK_PATH}"

# Source Aurora environment
if [[ -f "${AURORA_SDK_PATH}/PlatformSDK/environment-setup.sh" ]]; then
    echo "Sourcing Aurora environment..."
    source "${AURORA_SDK_PATH}/PlatformSDK/environment-setup.sh"
else
    echo "⚠ Aurora environment setup script not found, continuing with system environment"
fi

# Clean previous build
echo "Cleaning previous build..."
rm -rf "${BUILD_DIR}"
rm -rf "${INSTALL_DIR}"

# Create build directory
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

# Configure with CMake using Aurora toolchain
echo "Configuring with CMake for Aurora OS..."
cmake "${PROJECT_ROOT}" \
    -DCMAKE_TOOLCHAIN_FILE="${AURORA_SDK_PATH}/PlatformSDK/cmake/aurora.toolchain.cmake" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTS=ON \
    -DBUILD_EXAMPLES=ON \
    -DENABLE_QUANTUM_FEEDBACK=ON \
    -DENABLE_MECHANICAL_DEVICES=ON \
    -DENABLE_QRD_INTEGRATION=ON

# Build
echo "Building..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Run tests if available
if [[ -f "Makefile" ]] && grep -q "test:" Makefile; then
    echo "Running tests..."
    make test
fi

# Install
echo "Installing..."
make install

echo "✓ Aurora OS build completed successfully!"
echo "Installation directory: ${INSTALL_DIR}"

# Create distribution archive
cd "${PROJECT_ROOT}/install"
tar -czf "anantasound-aurora-armv7hl.tar.gz" "aurora"

echo "✓ Distribution archive created: anantasound-aurora-armv7hl.tar.gz"
