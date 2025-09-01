#include "consciousness_integration.hpp"
#include <algorithm>
#include <numeric>
#include <random>

namespace AnantaSound {

ConsciousnessIntegration::ConsciousnessIntegration()
    : coherence_threshold_(0.7)
    , integration_depth_(5)
    , consciousness_state_(ConsciousnessState::AWARE)
    , last_update_(std::chrono::high_resolution_clock::now()) {
    
    // Initialize consciousness field
    consciousness_field_.amplitude = std::complex<double>(1.0, 0.0);
    consciousness_field_.phase = 0.0;
    consciousness_field_.frequency = 432.0; // Hz - consciousness frequency
    consciousness_field_.quantum_state = QuantumSoundState::COHERENT;
    consciousness_field_.position = SphericalCoord(0.0, 0.0, 0.0, 0.0);
}

void ConsciousnessIntegration::updateConsciousnessState(const std::vector<QuantumSoundField>& sound_fields) {
    auto now = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration<double>(now - last_update_).count();
    
    // Calculate consciousness coherence from sound fields
    double coherence = calculateConsciousnessCoherence(sound_fields);
    
    // Update consciousness state based on coherence
    if (coherence > coherence_threshold_) {
        consciousness_state_ = ConsciousnessState::COHERENT;
    } else if (coherence > 0.5) {
        consciousness_state_ = ConsciousnessState::AWARE;
    } else {
        consciousness_state_ = ConsciousnessState::DISSOCIATED;
    }
    
    // Update consciousness field
    updateConsciousnessField(sound_fields, dt);
    
    last_update_ = now;
}

double ConsciousnessIntegration::calculateConsciousnessCoherence(const std::vector<QuantumSoundField>& sound_fields) const {
    if (sound_fields.empty()) {
        return 0.0;
    }
    
    // Calculate phase coherence across all sound fields
    std::vector<double> phases;
    phases.reserve(sound_fields.size());
    
    for (const auto& field : sound_fields) {
        phases.push_back(field.phase);
    }
    
    // Calculate circular variance (measure of phase coherence)
    double mean_sin = 0.0, mean_cos = 0.0;
    for (double phase : phases) {
        mean_sin += std::sin(phase);
        mean_cos += std::cos(phase);
    }
    mean_sin /= phases.size();
    mean_cos /= phases.size();
    
    double circular_variance = 1.0 - std::sqrt(mean_sin * mean_sin + mean_cos * mean_cos);
    
    // Convert to coherence (1.0 = fully coherent, 0.0 = fully incoherent)
    return 1.0 - circular_variance;
}

void ConsciousnessIntegration::updateConsciousnessField(const std::vector<QuantumSoundField>& sound_fields, double dt) {
    if (sound_fields.empty()) {
        return;
    }
    
    // Calculate average frequency and phase from sound fields
    double avg_frequency = 0.0;
    double avg_phase = 0.0;
    std::complex<double> avg_amplitude(0.0, 0.0);
    
    for (const auto& field : sound_fields) {
        avg_frequency += field.frequency;
        avg_phase += field.phase;
        avg_amplitude += field.amplitude;
    }
    
    avg_frequency /= sound_fields.size();
    avg_phase /= sound_fields.size();
    avg_amplitude /= static_cast<double>(sound_fields.size());
    
    // Update consciousness field with weighted average
    double alpha = 0.1; // Learning rate
    consciousness_field_.frequency = (1.0 - alpha) * consciousness_field_.frequency + alpha * avg_frequency;
    consciousness_field_.phase = (1.0 - alpha) * consciousness_field_.phase + alpha * avg_phase;
    consciousness_field_.amplitude = (1.0 - alpha) * consciousness_field_.amplitude + alpha * avg_amplitude;
    
    // Update quantum state based on consciousness level
    if (consciousness_state_ == ConsciousnessState::COHERENT) {
        consciousness_field_.quantum_state = QuantumSoundState::COHERENT;
    } else if (consciousness_state_ == ConsciousnessState::AWARE) {
        consciousness_field_.quantum_state = QuantumSoundState::SUPERPOSITION;
    } else {
        consciousness_field_.quantum_state = QuantumSoundState::GROUND;
    }
}

ConsciousnessState ConsciousnessIntegration::getConsciousnessState() const {
    return consciousness_state_;
}

double ConsciousnessIntegration::getConsciousnessCoherence() const {
    return coherence_threshold_;
}

const QuantumSoundField& ConsciousnessIntegration::getConsciousnessField() const {
    return consciousness_field_;
}

void ConsciousnessIntegration::setCoherenceThreshold(double threshold) {
    coherence_threshold_ = std::clamp(threshold, 0.0, 1.0);
}

void ConsciousnessIntegration::setIntegrationDepth(int depth) {
    integration_depth_ = std::max(1, depth);
}

std::vector<double> ConsciousnessIntegration::getConsciousnessSpectrum() const {
    std::vector<double> spectrum;
    spectrum.reserve(integration_depth_);
    
    // Generate consciousness spectrum based on current state
    double base_frequency = consciousness_field_.frequency;
    
    for (int i = 0; i < integration_depth_; ++i) {
        double harmonic = base_frequency * (i + 1);
        double amplitude = consciousness_field_.amplitude.real() / (i + 1);
        
        // Apply consciousness state modulation
        switch (consciousness_state_) {
            case ConsciousnessState::COHERENT:
                amplitude *= 1.5; // Enhanced harmonics
                break;
            case ConsciousnessState::AWARE:
                amplitude *= 1.0; // Normal harmonics
                break;
            case ConsciousnessState::DISSOCIATED:
                amplitude *= 0.5; // Reduced harmonics
                break;
        }
        
        spectrum.push_back(amplitude);
    }
    
    return spectrum;
}

// Additional methods for compatibility
void ConsciousnessIntegration::updateConsciousnessLevel(double level) {
    // Update consciousness level and recalculate coherence
    double coherence = std::clamp(level, 0.0, 1.0);
    coherence_threshold_ = coherence;
    
    // Update consciousness state based on level
    if (coherence > 0.7) {
        consciousness_state_ = ConsciousnessState::COHERENT;
    } else if (coherence > 0.3) {
        consciousness_state_ = ConsciousnessState::AWARE;
    } else {
        consciousness_state_ = ConsciousnessState::DISSOCIATED;
    }
}

void ConsciousnessIntegration::setConsciousnessParameter(const std::string& param, double value) {
    if (param == "coherence_threshold") {
        setCoherenceThreshold(value);
    } else if (param == "integration_depth") {
        setIntegrationDepth(static_cast<int>(value));
    }
    // Add more parameters as needed
}

} // namespace AnantaSound
