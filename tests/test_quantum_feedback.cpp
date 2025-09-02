#include "quantum_feedback_system.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace AnantaSound;

void test_quantum_feedback_system() {
    std::cout << "Testing QuantumFeedbackSystem..." << std::endl;
    
    QuantumFeedbackSystem feedback(1.5, 0.7);
    
    // Test getters
    assert(std::abs(feedback.getFeedbackGain() - 1.5) < 1e-6);
    assert(std::abs(feedback.getQuantumThreshold() - 0.7) < 1e-6);
    
    // Test setters
    feedback.setFeedbackGain(2.0);
    feedback.setQuantumThreshold(0.8);
    
    assert(std::abs(feedback.getFeedbackGain() - 2.0) < 1e-6);
    assert(std::abs(feedback.getQuantumThreshold() - 0.8) < 1e-6);
    
    std::cout << "✓ QuantumFeedbackSystem test passed" << std::endl;
}

void test_quantum_resonance_detector() {
    std::cout << "Testing QuantumResonanceDetector..." << std::endl;
    
    QuantumResonanceDetector detector(0.7);
    
    QuantumSoundField field;
    field.amplitude = std::complex<double>(0.8, 0.0);
    field.frequency = 432.0;
    field.phase = 0.0;
    field.quantum_state = QuantumSoundState::COHERENT;
    
    bool detected = detector.detectResonance(field);
    assert(detected);
    
    std::cout << "✓ QuantumResonanceDetector test passed" << std::endl;
}

void test_quantum_phase_synchronizer() {
    std::cout << "Testing QuantumPhaseSynchronizer..." << std::endl;
    
    QuantumPhaseSynchronizer sync(M_PI / 8.0);
    
    std::vector<QuantumSoundField> fields;
    for (int i = 0; i < 3; ++i) {
        QuantumSoundField field;
        field.amplitude = std::complex<double>(1.0, 0.0);
        field.frequency = 432.0;
        field.phase = i * M_PI / 6.0;
        field.quantum_state = QuantumSoundState::COHERENT;
        fields.push_back(field);
    }
    
    auto synchronized = sync.synchronizePhases(fields);
    assert(synchronized.size() == fields.size());
    
    std::cout << "✓ QuantumPhaseSynchronizer test passed" << std::endl;
}


