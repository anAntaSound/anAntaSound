#include "qrd_integration.hpp"
#include <algorithm>
#include <cmath>
#include <random>

namespace AnantaSound {

QRDIntegration::QRDIntegration()
    : qrd_active_(false)
    , resonance_frequency_(432.0)
    , resonance_amplitude_(1.0)
    , quantum_entanglement_enabled_(true)
    , last_resonance_update_(std::chrono::high_resolution_clock::now()) {
    
    // Initialize QRD field
    qrd_field_.amplitude = std::complex<double>(resonance_amplitude_, 0.0);
    qrd_field_.phase = 0.0;
    qrd_field_.frequency = resonance_frequency_;
    qrd_field_.quantum_state = QuantumSoundState::COHERENT;
    qrd_field_.position = SphericalCoord(0.0, 0.0, 0.0, 0.0);
}

void QRDIntegration::activateQRD(double frequency, double amplitude) {
    qrd_active_ = true;
    resonance_frequency_ = frequency;
    resonance_amplitude_ = amplitude;
    
    // Update QRD field
    qrd_field_.frequency = frequency;
    qrd_field_.amplitude = std::complex<double>(amplitude, 0.0);
    qrd_field_.quantum_state = QuantumSoundState::COHERENT;
    
    last_resonance_update_ = std::chrono::high_resolution_clock::now();
}

void QRDIntegration::deactivateQRD() {
    qrd_active_ = false;
    qrd_field_.amplitude = std::complex<double>(0.0, 0.0);
    qrd_field_.quantum_state = QuantumSoundState::GROUND;
}

bool QRDIntegration::isQRDActive() const {
    return qrd_active_;
}

void QRDIntegration::updateQRDResonance(const std::vector<QuantumSoundField>& sound_fields) {
    if (!qrd_active_) {
        return;
    }
    
    auto now = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration<double>(now - last_resonance_update_).count();
    
    // Calculate resonance with existing sound fields
    double resonance_strength = calculateResonanceStrength(sound_fields);
    
    // Update QRD field based on resonance
    updateQRDField(resonance_strength, dt);
    
    last_resonance_update_ = now;
}

double QRDIntegration::calculateResonanceStrength(const std::vector<QuantumSoundField>& sound_fields) const {
    if (sound_fields.empty()) {
        return 0.0;
    }
    
    double total_resonance = 0.0;
    
    for (const auto& field : sound_fields) {
        // Calculate frequency resonance
        double freq_diff = std::abs(field.frequency - resonance_frequency_);
        double freq_resonance = 1.0 / (1.0 + freq_diff / 50.0); // 50 Hz bandwidth
        
        // Calculate phase resonance
        double phase_diff = std::abs(field.phase - qrd_field_.phase);
        double phase_resonance = std::cos(phase_diff);
        
        // Calculate amplitude resonance
        double amp_resonance = std::min(field.amplitude.real() / resonance_amplitude_, 1.0);
        
        // Combine resonance factors
        double field_resonance = (freq_resonance + phase_resonance + amp_resonance) / 3.0;
        total_resonance += field_resonance;
    }
    
    return total_resonance / sound_fields.size();
}

void QRDIntegration::updateQRDField(double resonance_strength, double dt) {
    // Resonance feedback loop
    double feedback_gain = 0.1;
    double new_amplitude = resonance_amplitude_ * (1.0 + feedback_gain * resonance_strength);
    
    // Limit amplitude growth
    new_amplitude = std::min(new_amplitude, resonance_amplitude_ * 2.0);
    
    // Update QRD field
    qrd_field_.amplitude = std::complex<double>(new_amplitude, 0.0);
    
    // Phase evolution based on resonance
    double phase_evolution = resonance_strength * 2.0 * M_PI * resonance_frequency_ * dt;
    qrd_field_.phase += phase_evolution;
    
    // Normalize phase to [0, 2π]
    qrd_field_.phase = std::fmod(qrd_field_.phase, 2.0 * M_PI);
    if (qrd_field_.phase < 0.0) {
        qrd_field_.phase += 2.0 * M_PI;
    }
    
    // Update quantum state based on resonance
    if (resonance_strength > 0.8) {
        qrd_field_.quantum_state = QuantumSoundState::ENTANGLED;
    } else if (resonance_strength > 0.5) {
        qrd_field_.quantum_state = QuantumSoundState::COHERENT;
    } else {
        qrd_field_.quantum_state = QuantumSoundState::SUPERPOSITION;
    }
}

std::vector<QuantumSoundField> QRDIntegration::generateResonanceFields(const SphericalCoord& position, size_t count) const {
    if (!qrd_active_) {
        return {};
    }
    
    std::vector<QuantumSoundField> resonance_fields;
    resonance_fields.reserve(count);
    
    // Generate harmonically related resonance fields
    for (size_t i = 0; i < count; ++i) {
        QuantumSoundField field;
        
        // Harmonic frequency
        double harmonic_freq = resonance_frequency_ * (i + 1);
        
        // Harmonic amplitude (decreasing with harmonic number)
        double harmonic_amp = resonance_amplitude_ / (i + 1);
        
        // Harmonic phase
        double harmonic_phase = qrd_field_.phase * (i + 1);
        
        field.amplitude = std::complex<double>(harmonic_amp, 0.0);
        field.phase = harmonic_phase;
        field.frequency = harmonic_freq;
        field.quantum_state = qrd_field_.quantum_state;
        field.position = position;
        field.timestamp = std::chrono::high_resolution_clock::now();
        
        resonance_fields.push_back(field);
    }
    
    return resonance_fields;
}

void QRDIntegration::createQuantumEntanglement(const std::vector<QuantumSoundField>& fields) {
    if (!quantum_entanglement_enabled_ || fields.size() < 2) {
        return;
    }
    
    // Create entanglement between QRD field and sound fields
    for (const auto& field : fields) {
        // Calculate entanglement strength based on resonance
        double freq_diff = std::abs(field.frequency - resonance_frequency_);
        double entanglement_strength = 1.0 / (1.0 + freq_diff / 100.0);
        
        if (entanglement_strength > 0.7) {
            // Mark fields as entangled
            entangled_fields_.push_back(field);
        }
    }
}

std::vector<QuantumSoundField> QRDIntegration::getEntangledFields() const {
    return entangled_fields_;
}

const QuantumSoundField& QRDIntegration::getQRDField() const {
    return qrd_field_;
}

double QRDIntegration::getResonanceFrequency() const {
    return resonance_frequency_;
}

double QRDIntegration::getResonanceAmplitude() const {
    return resonance_amplitude_;
}

void QRDIntegration::setResonanceFrequency(double frequency) {
    resonance_frequency_ = frequency;
    if (qrd_active_) {
        qrd_field_.frequency = frequency;
    }
}

void QRDIntegration::setResonanceAmplitude(double amplitude) {
    resonance_amplitude_ = amplitude;
    if (qrd_active_) {
        qrd_field_.amplitude = std::complex<double>(amplitude, 0.0);
    }
}

void QRDIntegration::setQuantumEntanglementEnabled(bool enabled) {
    quantum_entanglement_enabled_ = enabled;
    if (!enabled) {
        entangled_fields_.clear();
    }
}

std::vector<double> QRDIntegration::getResonanceSpectrum() const {
    std::vector<double> spectrum;
    
    if (!qrd_active_) {
        return spectrum;
    }
    
    // Generate resonance spectrum with harmonics
    for (int i = 1; i <= 10; ++i) {
        double harmonic_freq = resonance_frequency_ * i;
        double harmonic_amp = resonance_amplitude_ / i;
        
        // Apply resonance envelope
        double envelope = std::exp(-std::pow((harmonic_freq - resonance_frequency_) / 100.0, 2));
        spectrum.push_back(harmonic_amp * envelope);
    }
    
    return spectrum;
}

} // namespace AnantaSound
