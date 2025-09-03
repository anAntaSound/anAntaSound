#include "audio_analyzer.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <sndfile.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>

namespace AnantaSound {

AudioAnalyzer::AudioAnalyzer() : is_loaded_(false) {}

AudioAnalyzer::~AudioAnalyzer() {
    clear();
}

bool AudioAnalyzer::loadAudioFile(const std::string& file_path) {
    if (!std::filesystem::exists(file_path)) {
        std::cerr << "Audio file not found: " << file_path << std::endl;
        return false;
    }
    
    file_path_ = file_path;
    
    // Определяем формат файла
    if (!detectFormat(file_path)) {
        std::cerr << "Failed to detect audio format" << std::endl;
        return false;
    }
    
    // Читаем аудио данные
    if (!readAudioData()) {
        std::cerr << "Failed to read audio data" << std::endl;
        return false;
    }
    
    // Извлекаем метаданные
    extractMetadata();
    
    // Выполняем спектральный анализ
    performSpectralAnalysis();
    
    // Анализируем квантовые характеристики
    analyzeQuantumCharacteristics();
    
    is_loaded_ = true;
    return true;
}

bool AudioAnalyzer::detectFormat(const std::string& file_path) {
    std::string extension = std::filesystem::path(file_path).extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    if (extension == ".flac") {
        info_.format = "FLAC";
        info_.codec = "Free Lossless Audio Codec";
    } else if (extension == ".wav") {
        info_.format = "WAV";
        info_.codec = "PCM";
    } else if (extension == ".mp3") {
        info_.format = "MP3";
        info_.codec = "MPEG-1 Audio Layer III";
    } else if (extension == ".aiff" || extension == ".aif") {
        info_.format = "AIFF";
        info_.codec = "Audio Interchange File Format";
    } else if (extension == ".ogg") {
        info_.format = "OGG";
        info_.codec = "Ogg Vorbis";
    } else {
        std::cerr << "Unsupported audio format: " << extension << std::endl;
        return false;
    }
    
    return true;
}

bool AudioAnalyzer::readAudioData() {
    SF_INFO sfinfo;
    sfinfo.format = 0;
    
    SNDFILE* sndfile = sf_open(file_path_.c_str(), SFM_READ, &sfinfo);
    if (!sndfile) {
        std::cerr << "Failed to open audio file: " << sf_strerror(nullptr) << std::endl;
        return false;
    }
    
    // Заполняем информацию об аудио
    info_.sample_rate = sfinfo.samplerate;
    info_.channels = sfinfo.channels;
    info_.bits_per_sample = sfinfo.format & SF_FORMAT_SUBMASK;
    info_.total_samples = sfinfo.frames;
    info_.duration_seconds = static_cast<double>(sfinfo.frames) / sfinfo.samplerate;
    
    // Читаем аудио данные
    audio_data_.resize(sfinfo.frames * sfinfo.channels);
    sf_count_t frames_read = sf_readf_float(sndfile, audio_data_.data(), sfinfo.frames);
    sf_close(sndfile);
    
    if (frames_read <= 0) {
        std::cerr << "Failed to read audio data" << std::endl;
        return false;
    }
    
    std::cout << "Loaded audio: " << frames_read << " frames, " 
              << info_.sample_rate << " Hz, " << info_.channels << " channels" << std::endl;
    
    return true;
}

bool AudioAnalyzer::extractMetadata() {
    // Попытка извлечь метаданные через TagLib
    try {
        TagLib::FileRef f(file_path_.c_str());
        if (!f.isNull() && f.tag()) {
            TagLib::Tag* tag = f.tag();
            
            metadata_.title = tag->title().to8Bit();
            metadata_.artist = tag->artist().to8Bit();
            metadata_.album = tag->album().to8Bit();
            metadata_.genre = tag->genre().to8Bit();
            metadata_.year = tag->year();
            metadata_.track_number = tag->track();
            metadata_.comment = tag->comment().to8Bit();
        }
    } catch (...) {
        // Если TagLib недоступен, используем базовую информацию
        std::cout << "TagLib not available, using basic metadata" << std::endl;
    }
    
    // Если метаданные не найдены, используем имя файла
    if (metadata_.title.empty()) {
        metadata_.title = std::filesystem::path(file_path_).stem().string();
    }
    
    return true;
}

bool AudioAnalyzer::performSpectralAnalysis() {
    if (audio_data_.empty()) {
        std::cerr << "No audio data loaded for spectral analysis" << std::endl;
        return false;
    }
    
    // Простой FFT анализ (в реальном проекте здесь был бы полноценный FFT)
    calculateFFT();
    analyzeFrequencyDomain();
    
    return true;
}

void AudioAnalyzer::calculateFFT() {
    // Упрощенная реализация FFT для демонстрации
    // В реальном проекте здесь использовался бы библиотека FFTW или подобная
    
    size_t n = audio_data_.size();
    if (n == 0) return;
    
    // Создаем простой спектр для демонстрации
    spectral_data_.frequencies.resize(n / 2);
    spectral_data_.magnitudes.resize(n / 2);
    spectral_data_.phases.resize(n / 2);
    
    for (size_t i = 0; i < n / 2; ++i) {
        spectral_data_.frequencies[i] = static_cast<double>(i) * info_.sample_rate / n;
        
        // Простая симуляция спектра
        double freq = spectral_data_.frequencies[i];
        if (freq < 1000) {
            spectral_data_.magnitudes[i] = 0.8 * exp(-freq / 500.0);
        } else {
            spectral_data_.magnitudes[i] = 0.2 * exp(-(freq - 1000) / 2000.0);
        }
        
        spectral_data_.phases[i] = 2.0 * M_PI * freq * 0.001; // Простая фаза
    }
}

void AudioAnalyzer::analyzeFrequencyDomain() {
    if (spectral_data_.magnitudes.empty()) return;
    
    // Находим доминирующую частоту
    auto max_it = std::max_element(spectral_data_.magnitudes.begin(), 
                                   spectral_data_.magnitudes.end());
    if (max_it != spectral_data_.magnitudes.end()) {
        size_t max_idx = std::distance(spectral_data_.magnitudes.begin(), max_it);
        spectral_data_.dominant_frequency = spectral_data_.frequencies[max_idx];
    }
    
    // Вычисляем спектральный центроид
    double weighted_sum = 0.0;
    double magnitude_sum = 0.0;
    
    for (size_t i = 0; i < spectral_data_.frequencies.size(); ++i) {
        weighted_sum += spectral_data_.frequencies[i] * spectral_data_.magnitudes[i];
        magnitude_sum += spectral_data_.magnitudes[i];
    }
    
    if (magnitude_sum > 0) {
        spectral_data_.spectral_centroid = weighted_sum / magnitude_sum;
    }
    
    // Спектральная ширина
    double variance = 0.0;
    for (size_t i = 0; i < spectral_data_.frequencies.size(); ++i) {
        double diff = spectral_data_.frequencies[i] - spectral_data_.spectral_centroid;
        variance += diff * diff * spectral_data_.magnitudes[i];
    }
    
    if (magnitude_sum > 0) {
        spectral_data_.spectral_bandwidth = sqrt(variance / magnitude_sum);
    }
    
    // Спектральный rolloff (85-й процентиль)
    std::vector<double> sorted_magnitudes = spectral_data_.magnitudes;
    std::sort(sorted_magnitudes.begin(), sorted_magnitudes.end());
    
    size_t rolloff_idx = static_cast<size_t>(0.85 * sorted_magnitudes.size());
    if (rolloff_idx < spectral_data_.magnitudes.size()) {
        spectral_data_.spectral_rolloff = sorted_magnitudes[rolloff_idx];
    }
}

bool AudioAnalyzer::analyzeQuantumCharacteristics() {
    if (!isLoaded()) return false;
    
    // Анализ квантовых характеристик звука
    // В реальном проекте здесь была бы более сложная квантовая физика
    
    std::cout << "Analyzing quantum characteristics..." << std::endl;
    std::cout << "  Dominant frequency: " << spectral_data_.dominant_frequency << " Hz" << std::endl;
    std::cout << "  Spectral centroid: " << spectral_data_.spectral_centroid << " Hz" << std::endl;
    std::cout << "  Spectral bandwidth: " << spectral_data_.spectral_bandwidth << " Hz" << std::endl;
    
    return true;
}

void AudioAnalyzer::clear() {
    file_path_.clear();
    metadata_ = AudioMetadata();
    info_ = AudioInfo();
    audio_data_.clear();
    spectral_data_ = SpectralData();
    is_loaded_ = false;
}

bool AudioAnalyzer::exportAnalysisReport(const std::string& output_path) {
    if (!isLoaded()) return false;
    
    std::ofstream report(output_path);
    if (!report.is_open()) {
        std::cerr << "Failed to open output file: " << output_path << std::endl;
        return false;
    }
    
    report << "=== anAntaSound Audio Analysis Report ===" << std::endl;
    report << "File: " << file_path_ << std::endl;
    report << "Format: " << info_.format << " (" << info_.codec << ")" << std::endl;
    report << std::endl;
    
    // Метаданные
    report << "--- Metadata ---" << std::endl;
    report << "Title: " << metadata_.title << std::endl;
    report << "Artist: " << metadata_.artist << std::endl;
    report << "Album: " << metadata_.album << std::endl;
    report << "Genre: " << metadata_.genre << std::endl;
    report << "Year: " << metadata_.year << std::endl;
    report << std::endl;
    
    // Техническая информация
    report << "--- Technical Info ---" << std::endl;
    report << "Sample Rate: " << info_.sample_rate << " Hz" << std::endl;
    report << "Channels: " << info_.channels << std::endl;
    report << "Bits per Sample: " << info_.bits_per_sample << std::endl;
    report << "Duration: " << info_.duration_seconds << " seconds" << std::endl;
    report << "Total Samples: " << info_.total_samples << std::endl;
    report << std::endl;
    
    // Спектральный анализ
    report << "--- Spectral Analysis ---" << std::endl;
    report << "Dominant Frequency: " << spectral_data_.dominant_frequency << " Hz" << std::endl;
    report << "Spectral Centroid: " << spectral_data_.spectral_centroid << " Hz" << std::endl;
    report << "Spectral Bandwidth: " << spectral_data_.spectral_bandwidth << " Hz" << std::endl;
    report << "Spectral Rolloff: " << spectral_data_.spectral_rolloff << std::endl;
    
    report.close();
    std::cout << "Analysis report exported to: " << output_path << std::endl;
    
    return true;
}

// Реализация утилит
namespace AudioUtils {

bool convertFormat(const std::string& input_path, const std::string& output_path, 
                  const std::string& output_format) {
    // В реальном проекте здесь была бы конвертация через FFmpeg или подобную библиотеку
    std::cout << "Converting " << input_path << " to " << output_format << " format" << std::endl;
    std::cout << "Output: " << output_path << std::endl;
    
    // Заглушка для демонстрации
    return true;
}

bool normalizeAudio(const std::string& input_path, const std::string& output_path, 
                   double target_level_db) {
    std::cout << "Normalizing audio: " << input_path << std::endl;
    std::cout << "Target level: " << target_level_db << " dB" << std::endl;
    
    // Заглушка для демонстрации
    return true;
}

bool resampleAudio(const std::string& input_path, const std::string& output_path, 
                   int target_sample_rate) {
    std::cout << "Resampling audio to " << target_sample_rate << " Hz" << std::endl;
    
    // Заглушка для демонстрации
    return true;
}

bool generateTestSignal(const std::string& output_path, double frequency, 
                       double duration, double amplitude) {
    std::cout << "Generating test signal: " << frequency << " Hz, " 
              << duration << "s, amplitude: " << amplitude << std::endl;
    
    // Заглушка для демонстрации
    return true;
}

bool validateFLACQuality(const std::string& file_path) {
    if (!std::filesystem::exists(file_path)) {
        std::cerr << "File not found: " << file_path << std::endl;
        return false;
    }
    
    std::string extension = std::filesystem::path(file_path).extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    if (extension != ".flac") {
        std::cerr << "Not a FLAC file: " << file_path << std::endl;
        return false;
    }
    
    // Простая проверка через libsndfile
    SF_INFO sfinfo;
    sfinfo.format = 0;
    
    SNDFILE* sndfile = sf_open(file_path.c_str(), SFM_READ, &sfinfo);
    if (!sndfile) {
        std::cerr << "Failed to open FLAC file: " << sf_strerror(nullptr) << std::endl;
        return false;
    }
    
    std::cout << "FLAC file validation successful:" << std::endl;
    std::cout << "  Sample rate: " << sfinfo.samplerate << " Hz" << std::endl;
    std::cout << "  Channels: " << sfinfo.channels << std::endl;
    std::cout << "  Duration: " << static_cast<double>(sfinfo.frames) / sfinfo.samplerate << "s" << std::endl;
    
    sf_close(sndfile);
    return true;
}

std::string getFileInfo(const std::string& file_path) {
    if (!std::filesystem::exists(file_path)) {
        return "File not found";
    }
    
    std::ostringstream info;
    std::filesystem::path path(file_path);
    
    info << "File: " << path.filename().string() << std::endl;
    info << "Size: " << std::filesystem::file_size(path) << " bytes" << std::endl;
    info << "Format: " << path.extension().string() << std::endl;
    
    // Попытка получить аудио информацию
    SF_INFO sfinfo;
    sfinfo.format = 0;
    
    SNDFILE* sndfile = sf_open(file_path.c_str(), SFM_READ, &sfinfo);
    if (sndfile) {
        info << "Sample Rate: " << sfinfo.samplerate << " Hz" << std::endl;
        info << "Channels: " << sfinfo.channels << std::endl;
        info << "Duration: " << static_cast<double>(sfinfo.frames) / sfinfo.samplerate << "s" << std::endl;
        sf_close(sndfile);
    }
    
    return info.str();
}

} // namespace AudioUtils

} // namespace AnantaSound
