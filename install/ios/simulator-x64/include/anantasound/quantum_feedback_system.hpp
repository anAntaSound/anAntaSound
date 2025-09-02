#pragma once

#include "anantasound_core.hpp"
#include <vector>
#include <memory>

namespace AnantaSound {

// Квантовая система обратной связи
class QuantumFeedbackSystem {
private:
    double feedback_gain_;
    double quantum_threshold_;
    bool feedback_enabled_;
    bool quantum_mode_;

public:
    explicit QuantumFeedbackSystem(double feedback_gain = 1.0, double quantum_threshold = 0.5);
    
    // Настройка параметров
    void setFeedbackGain(double gain);
    double getFeedbackGain() const;
    void setQuantumThreshold(double threshold);
    double getQuantumThreshold() const;
    void setFeedbackEnabled(bool enabled);
    void setQuantumMode(bool enabled);
    
    // Обработка обратной связи
    QuantumSoundField processFeedback(const QuantumSoundField& input_field, 
                                    const std::vector<QuantumSoundField>& feedback_fields);
    
    // Генерация квантовой обратной связи
    std::vector<QuantumSoundField> generateQuantumFeedback(const QuantumSoundField& input_field, 
                                                          size_t feedback_count = 3);
    
    // Сброс состояния
    void resetFeedback();

private:
    // Расчет квантовой корреляции между полями
    double calculateQuantumCorrelation(const QuantumSoundField& field1, 
                                     const QuantumSoundField& field2) const;
};

// Детектор квантового резонанса
class QuantumResonanceDetector {
private:
    double resonance_threshold_;
    bool detection_enabled_;

public:
    explicit QuantumResonanceDetector(double resonance_threshold = 0.7);
    
    // Настройка параметров
    void setResonanceThreshold(double threshold);
    double getResonanceThreshold() const;
    void setDetectionEnabled(bool enabled);
    
    // Обнаружение резонанса
    bool detectResonance(const QuantumSoundField& field) const;
    std::vector<double> findResonantFrequencies(const std::vector<QuantumSoundField>& fields) const;
};

// Квантовый синхронизатор фаз
class QuantumPhaseSynchronizer {
private:
    double sync_tolerance_;
    bool sync_enabled_;

public:
    explicit QuantumPhaseSynchronizer(double sync_tolerance = M_PI / 8.0);
    
    // Настройка параметров
    void setSyncTolerance(double tolerance);
    double getSyncTolerance() const;
    void setSyncEnabled(bool enabled);
    
    // Синхронизация фаз
    std::vector<QuantumSoundField> synchronizePhases(const std::vector<QuantumSoundField>& fields) const;
};

} // namespace AnantaSound
