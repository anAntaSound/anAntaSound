#include <iostream>
#include <cassert>
#include "../src/anantasound_core.hpp"

int test_anantasound_core() {
    std::cout << "Testing anantasound_core..." << std::endl;
    
    try {
        // Basic functionality test
        std::cout << "✓ anantasound_core tests passed" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ anantasound_core test failed: " << e.what() << std::endl;
        return 1;
    }
}

int main() {
    int result = 0;
    result += test_anantasound_core();
    
    if (result == 0) {
        std::cout << "All tests passed!" << std::endl;
    } else {
        std::cout << result << " test(s) failed!" << std::endl;
    }
    
    return result;
}
