#include "quantum_feedback_system.hpp"
#include <cmath>
#include <random>
#include <algorithm>

namespace AnantaSound {

// QuantumFeedbackSystem implementation
QuantumFeedbackSystem::QuantumFeedbackSystem(double feedback_gain, double quantum_threshold)
    : feedback_gain_(feedback_gain), quantum_threshold_(quantum_threshold), 
      feedback_enabled_(true), quantum_mode_(true) {
}

void QuantumFeedbackSystem::setFeedbackGain(double gain) {
    feedback_gain_ = std::clamp(gain, 0.0, 10.0);
}

double QuantumFeedbackSystem::getFeedbackGain() const {
    return feedback_gain_;
}

void QuantumFeedbackSystem::setQuantumThreshold(double threshold) {
    quantum_threshold_ = std::clamp(threshold, 0.0, 1.0);
}

double QuantumFeedbackSystem::getQuantumThreshold() const {
    return quantum_threshold_;
}

void QuantumFeedbackSystem::setFeedbackEnabled(bool enabled) {
    feedback_enabled_ = enabled;
}

void QuantumFeedbackSystem::setQuantumMode(bool enabled) {
    quantum_mode_ = enabled;
}

QuantumSoundField QuantumFeedbackSystem::processFeedback(const QuantumSoundField& input_field, 
                                                       const std::vector<QuantumSoundField>& feedback_fields) {
    if (!feedback_enabled_) {
        return input_field;
    }
    
    QuantumSoundField output_field = input_field;
    
    if (quantum_mode_ && !feedback_fields.empty()) {
        // Quantum feedback processing
        std::complex<double> quantum_feedback(0.0, 0.0);
        
        for (const auto& fb_field : feedback_fields) {
            // Calculate quantum correlation
            double correlation = calculateQuantumCorrelation(input_field, fb_field);
            
            if (correlation > quantum_threshold_) {
                // Apply quantum feedback
                std::complex<double> feedback_contribution = fb_field.amplitude * 
                    std::exp(std::complex<double>(0.0, fb_field.phase));
                
                quantum_feedback += feedback_contribution * correlation;
            }
        }
        
        // Apply quantum feedback with gain
        output_field.amplitude += quantum_feedback * feedback_gain_;
        
        // Update quantum state based on feedback
        if (std::abs(quantum_feedback.real()) > quantum_threshold_) {
            output_field.quantum_state = QuantumSoundState::ENTANGLED;
        }
    } else {
        // Classical feedback processing
        std::complex<double> classical_feedback(0.0, 0.0);
        
        for (const auto& fb_field : feedback_fields) {
            classical_feedback += fb_field.amplitude * 
                std::exp(std::complex<double>(0.0, fb_field.phase));
        }
        
        // Apply classical feedback
        output_field.amplitude += classical_feedback * feedback_gain_;
    }
    
    return output_field;
}

double QuantumFeedbackSystem::calculateQuantumCorrelation(const QuantumSoundField& field1, 
                                                        const QuantumSoundField& field2) const {
    // Calculate quantum correlation based on state similarity
    double correlation = 0.0;
    
    // Phase correlation
    double phase_diff = std::abs(field1.phase - field2.phase);
    double phase_corr = std::cos(phase_diff);
    
    // Frequency correlation
    double freq_diff = std::abs(field1.frequency - field2.frequency);
    double freq_corr = 1.0 / (1.0 + freq_diff / 1000.0); // Normalize to reasonable range
    
    // Quantum state correlation
    double state_corr = 0.0;
    if (field1.quantum_state == field2.quantum_state) {
        state_corr = 1.0;
    } else if ((field1.quantum_state == QuantumSoundState::ENTANGLED && 
                field2.quantum_state == QuantumSoundState::ENTANGLED) ||
               (field1.quantum_state == QuantumSoundState::SUPERPOSITION && 
                field2.quantum_state == QuantumSoundState::SUPERPOSITION)) {
        state_corr = 0.7;
    } else {
        state_corr = 0.3;
    }
    
    // Combine correlations
    correlation = (phase_corr + freq_corr + state_corr) / 3.0;
    
    return std::clamp(correlation, 0.0, 1.0);
}

std::vector<QuantumSoundField> QuantumFeedbackSystem::generateQuantumFeedback(const QuantumSoundField& input_field, 
                                                                             size_t feedback_count) {
    std::vector<QuantumSoundField> feedback_fields;
    
    if (!quantum_mode_) {
        return feedback_fields;
    }
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::normal_distribution<double> noise(0.0, 0.1);
    
    for (size_t i = 0; i < feedback_count; ++i) {
        QuantumSoundField feedback_field = input_field;
        
        // Add quantum noise
        feedback_field.amplitude += std::complex<double>(noise(gen), noise(gen));
        
        // Slight frequency variation
        feedback_field.frequency += noise(gen) * 10.0;
        
        // Phase shift
        feedback_field.phase += noise(gen) * M_PI / 8.0;
        
        // Quantum state variation
        if (noise(gen) > 0.5) {
            feedback_field.quantum_state = QuantumSoundState::SUPERPOSITION;
        }
        
        feedback_fields.push_back(feedback_field);
    }
    
    return feedback_fields;
}

void QuantumFeedbackSystem::resetFeedback() {
    // Reset feedback state
    feedback_gain_ = 1.0;
    quantum_threshold_ = 0.5;
}

// QuantumResonanceDetector implementation
QuantumResonanceDetector::QuantumResonanceDetector(double resonance_threshold)
    : resonance_threshold_(resonance_threshold), detection_enabled_(true) {
}

void QuantumResonanceDetector::setResonanceThreshold(double threshold) {
    resonance_threshold_ = std::clamp(threshold, 0.0, 1.0);
}

double QuantumResonanceDetector::getResonanceThreshold() const {
    return resonance_threshold_;
}

void QuantumResonanceDetector::setDetectionEnabled(bool enabled) {
    detection_enabled_ = enabled;
}

bool QuantumResonanceDetector::detectResonance(const QuantumSoundField& field) const {
    if (!detection_enabled_) {
        return false;
    }
    
    // Check amplitude threshold
    double amplitude_magnitude = std::abs(field.amplitude);
    if (amplitude_magnitude < resonance_threshold_) {
        return false;
    }
    
    // Check quantum state coherence
    if (field.quantum_state == QuantumSoundState::COHERENT) {
        return true;
    }
    
    // Check phase stability
    if (std::abs(field.phase) < M_PI / 4.0) {
        return true;
    }
    
    return false;
}

std::vector<double> QuantumResonanceDetector::findResonantFrequencies(const std::vector<QuantumSoundField>& fields) const {
    std::vector<double> resonant_frequencies;
    
    for (const auto& field : fields) {
        if (detectResonance(field)) {
            resonant_frequencies.push_back(field.frequency);
        }
    }
    
    // Remove duplicates and sort
    std::sort(resonant_frequencies.begin(), resonant_frequencies.end());
    resonant_frequencies.erase(std::unique(resonant_frequencies.begin(), resonant_frequencies.end()), 
                              resonant_frequencies.end());
    
    return resonant_frequencies;
}

// QuantumPhaseSynchronizer implementation
QuantumPhaseSynchronizer::QuantumPhaseSynchronizer(double sync_tolerance)
    : sync_tolerance_(sync_tolerance), sync_enabled_(true) {
}

void QuantumPhaseSynchronizer::setSyncTolerance(double tolerance) {
    sync_tolerance_ = std::clamp(tolerance, 0.0, M_PI);
}

double QuantumPhaseSynchronizer::getSyncTolerance() const {
    return sync_tolerance_;
}

void QuantumPhaseSynchronizer::setSyncEnabled(bool enabled) {
    sync_enabled_ = enabled;
}

std::vector<QuantumSoundField> QuantumPhaseSynchronizer::synchronizePhases(const std::vector<QuantumSoundField>& fields) const {
    if (!sync_enabled_ || fields.empty()) {
        return fields;
    }
    
    std::vector<QuantumSoundField> synchronized_fields = fields;
    
    // Find reference phase (average of coherent fields)
    double reference_phase = 0.0;
    int coherent_count = 0;
    
    for (const auto& field : fields) {
        if (field.quantum_state == QuantumSoundState::COHERENT) {
            reference_phase += field.phase;
            coherent_count++;
        }
    }
    
    if (coherent_count > 0) {
        reference_phase /= coherent_count;
    } else {
        // Use first field as reference if no coherent fields
        reference_phase = fields[0].phase;
    }
    
    // Synchronize all fields to reference phase
    for (auto& field : synchronized_fields) {
        double phase_diff = field.phase - reference_phase;
        
        // Normalize phase difference to [-π, π]
        while (phase_diff > M_PI) phase_diff -= 2.0 * M_PI;
        while (phase_diff < -M_PI) phase_diff += 2.0 * M_PI;
        
        // Apply phase correction if within tolerance
        if (std::abs(phase_diff) > sync_tolerance_) {
            field.phase = reference_phase;
            
            // Update quantum state to coherent if synchronized
            if (field.quantum_state == QuantumSoundState::SUPERPOSITION) {
                field.quantum_state = QuantumSoundState::COHERENT;
            }
        }
    }
    
    return synchronized_fields;
}

} // namespace AnantaSound
