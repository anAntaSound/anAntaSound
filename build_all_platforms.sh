#!/bin/bash

# anAntaSound Universal Build Script
# Supports: Linux, macOS, iOS, Android, Aurora OS, Windows

set -e

echo "=== anAntaSound Universal Build Script ==="
echo "Building for multiple platforms..."

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"
INSTALL_DIR="${PROJECT_ROOT}/install"

# Clean previous builds
echo "Cleaning previous builds..."
rm -rf "${BUILD_DIR}"
rm -rf "${INSTALL_DIR}"

# Function to build for specific platform
build_platform() {
    local PLATFORM=$1
    local CMAKE_ARGS=$2
    local BUILD_TYPE=${3:-Release}
    
    echo "Building for ${PLATFORM}..."
    
    local PLATFORM_BUILD_DIR="${BUILD_DIR}/${PLATFORM}"
    local PLATFORM_INSTALL_DIR="${INSTALL_DIR}/${PLATFORM}"
    
    mkdir -p "${PLATFORM_BUILD_DIR}"
    cd "${PLATFORM_BUILD_DIR}"
    
    cmake "${PROJECT_ROOT}" \
        -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
        -DCMAKE_INSTALL_PREFIX="${PLATFORM_INSTALL_DIR}" \
        ${CMAKE_ARGS}
    
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    make install
    
    echo "✓ ${PLATFORM} build completed"
    cd "${PROJECT_ROOT}"
}

# Detect host platform
detect_host_platform() {
    case "$(uname -s)" in
        Linux*)     echo "Linux";;
        Darwin*)    echo "macOS";;
        CYGWIN*|MINGW*|MSYS*) echo "Windows";;
        *)          echo "Unknown";;
    esac
}

HOST_PLATFORM=$(detect_host_platform)
echo "Host platform: ${HOST_PLATFORM}"

# Build for Linux (native or cross-compile)
echo "=== Building for Linux ==="
if command -v gcc >/dev/null 2>&1; then
    build_platform "linux-x64" "-DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++"
    echo "✓ Linux x64 build completed"
else
    echo "⚠ GCC not found, skipping Linux build"
fi

# Build for macOS (native or cross-compile)
echo "=== Building for macOS ==="
if [[ "${HOST_PLATFORM}" == "macOS" ]]; then
    build_platform "macos-x64" "-DCMAKE_OSX_ARCHITECTURES=x86_64"
    build_platform "macos-arm64" "-DCMAKE_OSX_ARCHITECTURES=arm64"
    
    # Universal binary
    echo "Creating macOS universal binary..."
    mkdir -p "${INSTALL_DIR}/macos-universal/lib"
    lipo -create \
        "${INSTALL_DIR}/macos-x64/lib/libanantasound_core.dylib" \
        "${INSTALL_DIR}/macos-arm64/lib/libanantasound_core.dylib" \
        -output "${INSTALL_DIR}/macos-universal/lib/libanantasound_core.dylib"
    
    # Copy headers
    cp -r "${INSTALL_DIR}/macos-x64/include" "${INSTALL_DIR}/macos-universal/"
    echo "✓ macOS universal build completed"
else
    echo "⚠ Not on macOS, skipping macOS build"
fi

# Build for iOS
echo "=== Building for iOS ==="
if [[ "${HOST_PLATFORM}" == "macOS" ]] && command -v xcodebuild >/dev/null 2>&1; then
    # iOS Simulator (x86_64)
    build_platform "ios-simulator-x64" "\
        -DCMAKE_SYSTEM_NAME=iOS \
        -DCMAKE_OSX_SYSROOT=iphonesimulator \
        -DCMAKE_OSX_ARCHITECTURES=x86_64 \
        -DCMAKE_OSX_DEPLOYMENT_TARGET=12.0 \
        -DBUILD_EXAMPLES=OFF \
        -DBUILD_TESTS=OFF"
    
    # iOS Simulator (arm64)
    build_platform "ios-simulator-arm64" "\
        -DCMAKE_SYSTEM_NAME=iOS \
        -DCMAKE_OSX_SYSROOT=iphonesimulator \
        -DCMAKE_OSX_ARCHITECTURES=arm64 \
        -DCMAKE_OSX_DEPLOYMENT_TARGET=12.0 \
        -DBUILD_EXAMPLES=OFF \
        -DBUILD_TESTS=OFF"
    
    # iOS Device (arm64)
    build_platform "ios-device-arm64" "\
        -DCMAKE_SYSTEM_NAME=iOS \
        -DCMAKE_OSX_SYSROOT=iphoneos \
        -DCMAKE_OSX_ARCHITECTURES=arm64 \
        -DCMAKE_OSX_DEPLOYMENT_TARGET=12.0 \
        -DBUILD_EXAMPLES=OFF \
        -DBUILD_TESTS=OFF"
    
    echo "✓ iOS builds completed"
