#!/bin/bash

echo "🎵 anAntaSound Audio Analysis System Test"
echo "=========================================="

# Проверяем наличие build директории
if [ ! -d "build" ]; then
    echo "❌ Build directory not found. Please build the project first:"
    echo "   mkdir build && cd build && cmake .. && make"
    exit 1
fi

cd build

echo ""
echo "🔨 Building audio analysis components..."
make advanced_audio_demo flac_utility -j$(nproc)

if [ $? -ne 0 ]; then
    echo "❌ Build failed!"
    exit 1
fi

echo "✅ Build successful!"

echo ""
echo "🧪 Testing FLAC utility..."

# Проверяем наличие samples директории
if [ ! -d "../samples" ]; then
    echo "⚠️  Samples directory not found, creating test samples..."
    mkdir -p ../samples
    echo "Created samples directory"
fi

# Тестируем FLAC utility
echo ""
echo "📋 Testing file info command..."
./flac_utility info ../samples/Hanuman.mp3

echo ""
echo "🔍 Testing validation command..."
./flac_utility validate ../samples/Hanuman.mp3

echo ""
echo "🔬 Testing analysis command..."
./flac_utility analyze ../samples/Hanuman.mp3

echo ""
echo "📁 Testing batch analysis..."
./flac_utility batch ../samples

echo ""
echo "🎮 Testing advanced audio demo..."
echo "Choose option 1 for automatic analysis..."
echo "1" | ./advanced_audio_demo

echo ""
echo "🎉 Audio analysis system test completed!"
echo ""
echo "📊 Generated reports:"
ls -la *.txt 2>/dev/null || echo "No reports generated"

echo ""
echo "🚀 You can now use the following commands:"
echo "  ./flac_utility validate <file>     - Validate FLAC quality"
echo "  ./flac_utility info <file>         - Show file information"
echo "  ./flac_utility analyze <file>      - Full audio analysis"
echo "  ./flac_utility batch <directory>   - Batch analysis"
echo "  ./advanced_audio_demo              - Interactive demo"
echo ""
echo "📚 For more information, see docs/AUDIO_ANALYSIS.md"
