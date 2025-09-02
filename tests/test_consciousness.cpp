#include "consciousness_integration.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace AnantaSound;

void test_consciousness_integration() {
    std::cout << "Testing ConsciousnessIntegration..." << std::endl;
    
    ConsciousnessIntegration consciousness;
    
    // Test initial state
    assert(consciousness.getConsciousnessState() == ConsciousnessState::AWARE);
    
    // Create test sound fields
    std::vector<QuantumSoundField> sound_fields;
    for (int i = 0; i < 3; ++i) {
        QuantumSoundField field;
        field.amplitude = std::complex<double>(1.0, 0.0);
        field.frequency = 432.0 + i * 10.0;
        field.phase = 0.0;
        field.quantum_state = QuantumSoundState::COHERENT;
        sound_fields.push_back(field);
    }
    
    // Update consciousness state
    consciousness.updateConsciousnessState(sound_fields);
    
    // Test coherence calculation
    double coherence = consciousness.getConsciousnessCoherence();
    assert(coherence >= 0.0 && coherence <= 1.0);
    
    // Test consciousness field
    const auto& consciousness_field = consciousness.getConsciousnessField();
    assert(consciousness_field.frequency > 0.0);
    
    // Test consciousness spectrum
    auto spectrum = consciousness.getConsciousnessSpectrum();
    assert(!spectrum.empty());
    
    std::cout << "✓ ConsciousnessIntegration test passed" << std::endl;
}

void test_consciousness_configuration() {
    std::cout << "Testing ConsciousnessIntegration configuration..." << std::endl;
    
    ConsciousnessIntegration consciousness;
    
    // Test coherence threshold
    consciousness.setCoherenceThreshold(0.8);
    assert(std::abs(consciousness.getConsciousnessCoherence() - 0.8) < 1e-6);
    
    // Test integration depth
    consciousness.setIntegrationDepth(10);
    
    // Test spectrum generation with new depth
    auto spectrum = consciousness.getConsciousnessSpectrum();
    assert(spectrum.size() == 10);
    
    std::cout << "✓ ConsciousnessIntegration configuration test passed" << std::endl;
}

void test_consciousness_state_transitions() {
    std::cout << "Testing consciousness state transitions..." << std::endl;
    
    ConsciousnessIntegration consciousness;
    
    // Test with coherent fields (should lead to COHERENT state)
    std::vector<QuantumSoundField> coherent_fields;
    for (int i = 0; i < 5; ++i) {
        QuantumSoundField field;
        field.amplitude = std::complex<double>(1.0, 0.0);
        field.frequency = 432.0;
        field.phase = 0.0; // Same phase for coherence
        field.quantum_state = QuantumSoundState::COHERENT;
        coherent_fields.push_back(field);
    }
    
    consciousness.updateConsciousnessState(coherent_fields);
    assert(consciousness.getConsciousnessState() == ConsciousnessState::COHERENT);
    
    // Test with incoherent fields (should lead to DISSOCIATED state)
    std::vector<QuantumSoundField> incoherent_fields;
    for (int i = 0; i < 5; ++i) {
        QuantumSoundField field;
        field.amplitude = std::complex<double>(1.0, 0.0);
        field.frequency = 432.0 + i * 100.0; // Different frequencies
        field.phase = i * M_PI; // Different phases
        field.quantum_state = QuantumSoundState::GROUND;
        incoherent_fields.push_back(field);
    }
    
    consciousness.updateConsciousnessState(incoherent_fields);
    assert(consciousness.getConsciousnessState() == ConsciousnessState::DISSOCIATED);
    
    std::cout << "✓ Consciousness state transitions test passed" << std::endl;
}

int main() {
    std::cout << "Running Consciousness Integration Tests..." << std::endl;
    
    try {
        test_consciousness_integration();
        test_consciousness_configuration();
        test_consciousness_state_transitions();
        
        std::cout << "✓ All consciousness tests passed!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
