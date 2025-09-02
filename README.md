# anAntaSound - Quantum Acoustic Processing Library

anAntaSound is a cross-platform C++ library for quantum acoustic processing, consciousness integration, and mechanical device simulation.

## Features

- **Quantum Sound Fields**: Advanced quantum acoustic field processing with coherent, superposition, entangled, and collapsed states
- **Interference Processing**: Constructive, destructive, phase-modulated, amplitude-modulated, and quantum-entangled interference fields
- **Dome Acoustic Resonator**: 3D spherical acoustic resonance simulation with eigen frequency calculation
- **Consciousness Integration**: Meditation guidance, coherence analysis, and consciousness field generation
- **Mechanical Devices**: Karmic clusters, spiritual mercy devices, and quantum resonance devices
- **QRD Integration**: Quantum Resonance Device integration and processing
- **Cross-Platform**: Supports Linux, macOS, iOS, Android, Aurora OS, and Windows

## Supported Platforms

- **Linux** (x86_64, ARM64)
- **macOS** (Intel x86_64, Apple Silicon ARM64)
- **iOS** (Device ARM64, Simulator x86_64/ARM64)
- **Android** (ARM64-v8a, ARMv7a, x86_64, x86)
- **Aurora OS** (ARMv7hl)
- **Windows** (x86_64)

## Build Requirements

### General Requirements
- CMake 3.16 or higher
- C++17 compatible compiler
- pthread support

### Platform-Specific Requirements

#### macOS/iOS
- Xcode with command line tools
- macOS 10.15+ or iOS 12.0+

#### Android
- Android NDK 21+ (set ANDROID_NDK_ROOT environment variable)
- Android API level 21+

#### Aurora OS
- Aurora Platform SDK installed in `/opt/aurora-platform-sdk`

#### Windows
- Visual Studio 2019+ or MinGW-w64 cross-compiler

## Quick Build

### Universal Build (All Platforms)
```bash
./build_all_platforms.sh
```

### Single Platform Build
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
make install
```

## Build Options

- `BUILD_SHARED_LIBS`: Build shared libraries (default: ON)
- `BUILD_TESTS`: Build test suite (default: ON)
- `BUILD_EXAMPLES`: Build example applications (default: ON)
- `ENABLE_QUANTUM_FEEDBACK`: Enable quantum feedback system (default: ON)
- `ENABLE_MECHANICAL_DEVICES`: Enable mechanical devices (default: ON)
- `ENABLE_QRD_INTEGRATION`: Enable QRD integration (default: ON)

## Usage Example

```cpp
#include "anantasound_core.hpp"
#include "quantum_feedback_system.hpp"
#include "mechanical_devices.hpp"

using namespace AnantaSound;

int main() {
    // Initialize core system
    AnantaSoundCore core(3.0, 2.0);  // 3m radius, 2m height
    core.initialize();
    
    // Create quantum sound field
    SphericalCoord position{1.0, M_PI/4, M_PI/4, 1.0};
    auto field = core.createQuantumSoundField(432.0, position, QuantumSoundState::COHERENT);
    
    // Process through quantum feedback
    QuantumFeedbackSystem feedback(1.5, 0.7);
    auto feedback_fields = feedback.generateQuantumFeedback(field, 3);
    auto processed = feedback.processFeedback(field, feedback_fields);
    
    // Add mechanical devices
    MechanicalDeviceManager devices;
    auto karmic_cluster = std::make_shared<KarmicCluster>(position, 7);
    devices.addDevice(karmic_cluster);
    
    // Generate all fields
    auto all_fields = devices.generateAllDeviceFields();
    
    return 0;
}
```

## Testing

Run the test suite:
```bash
cd build
make test
```

Or run individual tests:
```bash
./anantasound_tests
./anantasound_demo
./quantum_acoustic_demo
./mechanical_devices_demo
```

## Integration

### CMake Integration
```cmake
find_package(anantasound REQUIRED)
target_link_libraries(your_target PRIVATE anantasound::anantasound_core)
```

### Manual Integration
Include headers and link against the library:
```cpp
#include <anantasound/anantasound_core.hpp>
// Link: -lanantasound_core -lpthread
```

## Architecture

### Core Components
- `AnantaSoundCore`: Main system coordinator
- `QuantumSoundField`: Quantum acoustic field representation
- `InterferenceField`: Field interference processing
- `DomeAcousticResonator`: 3D acoustic resonance

### Quantum Processing
- `QuantumFeedbackSystem`: Quantum feedback processing
- `QuantumResonanceDetector`: Resonance detection
- `QuantumPhaseSynchronizer`: Phase synchronization

### Consciousness Integration
- `ConsciousnessIntegration`: Consciousness modulation
- `ConsciousnessFieldGenerator`: Consciousness field generation
- `ConsciousnessMeditationGuide`: Meditation guidance

### Mechanical Devices
- `KarmicCluster`: Karmic energy cluster simulation
- `SpiritualMercy`: Spiritual mercy device
- `QuantumResonanceDevice`: Quantum resonance device

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Version

Current version: 2.1.0

## Author

anAntaSound Team
