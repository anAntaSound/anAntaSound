#pragma once

#include "anantasound_core.hpp"
#include <vector>
#include <memory>

namespace AnantaSound {

// Режимы медитации
enum class MeditationMode {
    FOCUS,          // Фокус и концентрация
    TRANSCENDENCE,  // Трансцендентность
    HEALING,        // Исцеление
    AWAKENING       // Пробуждение
};

// Интеграция сознания
class ConsciousnessIntegration {
private:
    double consciousness_level_;
    bool integration_enabled_;

public:
    ConsciousnessIntegration();
    
    // Настройка уровня сознания
    void setConsciousnessLevel(double level);
    double getConsciousnessLevel() const;
    void setIntegrationEnabled(bool enabled);
    
    // Применение модуляции сознания
    QuantumSoundField applyConsciousnessModulation(const QuantumSoundField& field) const;
};

// Генератор полей сознания
class ConsciousnessFieldGenerator {
private:
    double field_intensity_;
    bool generation_enabled_;

public:
    explicit ConsciousnessFieldGenerator(double field_intensity = 1.0);
    
    // Настройка параметров
    void setFieldIntensity(double intensity);
    double getFieldIntensity() const;
    void setGenerationEnabled(bool enabled);
    
    // Генерация полей сознания
    std::vector<QuantumSoundField> generateConsciousnessFields(
        const SphericalCoord& center_position, size_t field_count = 5) const;
};

// Анализатор когерентности сознания
class ConsciousnessCoherenceAnalyzer {
private:
    double coherence_threshold_;
    bool analysis_enabled_;

public:
    explicit ConsciousnessCoherenceAnalyzer(double coherence_threshold = 0.8);
    
    // Настройка параметров
    void setCoherenceThreshold(double threshold);
    double getCoherenceThreshold() const;
    void setAnalysisEnabled(bool enabled);
    
    // Анализ когерентности
    double analyzeCoherence(const std::vector<QuantumSoundField>& fields) const;
    std::vector<QuantumSoundField> findCoherentFields(const std::vector<QuantumSoundField>& fields) const;

private:
    // Расчет когерентности между полями
    double calculateFieldCoherence(const QuantumSoundField& field1, 
                                 const QuantumSoundField& field2) const;
};

// Руководство по медитации сознания
class ConsciousnessMeditationGuide {
private:
    MeditationMode meditation_mode_;
    bool guidance_enabled_;

public:
    ConsciousnessMeditationGuide();
    
    // Настройка режима медитации
    void setMeditationMode(MeditationMode mode);
    MeditationMode getMeditationMode() const;
    void setGuidanceEnabled(bool enabled);
    
    // Генерация полей для медитации
    std::vector<QuantumSoundField> generateMeditationFields(
        const SphericalCoord& position, double session_duration) const;

private:
    // Специализированные генераторы полей
    std::vector<QuantumSoundField> generateFocusFields(
        const SphericalCoord& position, double session_duration) const;
    std::vector<QuantumSoundField> generateTranscendenceFields(
        const SphericalCoord& position, double session_duration) const;
    std::vector<QuantumSoundField> generateHealingFields(
        const SphericalCoord& position, double session_duration) const;
    std::vector<QuantumSoundField> generateAwakeningFields(
        const SphericalCoord& position, double session_duration) const;
};

} // namespace AnantaSound
