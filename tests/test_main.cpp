#include <iostream>
#include <cassert>

// Forward declarations of test functions
void test_consciousness_integration();
void test_consciousness_configuration();
void test_consciousness_state_transitions();
void test_quantum_feedback_system();
void test_quantum_resonance_detector();
void test_quantum_phase_synchronizer();
void test_karmic_cluster();
void test_spiritual_mercy();
void test_quantum_resonance_device();
void test_mechanical_device_manager();
void test_quantum_sound_field();
void test_interference_field();
void test_dome_acoustic_resonator();
void test_anantasound_core();

int main() {
    std::cout << "Running anAntaSound Tests..." << std::endl;
    std::cout << "================================" << std::endl;
    
    try {
        // Consciousness tests
        std::cout << "\n--- Consciousness Integration Tests ---" << std::endl;
        test_consciousness_integration();
        test_consciousness_configuration();
        test_consciousness_state_transitions();
        
        // Quantum feedback tests
        std::cout << "\n--- Quantum Feedback Tests ---" << std::endl;
        test_quantum_feedback_system();
        test_quantum_resonance_detector();
        test_quantum_phase_synchronizer();
        
        // Mechanical devices tests
        std::cout << "\n--- Mechanical Devices Tests ---" << std::endl;
        test_karmic_cluster();
        test_spiritual_mercy();
        test_quantum_resonance_device();
        test_mechanical_device_manager();
        
        // Core tests
        std::cout << "\n--- Core System Tests ---" << std::endl;
        test_quantum_sound_field();
        test_interference_field();
        test_dome_acoustic_resonator();
        test_anantasound_core();
        
        std::cout << "\n================================" << std::endl;
        std::cout << "✓ All tests passed successfully!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "\n❌ Unknown test failure occurred" << std::endl;
        return 1;
    }
}
