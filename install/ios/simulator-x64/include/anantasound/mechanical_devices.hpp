#pragma once

#include "anantasound_core.hpp"
#include <vector>
#include <memory>

namespace AnantaSound {

// Типы механических устройств
enum class DeviceType {
    KARMIC_CLUSTER,     // Кармический кластер
    SPIRITUAL_MERCY,    // Духовное милосердие
    QUANTUM_RESONANCE   // Квантовый резонанс
};

// Элемент кластера
struct ClusterElement {
    size_t id;
    double resonance_frequency;
    double karmic_charge;
    double healing_potential;
    bool is_active;
};

// Базовое механическое устройство
class MechanicalDevice {
protected:
    DeviceType device_type_;
    SphericalCoord position_;
    bool is_active_;
    bool vibration_enabled_;

public:
    MechanicalDevice(DeviceType type, const SphericalCoord& position);
    virtual ~MechanicalDevice() = default;
    
    // Основные свойства
    DeviceType getDeviceType() const;
    const SphericalCoord& getPosition() const;
    void setPosition(const SphericalCoord& position);
    bool isActive() const;
    void setActive(bool active);
    bool isVibrationEnabled() const;
    void setVibrationEnabled(bool enabled);
};

// Кармический кластер
class KarmicCluster : public MechanicalDevice {
private:
    size_t cluster_size_;
    double karmic_resonance_;
    bool healing_enabled_;
    std::vector<ClusterElement> cluster_elements_;

public:
    KarmicCluster(const SphericalCoord& position, size_t cluster_size = 7);
    
    // Свойства кластера
    size_t getClusterSize() const;
    double getKarmicResonance() const;
    void setKarmicResonance(double resonance);
    bool isHealingEnabled() const;
    void setHealingEnabled(bool enabled);
    
    // Управление элементами
    void updateKarmicCharge(size_t element_id, double charge);
    void activateElement(size_t element_id);
    void deactivateElement(size_t element_id);
    
    // Генерация полей
    std::vector<QuantumSoundField> generateKarmicFields() const;
};

// Духовное милосердие
class SpiritualMercy : public MechanicalDevice {
private:
    double mercy_level_;
    bool forgiveness_enabled_;
    double compassion_radius_;

public:
    SpiritualMercy(const SphericalCoord& position, double mercy_level = 0.5);
    
    // Свойства милосердия
    double getMercyLevel() const;
    void setMercyLevel(double level);
    bool isForgivenessEnabled() const;
    void setForgivenessEnabled(bool enabled);
    double getCompassionRadius() const;
    void setCompassionRadius(double radius);
    
    // Генерация полей
    std::vector<QuantumSoundField> generateMercyFields() const;
};

// Квантовое резонансное устройство
class QuantumResonanceDevice : public MechanicalDevice {
private:
    double resonance_frequency_;
    double quantum_coherence_;
    bool entanglement_enabled_;

public:
    QuantumResonanceDevice(const SphericalCoord& position, double resonance_frequency = 432.0);
    
    // Свойства резонанса
    double getResonanceFrequency() const;
    void setResonanceFrequency(double frequency);
    double getQuantumCoherence() const;
    void setQuantumCoherence(double coherence);
    bool isEntanglementEnabled() const;
    void setEntanglementEnabled(bool enabled);
    
    // Генерация полей
    std::vector<QuantumSoundField> generateResonanceFields() const;
};

// Менеджер механических устройств
class MechanicalDeviceManager {
private:
    std::vector<std::shared_ptr<MechanicalDevice>> devices_;
    size_t device_count_;
    bool auto_sync_enabled_;

public:
    MechanicalDeviceManager();
    
    // Управление устройствами
    size_t getDeviceCount() const;
    bool isAutoSyncEnabled() const;
    void setAutoSyncEnabled(bool enabled);
    void addDevice(std::shared_ptr<MechanicalDevice> device);
    void removeDevice(size_t device_id);
    std::shared_ptr<MechanicalDevice> getDevice(size_t device_id) const;
    
    // Операции с устройствами
    std::vector<QuantumSoundField> generateAllDeviceFields() const;
    void synchronizeDevices();
};

} // namespace AnantaSound
