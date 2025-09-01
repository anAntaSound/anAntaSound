#include "consciousness_integration.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace AnantaSound;

void test_consciousness_integration() {
    std::cout << "Testing ConsciousnessIntegration..." << std::endl;
    
    ConsciousnessIntegration consciousness;
    
    consciousness.setConsciousnessLevel(0.8);
    assert(std::abs(consciousness.getConsciousnessLevel() - 0.8) < 1e-6);
    
    QuantumSoundField field;
    field.amplitude = std::complex<double>(1.0, 0.0);
    field.frequency = 432.0;
    field.quantum_state = QuantumSoundState::SUPERPOSITION;
    
    auto modulated = consciousness.applyConsciousnessModulation(field);
    assert(std::abs(modulated.amplitude) > std::abs(field.amplitude));
    
    std::cout << "✓ ConsciousnessIntegration test passed" << std::endl;
}

void test_consciousness_field_generator() {
    std::cout << "Testing ConsciousnessFieldGenerator..." << std::endl;
    
    ConsciousnessFieldGenerator generator(1.5);
    
    SphericalCoord position{1.0, M_PI/4, M_PI/4, 1.0};
    auto fields = generator.generateConsciousnessFields(position, 5);
    
    assert(fields.size() == 5);
    
    std::cout << "✓ ConsciousnessFieldGenerator test passed" << std::endl;
}

void test_consciousness_coherence_analyzer() {
    std::cout << "Testing ConsciousnessCoherenceAnalyzer..." << std::endl;
    
    ConsciousnessCoherenceAnalyzer analyzer(0.7);
    
    std::vector<QuantumSoundField> fields;
    for (int i = 0; i < 3; ++i) {
        QuantumSoundField field;
        field.amplitude = std::complex<double>(1.0, 0.0);
        field.frequency = 432.0 + i * 10.0;
        field.phase = 0.0;
        field.quantum_state = QuantumSoundState::COHERENT;
        fields.push_back(field);
    }
    
    double coherence = analyzer.analyzeCoherence(fields);
    assert(coherence >= 0.0 && coherence <= 1.0);
    
    auto coherent_fields = analyzer.findCoherentFields(fields);
    assert(coherent_fields.size() == fields.size());
    
    std::cout << "✓ ConsciousnessCoherenceAnalyzer test passed" << std::endl;
}

void test_consciousness_meditation_guide() {
    std::cout << "Testing ConsciousnessMeditationGuide..." << std::endl;
    
    ConsciousnessMeditationGuide guide;
    
    guide.setMeditationMode(MeditationMode::HEALING);
    assert(guide.getMeditationMode() == MeditationMode::HEALING);
    
    SphericalCoord position{1.0, M_PI/4, M_PI/4, 1.0};
    auto meditation_fields = guide.generateMeditationFields(position, 10.0);
    
    assert(!meditation_fields.empty());
    
    std::cout << "✓ ConsciousnessMeditationGuide test passed" << std::endl;
}

int main() {
    std::cout << "Running Consciousness Integration Tests..." << std::endl;
    
    try {
        test_consciousness_integration();
        test_consciousness_field_generator();
        test_consciousness_coherence_analyzer();
        test_consciousness_meditation_guide();
        
        std::cout << "✓ All consciousness tests passed!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
