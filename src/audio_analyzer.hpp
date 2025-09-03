#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <complex>
#include <chrono>

namespace AnantaSound {

// Структура для метаданных аудио файла
struct AudioMetadata {
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    int year;
    int track_number;
    std::string comment;
    std::string copyright;
    std::string software;
    
    AudioMetadata() : year(0), track_number(0) {}
};

// Структура для технической информации об аудио
struct AudioInfo {
    int sample_rate;
    int channels;
    int bits_per_sample;
    double duration_seconds;
    int64_t total_samples;
    std::string format;
    std::string codec;
    
    AudioInfo() : sample_rate(0), channels(0), bits_per_sample(0), 
                  duration_seconds(0.0), total_samples(0) {}
};

// Структура для спектрального анализа
struct SpectralData {
    std::vector<std::complex<double>> fft_data;
    std::vector<double> frequencies;
    std::vector<double> magnitudes;
    std::vector<double> phases;
    double dominant_frequency;
    double spectral_centroid;
    double spectral_rolloff;
    double spectral_bandwidth;
    
    SpectralData() : dominant_frequency(0.0), spectral_centroid(0.0), 
                     spectral_rolloff(0.0), spectral_bandwidth(0.0) {}
};

// Класс для анализа аудио файлов
class AudioAnalyzer {
private:
    std::string file_path_;
    AudioMetadata metadata_;
    AudioInfo info_;
    std::vector<float> audio_data_;
    SpectralData spectral_data_;
    bool is_loaded_;
    
public:
    AudioAnalyzer();
    ~AudioAnalyzer();
    
    // Загрузка аудио файла
    bool loadAudioFile(const std::string& file_path);
    
    // Анализ метаданных
    bool extractMetadata();
    
    // Спектральный анализ
    bool performSpectralAnalysis();
    
    // Анализ квантовых характеристик
    bool analyzeQuantumCharacteristics();
    
    // Получение информации
    const AudioMetadata& getMetadata() const { return metadata_; }
    const AudioInfo& getAudioInfo() const { return info_; }
    const SpectralData& getSpectralData() const { return spectral_data_; }
    const std::vector<float>& getAudioData() const { return audio_data_; }
    
    // Проверка загрузки
    bool isLoaded() const { return is_loaded_; }
    
    // Очистка данных
    void clear();
    
    // Экспорт результатов анализа
    bool exportAnalysisReport(const std::string& output_path);
    
private:
    // Внутренние методы анализа
    bool detectFormat(const std::string& file_path);
    bool readAudioData();
    void calculateFFT();
    void analyzeFrequencyDomain();
    void detectQuantumResonances();
};

// Утилиты для работы с аудио
namespace AudioUtils {
    
    // Конвертация между форматами
    bool convertFormat(const std::string& input_path, const std::string& output_path, 
                      const std::string& output_format);
    
    // Нормализация аудио
    bool normalizeAudio(const std::string& input_path, const std::string& output_path, 
                       double target_level_db = -1.0);
    
    // Изменение частоты дискретизации
    bool resampleAudio(const std::string& input_path, const std::string& output_path, 
                       int target_sample_rate);
    
    // Создание тестового сигнала
    bool generateTestSignal(const std::string& output_path, double frequency, 
                           double duration, double amplitude = 0.5);
    
    // Проверка качества FLAC
    bool validateFLACQuality(const std::string& file_path);
    
    // Получение информации о файле
    std::string getFileInfo(const std::string& file_path);
}

} // namespace AnantaSound
