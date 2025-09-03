#include "../src/audio_analyzer.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>

using namespace AnantaSound;
namespace fs = std::filesystem;

void printUsage() {
    std::cout << "anAntaSound FLAC Utility" << std::endl;
    std::cout << "Usage: flac_utility <command> [options]" << std::endl;
    std::cout << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  validate <file>     - Validate FLAC file quality" << std::endl;
    std::cout << "  info <file>         - Show detailed file information" << std::endl;
    std::cout << "  analyze <file>      - Perform full audio analysis" << std::endl;
    std::cout << "  batch <directory>   - Analyze all FLAC files in directory" << std::endl;
    std::cout << "  convert <input> <output> - Convert audio format" << std::endl;
    std::cout << "  normalize <input> <output> [level] - Normalize audio" << std::endl;
    std::cout << "  resample <input> <output> <rate> - Change sample rate" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  flac_utility validate sample.flac" << std::endl;
    std::cout << "  flac_utility info sample.flac" << std::endl;
    std::cout << "  flac_utility analyze sample.flac" << std::endl;
    std::cout << "  flac_utility batch ./samples" << std::endl;
    std::cout << "  flac_utility convert input.wav output.flac" << std::endl;
    std::cout << "  flac_utility normalize input.flac output.flac -1.0" << std::endl;
    std::cout << "  flac_utility resample input.flac output.flac 48000" << std::endl;
}

bool validateFLACFile(const std::string& filepath) {
    std::cout << "🔍 Validating FLAC file: " << filepath << std::endl;
    
    if (!fs::exists(filepath)) {
        std::cerr << "❌ File not found: " << filepath << std::endl;
        return false;
    }
    
    std::string extension = fs::path(filepath).extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    if (extension != ".flac") {
        std::cerr << "❌ Not a FLAC file: " << filepath << std::endl;
        return false;
    }
    
    // Валидация через AudioUtils
    if (AudioUtils::validateFLACQuality(filepath)) {
        std::cout << "✅ FLAC file validation successful!" << std::endl;
        
        // Дополнительная информация
        std::cout << "📊 File details:" << std::endl;
        std::cout << "  Size: " << fs::file_size(filepath) << " bytes" << std::endl;
        std::cout << "  Path: " << fs::absolute(filepath) << std::endl;
        
        return true;
    } else {
        std::cerr << "❌ FLAC file validation failed!" << std::endl;
        return false;
    }
}

void showFileInfo(const std::string& filepath) {
    std::cout << "📋 File Information: " << filepath << std::endl;
    std::cout << "=====================================" << std::endl;
    
    std::string info = AudioUtils::getFileInfo(filepath);
    std::cout << info << std::endl;
}

void analyzeAudioFile(const std::string& filepath) {
    std::cout << "🔬 Full Audio Analysis: " << filepath << std::endl;
    std::cout << "=====================================" << std::endl;
    
    AudioAnalyzer analyzer;
    
    if (!analyzer.loadAudioFile(filepath)) {
        std::cerr << "❌ Failed to load audio file" << std::endl;
        return;
    }
    
    const auto& metadata = analyzer.getMetadata();
    const auto& info = analyzer.getAudioInfo();
    const auto& spectral = analyzer.getSpectralData();
    
    // Выводим детальную информацию
    std::cout << "📊 Technical Information:" << std::endl;
    std::cout << "  Format: " << info.format << " (" << info.codec << ")" << std::endl;
    std::cout << "  Sample Rate: " << info.sample_rate << " Hz" << std::endl;
    std::cout << "  Channels: " << info.channels << std::endl;
    std::cout << "  Duration: " << std::fixed << std::setprecision(2) 
              << info.duration_seconds << "s" << std::endl;
    std::cout << "  Total Samples: " << info.total_samples << std::endl;
    
    if (!metadata.title.empty()) {
        std::cout << "\n🏷️  Metadata:" << std::endl;
        std::cout << "  Title: " << metadata.title << std::endl;
        if (!metadata.artist.empty()) std::cout << "  Artist: " << metadata.artist << std::endl;
        if (!metadata.album.empty()) std::cout << "  Album: " << metadata.album << std::endl;
        if (!metadata.genre.empty()) std::cout << "  Genre: " << metadata.genre << std::endl;
        if (metadata.year > 0) std::cout << "  Year: " << metadata.year << std::endl;
    }
    
    std::cout << "\n🌊 Spectral Analysis:" << std::endl;
    std::cout << "  Dominant Frequency: " << std::fixed << std::setprecision(1) 
              << spectral.dominant_frequency << " Hz" << std::endl;
    std::cout << "  Spectral Centroid: " << std::fixed << std::setprecision(1) 
              << spectral.spectral_centroid << " Hz" << std::endl;
    std::cout << "  Spectral Bandwidth: " << std::fixed << std::setprecision(1) 
              << spectral.spectral_bandwidth << " Hz" << std::endl;
    
    // Экспортируем отчет
    std::string report_path = "analysis_report_" + 
                             fs::path(filepath).stem().string() + ".txt";
    if (analyzer.exportAnalysisReport(report_path)) {
        std::cout << "\n📄 Analysis report exported to: " << report_path << std::endl;
    }
}