else
    echo "⚠ iOS build requires macOS with Xcode, skipping"
fi

# Build for Android
echo "=== Building for Android ==="
if [[ -n "${ANDROID_NDK_ROOT}" ]] || [[ -n "${ANDROID_NDK}" ]]; then
    NDK_PATH="${ANDROID_NDK_ROOT:-${ANDROID_NDK}}"
    
    for ABI in "arm64-v8a" "armeabi-v7a" "x86_64" "x86"; do
        echo "Building Android ${ABI}..."
        build_platform "android-${ABI}" "\
            -DCMAKE_TOOLCHAIN_FILE=${NDK_PATH}/build/cmake/android.toolchain.cmake \
            -DANDROID_ABI=${ABI} \
            -DANDROID_PLATFORM=android-21 \
            -DANDROID_STL=c++_shared \
            -DBUILD_EXAMPLES=OFF \
            -DBUILD_TESTS=OFF"
    done
    echo "✓ Android builds completed"
else
    echo "⚠ ANDROID_NDK_ROOT not set, skipping Android build"
fi

# Build for Aurora OS (if toolchain available)
echo "=== Building for Aurora OS ==="
if [[ -d "/opt/aurora-platform-sdk" ]]; then
    source /opt/aurora-platform-sdk/PlatformSDK/environment-setup.sh
    
    build_platform "aurora-armv7hl" "\
        -DCMAKE_TOOLCHAIN_FILE=/opt/aurora-platform-sdk/PlatformSDK/cmake/aurora.toolchain.cmake \
        -DBUILD_EXAMPLES=OFF \
        -DBUILD_TESTS=OFF"
    
    echo "✓ Aurora OS build completed"
else
    echo "⚠ Aurora Platform SDK not found, skipping Aurora build"
fi

# Build for Windows (cross-compile from Linux/macOS)
echo "=== Building for Windows ==="
if command -v x86_64-w64-mingw32-gcc >/dev/null 2>&1; then
    build_platform "windows-x64" "\
        -DCMAKE_SYSTEM_NAME=Windows \
        -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
        -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ \
        -DCMAKE_RC_COMPILER=x86_64-w64-mingw32-windres"
    
    echo "✓ Windows build completed"
elif [[ "${HOST_PLATFORM}" == "Windows" ]]; then
    # Native Windows build with MSVC
    build_platform "windows-x64" "-G \"Visual Studio 16 2019\" -A x64"
    echo "✓ Windows build completed"
else
    echo "⚠ MinGW cross-compiler not found, skipping Windows build"
fi

echo ""
echo "=== Build Summary ==="
echo "Built platforms:"
for dir in "${INSTALL_DIR}"/*; do
    if [[ -d "$dir" ]]; then
        platform=$(basename "$dir")
        lib_count=$(find "$dir" -name "*.so" -o -name "*.dylib" -o -name "*.dll" -o -name "*.a" | wc -l)
        echo "  ✓ ${platform} (${lib_count} libraries)"
    fi
done

echo ""
echo "Installation directory: ${INSTALL_DIR}"
echo "Build completed successfully!"

# Create distribution archives
echo "Creating distribution archives..."
cd "${INSTALL_DIR}"
for dir in */; do
    if [[ -d "$dir" ]]; then
        platform=$(basename "$dir")
        echo "Creating archive for ${platform}..."
        tar -czf "anantasound-${platform}.tar.gz" "$dir"
    fi
done

echo "✓ Distribution archives created"
echo "=== Build process completed ==="
