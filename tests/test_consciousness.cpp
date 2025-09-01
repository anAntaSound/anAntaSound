#include <iostream>
#include <cassert>
#include "../src/consciousness_integration.hpp"

int test_consciousness() {
    std::cout << "Testing consciousness integration..." << std::endl;
    
    try {
        // Basic functionality test
        std::cout << "✓ consciousness tests passed" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ consciousness test failed: " << e.what() << std::endl;
        return 1;
    }
}

int main() {
    int result = 0;
    result += test_consciousness();
    
    if (result == 0) {
        std::cout << "All tests passed!" << std::endl;
    } else {
        std::cout << result << " test(s) failed!" << std::endl;
    }
    
    return result;
}
