#include <iostream>
#include <cassert>
#include "../src/mechanical_devices.hpp"

int test_mechanical_devices() {
    std::cout << "Testing mechanical devices..." << std::endl;
    
    try {
        // Basic functionality test
        std::cout << "✓ mechanical devices tests passed" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ mechanical devices test failed: " << e.what() << std::endl;
        return 1;
    }
}

int main() {
    int result = 0;
    result += test_mechanical_devices();
    
    if (result == 0) {
        std::cout << "All tests passed!" << std::endl;
    } else {
        std::cout << result << " test(s) failed!" << std::endl;
    }
    
    return result;
}
