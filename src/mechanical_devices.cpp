#include "mechanical_devices.hpp"
#include <cmath>
#include <random>
#include <algorithm>

namespace AnantaSound {

// MechanicalDevice implementation
MechanicalDevice::MechanicalDevice(DeviceType type, const SphericalCoord& position)
    : device_type_(type), position_(position), is_active_(true), vibration_enabled_(true) {
}

DeviceType MechanicalDevice::getDeviceType() const {
    return device_type_;
}

const SphericalCoord& MechanicalDevice::getPosition() const {
    return position_;
}

void MechanicalDevice::setPosition(const SphericalCoord& position) {
    position_ = position;
}

bool MechanicalDevice::isActive() const {
    return is_active_;
}

void MechanicalDevice::setActive(bool active) {
    is_active_ = active;
}

bool MechanicalDevice::isVibrationEnabled() const {
    return vibration_enabled_;
}

void MechanicalDevice::setVibrationEnabled(bool enabled) {
    vibration_enabled_ = enabled;
}

// KarmicCluster implementation
KarmicCluster::KarmicCluster(const SphericalCoord& position, size_t cluster_size)
    : MechanicalDevice(DeviceType::KARMIC_CLUSTER, position), cluster_size_(cluster_size),
      karmic_resonance_(1.0), healing_enabled_(true) {
    
    // Initialize cluster elements
    for (size_t i = 0; i < cluster_size_; ++i) {
        ClusterElement element;
        element.id = i;
        element.resonance_frequency = 432.0 + i * 111.0; // Sacred geometry frequencies
        element.karmic_charge = 0.0;
        element.healing_potential = 1.0;
        element.is_active = true;
        
        cluster_elements_.push_back(element);
    }
}

size_t KarmicCluster::getClusterSize() const {
    return cluster_size_;
}

double KarmicCluster::getKarmicResonance() const {
    return karmic_resonance_;
}

void KarmicCluster::setKarmicResonance(double resonance) {
    karmic_resonance_ = std::clamp(resonance, 0.0, 10.0);
}

bool KarmicCluster::isHealingEnabled() const {
    return healing_enabled_;
}

void KarmicCluster::setHealingEnabled(bool enabled) {
    healing_enabled_ = enabled;
}

std::vector<QuantumSoundField> KarmicCluster::generateKarmicFields() const {
    if (!isActive() || !healing_enabled_) {
        return {};
    }
    
    std::vector<QuantumSoundField> karmic_fields;
    
    for (const auto& element : cluster_elements_) {
        if (!element.is_active) continue;
        
        QuantumSoundField field;
        field.amplitude = std::complex<double>(
            element.healing_potential * karmic_resonance_,
            element.karmic_charge * karmic_resonance_
        );
        field.phase = element.karmic_charge * M_PI;
        field.frequency = element.resonance_frequency;
        field.quantum_state = QuantumSoundState::COHERENT;
        field.position = position_;
        field.timestamp = std::chrono::high_resolution_clock::now();
        
        karmic_fields.push_back(field);
    }
    
    return karmic_fields;
}

void KarmicCluster::updateKarmicCharge(size_t element_id, double charge) {
    if (element_id < cluster_elements_.size()) {
        cluster_elements_[element_id].karmic_charge = std::clamp(charge, -1.0, 1.0);
    }
}

void KarmicCluster::activateElement(size_t element_id) {
    if (element_id < cluster_elements_.size()) {
        cluster_elements_[element_id].is_active = true;
    }
}

void KarmicCluster::deactivateElement(size_t element_id) {
    if (element_id < cluster_elements_.size()) {
        cluster_elements_[element_id].is_active = false;
    }
}

// SpiritualMercy implementation
SpiritualMercy::SpiritualMercy(const SphericalCoord& position, double mercy_level)
    : MechanicalDevice(DeviceType::SPIRITUAL_MERCY, position), mercy_level_(mercy_level),
      forgiveness_enabled_(true), compassion_radius_(1.0) {
}

double SpiritualMercy::getMercyLevel() const {
    return mercy_level_;
}

void SpiritualMercy::setMercyLevel(double level) {
    mercy_level_ = std::clamp(level, 0.0, 1.0);
}

bool SpiritualMercy::isForgivenessEnabled() const {
    return forgiveness_enabled_;
}

void SpiritualMercy::setForgivenessEnabled(bool enabled) {
    forgiveness_enabled_ = enabled;
}

double SpiritualMercy::getCompassionRadius() const {
    return compassion_radius_;
}

void SpiritualMercy::setCompassionRadius(double radius) {
    compassion_radius_ = std::clamp(radius, 0.1, 10.0);
}

std::vector<QuantumSoundField> SpiritualMercy::generateMercyFields() const {
    if (!isActive() || !forgiveness_enabled_) {
        return {};
    }
    
    std::vector<QuantumSoundField> mercy_fields;
    
    // Generate mercy fields based on mercy level
    for (int i = 0; i < 7; ++i) { // Seven chakras
        QuantumSoundField field;
        
        // Mercy amplitude based on level
        field.amplitude = std::complex<double>(
            mercy_level_ * (1.0 + i * 0.1),
            mercy_level_ * (0.5 + i * 0.05)
        );
        
        // Chakra frequencies
        std::vector<double> chakra_frequencies = {396, 417, 528, 639, 741, 852, 963};
        field.frequency = chakra_frequencies[i % chakra_frequencies.size()];
        
        field.phase = i * M_PI / 7.0;
        field.quantum_state = QuantumSoundState::SUPERPOSITION;
        field.position = position_;
        field.timestamp = std::chrono::high_resolution_clock::now();
        
        mercy_fields.push_back(field);
    }
    
    return mercy_fields;
}

// QuantumResonanceDevice implementation
QuantumResonanceDevice::QuantumResonanceDevice(const SphericalCoord& position, double resonance_frequency)
    : MechanicalDevice(DeviceType::QUANTUM_RESONANCE, position), resonance_frequency_(resonance_frequency),
      quantum_coherence_(1.0), entanglement_enabled_(true) {
}

double QuantumResonanceDevice::getResonanceFrequency() const {
    return resonance_frequency_;
}

void QuantumResonanceDevice::setResonanceFrequency(double frequency) {
    resonance_frequency_ = std::clamp(frequency, 1.0, 10000.0);
}

double QuantumResonanceDevice::getQuantumCoherence() const {
    return quantum_coherence_;
}

void QuantumResonanceDevice::setQuantumCoherence(double coherence) {
    quantum_coherence_ = std::clamp(coherence, 0.0, 1.0);
}

bool QuantumResonanceDevice::isEntanglementEnabled() const {
    return entanglement_enabled_;
}

void QuantumResonanceDevice::setEntanglementEnabled(bool enabled) {
    entanglement_enabled_ = enabled;
}

std::vector<QuantumSoundField> QuantumResonanceDevice::generateResonanceFields() const {
    if (!isActive()) {
        return {};
    }
    
    std::vector<QuantumSoundField> resonance_fields;
    
    // Generate harmonic resonance fields
    for (int harmonic = 1; harmonic <= 8; ++harmonic) {
        QuantumSoundField field;
        
        double harmonic_freq = resonance_frequency_ * harmonic;
        double harmonic_amplitude = quantum_coherence_ / harmonic;
        
        field.amplitude = std::complex<double>(harmonic_amplitude, 0.0);
        field.frequency = harmonic_freq;
        field.phase = harmonic * M_PI / 4.0;
        
        // Set quantum state based on coherence
        if (quantum_coherence_ > 0.8) {
            field.quantum_state = QuantumSoundState::COHERENT;
        } else if (quantum_coherence_ > 0.5) {
            field.quantum_state = QuantumSoundState::SUPERPOSITION;
        } else {
            field.quantum_state = QuantumSoundState::COLLAPSED;
        }
        
        field.position = position_;
        field.timestamp = std::chrono::high_resolution_clock::now();
        
        resonance_fields.push_back(field);
    }
    
    return resonance_fields;
}

// MechanicalDeviceManager implementation
MechanicalDeviceManager::MechanicalDeviceManager()
    : device_count_(0), auto_sync_enabled_(true) {
}

size_t MechanicalDeviceManager::getDeviceCount() const {
    return device_count_;
}

bool MechanicalDeviceManager::isAutoSyncEnabled() const {
    return auto_sync_enabled_;
}

void MechanicalDeviceManager::setAutoSyncEnabled(bool enabled) {
    auto_sync_enabled_ = enabled;
}

void MechanicalDeviceManager::addDevice(std::shared_ptr<MechanicalDevice> device) {
    if (device) {
        devices_.push_back(device);
        device_count_ = devices_.size();
    }
}

void MechanicalDeviceManager::removeDevice(size_t device_id) {
    if (device_id < devices_.size()) {
        devices_.erase(devices_.begin() + device_id);
        device_count_ = devices_.size();
    }
}

std::shared_ptr<MechanicalDevice> MechanicalDeviceManager::getDevice(size_t device_id) const {
    if (device_id < devices_.size()) {
        return devices_[device_id];
    }
    return nullptr;
}

std::vector<QuantumSoundField> MechanicalDeviceManager::generateAllDeviceFields() const {
    std::vector<QuantumSoundField> all_fields;
    
    for (const auto& device : devices_) {
        if (!device || !device->isActive()) continue;
        
        std::vector<QuantumSoundField> device_fields;
        
        // Generate fields based on device type
        switch (device->getDeviceType()) {
            case DeviceType::KARMIC_CLUSTER: {
                auto karmic_device = std::dynamic_pointer_cast<KarmicCluster>(device);
                if (karmic_device) {
                    device_fields = karmic_device->generateKarmicFields();
                }
                break;
            }
            case DeviceType::SPIRITUAL_MERCY: {
                auto mercy_device = std::dynamic_pointer_cast<SpiritualMercy>(device);
                if (mercy_device) {
                    device_fields = mercy_device->generateMercyFields();
                }
                break;
            }
            case DeviceType::QUANTUM_RESONANCE: {
                auto resonance_device = std::dynamic_pointer_cast<QuantumResonanceDevice>(device);
                if (resonance_device) {
                    device_fields = resonance_device->generateResonanceFields();
                }
                break;
            }
        }
        
        // Add device fields to total
        all_fields.insert(all_fields.end(), device_fields.begin(), device_fields.end());
    }
    
    return all_fields;
}

void MechanicalDeviceManager::synchronizeDevices() {
    if (!auto_sync_enabled_) return;
    
    // Simple device synchronization
    for (auto& device : devices_) {
        if (device && device->isActive()) {
            // Update device states based on other devices
            // This is a simplified synchronization
        }
    }
}

} // namespace AnantaSound
