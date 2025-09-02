#pragma once

#include "anantasound_core.hpp"
#include <vector>
#include <chrono>

namespace AnantaSound {

// QRD Integration System
class QRDIntegration {
private:
    bool qrd_active_;
    double resonance_frequency_;
    double resonance_amplitude_;
    bool quantum_entanglement_enabled_;
    QuantumSoundField qrd_field_;
    std::vector<QuantumSoundField> entangled_fields_;
    std::chrono::high_resolution_clock::time_point last_resonance_update_;

public:
    QRDIntegration();
    
    // QRD Control
    void activateQRD(double frequency, double amplitude);
    void deactivateQRD();
    bool isQRDActive() const;
    
    // Resonance Management
    void updateQRDResonance(const std::vector<QuantumSoundField>& sound_fields);
    double calculateResonanceStrength(const std::vector<QuantumSoundField>& sound_fields) const;
    void updateQRDField(double resonance_strength, double dt);
    
    // Field Generation
    std::vector<QuantumSoundField> generateResonanceFields(const SphericalCoord& position, size_t count) const;
    
    // Quantum Entanglement
    void createQuantumEntanglement(const std::vector<QuantumSoundField>& fields);
    std::vector<QuantumSoundField> getEntangledFields() const;
    
    // Getters
    const QuantumSoundField& getQRDField() const;
    double getResonanceFrequency() const;
    double getResonanceAmplitude() const;
    
    // Setters
    void setResonanceFrequency(double frequency);
    void setResonanceAmplitude(double amplitude);
    void setQuantumEntanglementEnabled(bool enabled);
    
    // Analysis
    std::vector<double> getResonanceSpectrum() const;
};

} // namespace AnantaSound
