#include "anantasound_core.hpp"
#include "mechanical_devices.hpp"
#include <iostream>
#include <memory>

using namespace AnantaSound;

int main() {
    std::cout << "Mechanical Devices Demo Application" << std::endl;
    
    // Создание менеджера механических устройств
    MechanicalDeviceManager device_manager;
    
    // Создание кармического кластера
    SphericalCoord karmic_position{2.0, M_PI/3, M_PI/6, 1.5};
    auto karmic_cluster = std::make_shared<KarmicCluster>(karmic_position, 7);
    karmic_cluster->setKarmicResonance(1.5);
    karmic_cluster->setHealingEnabled(true);
    
    device_manager.addDevice(karmic_cluster);
    std::cout << "Added Karmic Cluster with " << karmic_cluster->getClusterSize() << " elements" << std::endl;
    
    // Создание духовного милосердия
    SphericalCoord mercy_position{1.5, M_PI/4, M_PI/2, 1.0};
    auto spiritual_mercy = std::make_shared<SpiritualMercy>(mercy_position, 0.8);
    spiritual_mercy->setForgivenessEnabled(true);
    spiritual_mercy->setCompassionRadius(2.5);
    
    device_manager.addDevice(spiritual_mercy);
    std::cout << "Added Spiritual Mercy device with mercy level: " 
              << spiritual_mercy->getMercyLevel() << std::endl;
    
    // Создание квантового резонансного устройства
    SphericalCoord resonance_position{1.0, M_PI/2, 0, 2.0};
    auto quantum_resonance = std::make_shared<QuantumResonanceDevice>(resonance_position, 528.0);
    quantum_resonance->setQuantumCoherence(0.9);
    quantum_resonance->setEntanglementEnabled(true);
    
    device_manager.addDevice(quantum_resonance);
    std::cout << "Added Quantum Resonance Device at frequency: " 
              << quantum_resonance->getResonanceFrequency() << " Hz" << std::endl;
    
    std::cout << "Total devices: " << device_manager.getDeviceCount() << std::endl;
    
    // Генерация полей от всех устройств
    auto all_fields = device_manager.generateAllDeviceFields();
    std::cout << "Generated " << all_fields.size() << " quantum fields from all devices" << std::endl;
    
    // Анализ полей по типам
    size_t coherent_fields = 0;
    size_t superposition_fields = 0;
    size_t entangled_fields = 0;
    
    for (const auto& field : all_fields) {
        switch (field.quantum_state) {
            case QuantumSoundState::COHERENT:
                coherent_fields++;
                break;
            case QuantumSoundState::SUPERPOSITION:
                superposition_fields++;
                break;
            case QuantumSoundState::ENTANGLED:
                entangled_fields++;
                break;
            default:
                break;
        }
    }
    
    std::cout << "Field analysis:" << std::endl;
    std::cout << "  Coherent fields: " << coherent_fields << std::endl;
    std::cout << "  Superposition fields: " << superposition_fields << std::endl;
    std::cout << "  Entangled fields: " << entangled_fields << std::endl;
    
    // Тестирование кармического кластера
    std::cout << "\nTesting Karmic Cluster operations:" << std::endl;
    karmic_cluster->updateKarmicCharge(0, 0.5);
    karmic_cluster->updateKarmicCharge(1, -0.3);
    karmic_cluster->updateKarmicCharge(2, 0.8);
    
    auto karmic_fields = karmic_cluster->generateKarmicFields();
    std::cout << "Generated " << karmic_fields.size() << " karmic fields" << std::endl;
    
    // Синхронизация устройств
    device_manager.synchronizeDevices();
    std::cout << "Device synchronization completed" << std::endl;
    
    std::cout << "Mechanical devices demo completed successfully" << std::endl;
    
    return 0;
}
