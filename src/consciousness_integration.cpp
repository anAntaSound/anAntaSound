#include "consciousness_integration.hpp"
#include <cmath>
#include <random>
#include <algorithm>

namespace AnantaSound {

// ConsciousnessIntegration implementation
ConsciousnessIntegration::ConsciousnessIntegration()
    : consciousness_level_(0.0), integration_enabled_(true) {
}

void ConsciousnessIntegration::setConsciousnessLevel(double level) {
    consciousness_level_ = std::clamp(level, 0.0, 1.0);
}

double ConsciousnessIntegration::getConsciousnessLevel() const {
    return consciousness_level_;
}

void ConsciousnessIntegration::setIntegrationEnabled(bool enabled) {
    integration_enabled_ = enabled;
}

QuantumSoundField ConsciousnessIntegration::applyConsciousnessModulation(const QuantumSoundField& field) const {
    if (!integration_enabled_) {
        return field;
    }
    
    QuantumSoundField modulated_field = field;
    
    // Apply consciousness-based modulation
    double consciousness_factor = 1.0 + consciousness_level_ * 0.5;
    modulated_field.amplitude *= consciousness_factor;
    
    // Adjust quantum state based on consciousness
    if (consciousness_level_ > 0.7) {
        modulated_field.quantum_state = QuantumSoundState::COHERENT;
    } else if (consciousness_level_ > 0.3) {
        modulated_field.quantum_state = QuantumSoundState::SUPERPOSITION;
    }
    
    return modulated_field;
}

// ConsciousnessFieldGenerator implementation
ConsciousnessFieldGenerator::ConsciousnessFieldGenerator(double field_intensity)
    : field_intensity_(field_intensity), generation_enabled_(true) {
}

void ConsciousnessFieldGenerator::setFieldIntensity(double intensity) {
    field_intensity_ = std::clamp(intensity, 0.0, 10.0);
}

double ConsciousnessFieldGenerator::getFieldIntensity() const {
    return field_intensity_;
}

void ConsciousnessFieldGenerator::setGenerationEnabled(bool enabled) {
    generation_enabled_ = enabled;
}

std::vector<QuantumSoundField> ConsciousnessFieldGenerator::generateConsciousnessFields(
    const SphericalCoord& center_position, size_t field_count) const {
    
    if (!generation_enabled_) {
        return {};
    }
    
    std::vector<QuantumSoundField> consciousness_fields;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(-1.0, 1.0);
    
    for (size_t i = 0; i < field_count; ++i) {
        QuantumSoundField field;
        
        // Generate consciousness-based field properties
        field.amplitude = std::complex<double>(
            dist(gen) * field_intensity_,
            dist(gen) * field_intensity_
        );
        
        field.phase = dist(gen) * M_PI;
        field.frequency = 432.0 + dist(gen) * 100.0; // Sacred geometry frequency range
        field.quantum_state = QuantumSoundState::SUPERPOSITION;
        field.position = center_position;
        field.timestamp = std::chrono::high_resolution_clock::now();
        
        consciousness_fields.push_back(field);
    }
    
    return consciousness_fields;
}

// ConsciousnessCoherenceAnalyzer implementation
ConsciousnessCoherenceAnalyzer::ConsciousnessCoherenceAnalyzer(double coherence_threshold)
    : coherence_threshold_(coherence_threshold), analysis_enabled_(true) {
}

void ConsciousnessCoherenceAnalyzer::setCoherenceThreshold(double threshold) {
    coherence_threshold_ = std::clamp(threshold, 0.0, 1.0);
}

double ConsciousnessCoherenceAnalyzer::getCoherenceThreshold() const {
    return coherence_threshold_;
}

void ConsciousnessCoherenceAnalyzer::setAnalysisEnabled(bool enabled) {
    analysis_enabled_ = enabled;
}

double ConsciousnessCoherenceAnalyzer::analyzeCoherence(const std::vector<QuantumSoundField>& fields) const {
    if (!analysis_enabled_ || fields.empty()) {
        return 0.0;
    }
    
    double total_coherence = 0.0;
    size_t field_count = fields.size();
    
    for (size_t i = 0; i < field_count; ++i) {
        for (size_t j = i + 1; j < field_count; ++j) {
            double coherence = calculateFieldCoherence(fields[i], fields[j]);
            total_coherence += coherence;
        }
    }
    
    // Normalize by number of field pairs
    size_t pair_count = field_count * (field_count - 1) / 2;
    return pair_count > 0 ? total_coherence / pair_count : 0.0;
}

std::vector<QuantumSoundField> ConsciousnessCoherenceAnalyzer::findCoherentFields(
    const std::vector<QuantumSoundField>& fields) const {
    
    if (!analysis_enabled_) {
        return {};
    }
    
    std::vector<QuantumSoundField> coherent_fields;
    
    for (const auto& field : fields) {
        if (field.quantum_state == QuantumSoundState::COHERENT) {
            coherent_fields.push_back(field);
        }
    }
    
    return coherent_fields;
}

double ConsciousnessCoherenceAnalyzer::calculateFieldCoherence(const QuantumSoundField& field1, 
                                                            const QuantumSoundField& field2) const {
    // Calculate coherence based on multiple factors
    
    // Phase coherence
    double phase_diff = std::abs(field1.phase - field2.phase);
    double phase_coherence = std::cos(phase_diff);
    
    // Frequency coherence
    double freq_diff = std::abs(field1.frequency - field2.frequency);
    double freq_coherence = 1.0 / (1.0 + freq_diff / 100.0);
    
    // Amplitude coherence
    double amp1 = std::abs(field1.amplitude);
    double amp2 = std::abs(field2.amplitude);
    double amp_coherence = 1.0 - std::abs(amp1 - amp2) / std::max(amp1, amp2);
    
    // Quantum state coherence
    double state_coherence = 0.0;
    if (field1.quantum_state == field2.quantum_state) {
        state_coherence = 1.0;
    } else if (field1.quantum_state == QuantumSoundState::COHERENT || 
               field2.quantum_state == QuantumSoundState::COHERENT) {
        state_coherence = 0.5;
    }
    
    // Combine coherence factors
    double total_coherence = (phase_coherence + freq_coherence + amp_coherence + state_coherence) / 4.0;
    
    return std::clamp(total_coherence, 0.0, 1.0);
}

// ConsciousnessMeditationGuide implementation
ConsciousnessMeditationGuide::ConsciousnessMeditationGuide()
    : meditation_mode_(MeditationMode::FOCUS), guidance_enabled_(true) {
}

void ConsciousnessMeditationGuide::setMeditationMode(MeditationMode mode) {
    meditation_mode_ = mode;
}

MeditationMode ConsciousnessMeditationGuide::getMeditationMode() const {
    return meditation_mode_;
}

void ConsciousnessMeditationGuide::setGuidanceEnabled(bool enabled) {
    guidance_enabled_ = enabled;
}

std::vector<QuantumSoundField> ConsciousnessMeditationGuide::generateMeditationFields(
    const SphericalCoord& position, double session_duration) const {
    
    if (!guidance_enabled_) {
        return {};
    }
    
    std::vector<QuantumSoundField> meditation_fields;
    
    switch (meditation_mode_) {
        case MeditationMode::FOCUS:
            meditation_fields = generateFocusFields(position, session_duration);
            break;
        case MeditationMode::TRANSCENDENCE:
            meditation_fields = generateTranscendenceFields(position, session_duration);
            break;
        case MeditationMode::HEALING:
            meditation_fields = generateHealingFields(position, session_duration);
            break;
        case MeditationMode::AWAKENING:
            meditation_fields = generateAwakeningFields(position, session_duration);
            break;
    }
    
    return meditation_fields;
}

std::vector<QuantumSoundField> ConsciousnessMeditationGuide::generateFocusFields(
    const SphericalCoord& position, double session_duration) const {
    
    std::vector<QuantumSoundField> focus_fields;
    
    // Generate focused, coherent fields for concentration
    for (int i = 0; i < 5; ++i) {
        QuantumSoundField field;
        field.amplitude = std::complex<double>(1.0, 0.0);
        field.phase = 0.0;
        field.frequency = 432.0 + i * 50.0; // Harmonically related frequencies
        field.quantum_state = QuantumSoundState::COHERENT;
        field.position = position;
        field.timestamp = std::chrono::high_resolution_clock::now();
        
        focus_fields.push_back(field);
    }
    
    return focus_fields;
}

std::vector<QuantumSoundField> ConsciousnessMeditationGuide::generateTranscendenceFields(
    const SphericalCoord& position, double session_duration) const {
    
    std::vector<QuantumSoundField> transcendence_fields;
    
    // Generate fields for transcendent states
    for (int i = 0; i < 7; ++i) {
        QuantumSoundField field;
        field.amplitude = std::complex<double>(0.5, 0.5);
        field.phase = i * M_PI / 4.0;
        field.frequency = 528.0 + i * 72.0; // Sacred frequencies
        field.quantum_state = QuantumSoundState::SUPERPOSITION;
        field.position = position;
        field.timestamp = std::chrono::high_resolution_clock::now();
        
        transcendence_fields.push_back(field);
    }
    
    return transcendence_fields;
}

std::vector<QuantumSoundField> ConsciousnessMeditationGuide::generateHealingFields(
    const SphericalCoord& position, double session_duration) const {
    
    std::vector<QuantumSoundField> healing_fields;
    
    // Generate healing frequencies
    std::vector<double> healing_frequencies = {396, 417, 528, 639, 741, 852, 963};
    
    for (double freq : healing_frequencies) {
        QuantumSoundField field;
        field.amplitude = std::complex<double>(0.8, 0.2);
        field.phase = 0.0;
        field.frequency = freq;
        field.quantum_state = QuantumSoundState::COHERENT;
        field.position = position;
        field.timestamp = std::chrono::high_resolution_clock::now();
        
        healing_fields.push_back(field);
    }
    
    return healing_fields;
}

std::vector<QuantumSoundField> ConsciousnessMeditationGuide::generateAwakeningFields(
    const SphericalCoord& position, double session_duration) const {
    
    std::vector<QuantumSoundField> awakening_fields;
    
    // Generate awakening frequencies
    for (int i = 0; i < 9; ++i) {
        QuantumSoundField field;
        field.amplitude = std::complex<double>(1.0, 1.0);
        field.phase = i * M_PI / 6.0;
        field.frequency = 963.0 + i * 111.0; // Higher consciousness frequencies
        field.quantum_state = QuantumSoundState::ENTANGLED;
        field.position = position;
        field.timestamp = std::chrono::high_resolution_clock::now();
        
        awakening_fields.push_back(field);
    }
    
    return awakening_fields;
}

} // namespace AnantaSound
