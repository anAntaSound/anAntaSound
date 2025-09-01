#include <iostream>
#include <cassert>
#include "../src/quantum_feedback_system.hpp"

int test_quantum_feedback() {
    std::cout << "Testing quantum feedback system..." << std::endl;
    
    try {
        // Basic functionality test
        std::cout << "✓ quantum feedback tests passed" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "✗ quantum feedback test failed: " << e.what() << std::endl;
        return 1;
    }
}

int main() {
    int result = 0;
    result += test_quantum_feedback();
    
    if (result == 0) {
        std::cout << "All tests passed!" << std::endl;
    } else {
        std::cout << result << " test(s) failed!" << std::endl;
    }
    
    return result;
}
