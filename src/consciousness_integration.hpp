#pragma once

#include "anantasound_core.hpp"
#include <vector>
#include <memory>

namespace AnantaSound {

// Consciousness States
enum class ConsciousnessState {
    DISSOCIATED,    // Dissociated state
    AWARE,          // Aware state
    COHERENT        // Coherent state
};

// Consciousness Integration System
class ConsciousnessIntegration {
private:
    double coherence_threshold_;
    int integration_depth_;
    ConsciousnessState consciousness_state_;
    QuantumSoundField consciousness_field_;
    std::chrono::high_resolution_clock::time_point last_update_;

public:
    ConsciousnessIntegration();
    
    // Consciousness State Management
    void updateConsciousnessState(const std::vector<QuantumSoundField>& sound_fields);
    ConsciousnessState getConsciousnessState() const;
    
    // Coherence Analysis
    double calculateConsciousnessCoherence(const std::vector<QuantumSoundField>& sound_fields) const;
    double getConsciousnessCoherence() const;
    
    // Field Management
    void updateConsciousnessField(const std::vector<QuantumSoundField>& sound_fields, double dt);
    const QuantumSoundField& getConsciousnessField() const;
    
    // Configuration
    void setCoherenceThreshold(double threshold);
    void setIntegrationDepth(int depth);
    
    // Analysis
    std::vector<double> getConsciousnessSpectrum() const;
    
    // Additional methods for compatibility
    void updateConsciousnessLevel(double level);
    void setConsciousnessParameter(const std::string& param, double value);

}; // class ConsciousnessIntegration

} // namespace AnantaSound
