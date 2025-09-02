#include "mechanical_devices.hpp"
#include <iostream>
#include <cassert>
#include <cmath>
#include <memory>

using namespace AnantaSound;

void test_karmic_cluster() {
    std::cout << "Testing KarmicCluster..." << std::endl;
    
    SphericalCoord position{1.0, M_PI/4, M_PI/4, 1.0};
    KarmicCluster cluster(position, 5);
    
    assert(cluster.getClusterSize() == 5);
    assert(cluster.isActive());
    assert(cluster.getDeviceType() == DeviceType::KARMIC_CLUSTER);
    
    cluster.setKarmicResonance(1.5);
    assert(std::abs(cluster.getKarmicResonance() - 1.5) < 1e-6);
    
    cluster.updateKarmicCharge(0, 0.5);
    cluster.activateElement(1);
    cluster.deactivateElement(2);
    
    auto fields = cluster.generateKarmicFields();
    assert(!fields.empty());
    
    std::cout << "✓ KarmicCluster test passed" << std::endl;
}

void test_spiritual_mercy() {
    std::cout << "Testing SpiritualMercy..." << std::endl;
    
    SphericalCoord position{1.0, M_PI/4, M_PI/4, 1.0};
    SpiritualMercy mercy(position, 0.7);
    
    assert(std::abs(mercy.getMercyLevel() - 0.7) < 1e-6);
    assert(mercy.getDeviceType() == DeviceType::SPIRITUAL_MERCY);
    
    mercy.setCompassionRadius(2.5);
    assert(std::abs(mercy.getCompassionRadius() - 2.5) < 1e-6);
    
    auto fields = mercy.generateMercyFields();
    assert(!fields.empty());
    
    std::cout << "✓ SpiritualMercy test passed" << std::endl;
}

void test_quantum_resonance_device() {
    std::cout << "Testing QuantumResonanceDevice..." << std::endl;
    
    SphericalCoord position{1.0, M_PI/4, M_PI/4, 1.0};
    QuantumResonanceDevice device(position, 528.0);
    
    assert(std::abs(device.getResonanceFrequency() - 528.0) < 1e-6);
    assert(device.getDeviceType() == DeviceType::QUANTUM_RESONANCE);
    
    device.setQuantumCoherence(0.9);
    assert(std::abs(device.getQuantumCoherence() - 0.9) < 1e-6);
    
    auto fields = device.generateResonanceFields();
    assert(!fields.empty());
    
    std::cout << "✓ QuantumResonanceDevice test passed" << std::endl;
}

void test_mechanical_device_manager() {
    std::cout << "Testing MechanicalDeviceManager..." << std::endl;
    
    MechanicalDeviceManager manager;
    
    assert(manager.getDeviceCount() == 0);
    
    SphericalCoord position{1.0, M_PI/4, M_PI/4, 1.0};
    auto cluster = std::make_shared<KarmicCluster>(position, 3);
    auto mercy = std::make_shared<SpiritualMercy>(position, 0.5);
    
    manager.addDevice(cluster);
    manager.addDevice(mercy);
    
    assert(manager.getDeviceCount() == 2);
    
    auto device = manager.getDevice(0);
    assert(device != nullptr);
    assert(device->getDeviceType() == DeviceType::KARMIC_CLUSTER);
    
    auto all_fields = manager.generateAllDeviceFields();
    assert(!all_fields.empty());
    
    manager.synchronizeDevices();
    
    std::cout << "✓ MechanicalDeviceManager test passed" << std::endl;
}


