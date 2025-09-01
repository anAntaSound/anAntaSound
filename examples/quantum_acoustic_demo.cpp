#include "anantasound_core.hpp"
#include "quantum_feedback_system.hpp"
#include <iostream>
#include <chrono>
#include <thread>

using namespace AnantaSound;

int main() {
    std::cout << "Quantum Acoustic Demo Application" << std::endl;
    
    // Создание квантового акустического процессора
    QuantumAcousticProcessor processor(50);
    
    // Создание квантовой системы обратной связи
    QuantumFeedbackSystem feedback_system(1.5, 0.7);
    
    // Создание детектора резонанса
    QuantumResonanceDetector resonance_detector(0.8);
    
    // Создание синхронизатора фаз
    QuantumPhaseSynchronizer phase_sync(M_PI / 6.0);
    
    std::cout << "Quantum systems initialized" << std::endl;
    
    // Создание тестовых квантовых полей
    std::vector<QuantumSoundField> test_fields;
    
    for (int i = 0; i < 5; ++i) {
        QuantumSoundField field;
        field.amplitude = std::complex<double>(1.0, 0.5);
        field.phase = i * M_PI / 4.0;
        field.frequency = 432.0 + i * 111.0;
        field.quantum_state = QuantumSoundState::SUPERPOSITION;
        field.position = {1.0, i * M_PI / 8.0, i * M_PI / 4.0, 1.0};
        field.timestamp = std::chrono::high_resolution_clock::now();
        
        test_fields.push_back(field);
        processor.addField(field);
    }
    
    std::cout << "Created " << test_fields.size() << " test quantum fields" << std::endl;
    
    // Обработка через систему обратной связи
    for (auto& field : test_fields) {
        auto feedback_fields = feedback_system.generateQuantumFeedback(field, 3);
        auto processed_field = feedback_system.processFeedback(field, feedback_fields);
        
        std::cout << "Original frequency: " << field.frequency 
                  << " Hz, Processed frequency: " << processed_field.frequency << " Hz" << std::endl;
        
        // Проверка резонанса
        if (resonance_detector.detectResonance(processed_field)) {
            std::cout << "Resonance detected at " << processed_field.frequency << " Hz" << std::endl;
        }
    }
    
    // Синхронизация фаз
    auto synchronized_fields = phase_sync.synchronizePhases(test_fields);
    std::cout << "Phase synchronization completed" << std::endl;
    
    // Анализ резонантных частот
    auto resonant_frequencies = resonance_detector.findResonantFrequencies(synchronized_fields);
    std::cout << "Found " << resonant_frequencies.size() << " resonant frequencies:" << std::endl;
    for (double freq : resonant_frequencies) {
        std::cout << "  " << freq << " Hz" << std::endl;
    }
    
    std::cout << "Quantum acoustic demo completed successfully" << std::endl;
    
    return 0;
}