void batchAnalyzeDirectory(const std::string& directory) {
    std::cout << "📁 Batch Analysis of Directory: " << directory << std::endl;
    std::cout << "=====================================" << std::endl;
    
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        std::cerr << "❌ Directory not found or not a directory: " << directory << std::endl;
        return;
    }
    
    std::vector<std::string> flac_files;
    
    // Собираем все FLAC файлы
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            
            if (ext == ".flac") {
                flac_files.push_back(entry.path().string());
            }
        }
    }
    
    if (flac_files.empty()) {
        std::cout << "ℹ️  No FLAC files found in directory" << std::endl;
        return;
    }
    
    std::cout << "Found " << flac_files.size() << " FLAC files:" << std::endl;
    for (const auto& file : flac_files) {
        std::cout << "  - " << fs::path(file).filename().string() << std::endl;
    }
    
    std::cout << "\nStarting batch analysis..." << std::endl;
    
    int success_count = 0;
    for (const auto& file : flac_files) {
        std::cout << "\n🔍 Analyzing: " << fs::path(file).filename().string() << std::endl;
        
        if (validateFLACFile(file)) {
            success_count++;
        }
        
        std::cout << "---" << std::endl;
    }
    
    std::cout << "\n📊 Batch Analysis Complete!" << std::endl;
    std::cout << "Successfully analyzed: " << success_count << "/" << flac_files.size() << " files" << std::endl;
}

void convertAudioFormat(const std::string& input, const std::string& output) {
    std::cout << "🔄 Converting audio format:" << std::endl;
    std::cout << "  Input: " << input << std::endl;
    std::cout << "  Output: " << output << std::endl;
    
    std::string output_format = fs::path(output).extension().string();
    std::transform(output_format.begin(), output_format.end(), output_format.begin(), ::tolower);
    
    if (AudioUtils::convertFormat(input, output, output_format)) {
        std::cout << "✅ Conversion completed successfully!" << std::endl;
    } else {
        std::cerr << "❌ Conversion failed!" << std::endl;
    }
}

void normalizeAudio(const std::string& input, const std::string& output, double level = -1.0) {
    std::cout << "📏 Normalizing audio:" << std::endl;
    std::cout << "  Input: " << input << std::endl;
    std::cout << "  Output: " << output << std::endl;
    std::cout << "  Target Level: " << level << " dB" << std::endl;
    
    if (AudioUtils::normalizeAudio(input, output, level)) {
        std::cout << "✅ Normalization completed successfully!" << std::endl;
    } else {
        std::cerr << "❌ Normalization failed!" << std::endl;
    }
}

void resampleAudio(const std::string& input, const std::string& output, int sample_rate) {
    std::cout << "🎵 Resampling audio:" << std::endl;
    std::cout << "  Input: " << input << std::endl;
    std::cout << "  Output: " << output << std::endl;
    std::cout << "  Target Sample Rate: " << sample_rate << " Hz" << std::endl;
    
    if (AudioUtils::resampleAudio(input, output, sample_rate)) {
        std::cout << "✅ Resampling completed successfully!" << std::endl;
    } else {
        std::cerr << "❌ Resampling failed!" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }
    
    std::string command = argv[1];
    
    try {
        if (command == "validate" && argc >= 3) {
            validateFLACFile(argv[2]);
        } else if (command == "info" && argc >= 3) {
            showFileInfo(argv[2]);
        } else if (command == "analyze" && argc >= 3) {
            analyzeAudioFile(argv[2]);
        } else if (command == "batch" && argc >= 3) {
            batchAnalyzeDirectory(argv[2]);
        } else if (command == "convert" && argc >= 4) {
            convertAudioFormat(argv[2], argv[3]);
        } else if (command == "normalize" && argc >= 4) {
            double level = -1.0;
            if (argc >= 5) {
                level = std::stod(argv[4]);
            }
            normalizeAudio(argv[2], argv[3], level);
        } else if (command == "resample" && argc >= 5) {
            int sample_rate = std::stoi(argv[4]);
            resampleAudio(argv[2], argv[3], sample_rate);
        } else {
            std::cerr << "❌ Invalid command or missing arguments" << std::endl;
            printUsage();
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
