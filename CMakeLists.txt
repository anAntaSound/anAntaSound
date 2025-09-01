cmake_minimum_required(VERSION 3.16)
project(anAntaSound VERSION 2.1.0 LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции сборки
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)
option(ENABLE_QUANTUM_FEEDBACK "Enable quantum feedback system" ON)
option(ENABLE_MECHANICAL_DEVICES "Enable mechanical devices" ON)
option(ENABLE_QRD_INTEGRATION "Enable QRD integration" ON)

# Настройка компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    endif()
endif()

# Поиск зависимостей
find_package(Threads REQUIRED)

# Основная библиотека
add_library(anantasound_core
    src/anantasound_core.cpp
    src/quantum_feedback_system.cpp
    src/consciousness_hybrid.cpp
    src/consciousness_integration.cpp
    src/mechanical_devices.cpp
    src/qrd_integration.cpp
)

# Настройка свойств библиотеки
set_target_properties(anantasound_core PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "src/anantasound_core.hpp;src/quantum_feedback_system.hpp;src/mechanical_devices.hpp"
)

# Подключение зависимостей
target_link_libraries(anantasound_core
    PUBLIC Threads::Threads
)

# Включение директорий
target_include_directories(anantasound_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

# Компиляционные определения
target_compile_definitions(anantasound_core
    PRIVATE
        ANANTASOUND_VERSION="${PROJECT_VERSION}"
        $<$<BOOL:${ENABLE_QUANTUM_FEEDBACK}>:ENABLE_QUANTUM_FEEDBACK>
        $<$<BOOL:${ENABLE_MECHANICAL_DEVICES}>:ENABLE_MECHANICAL_DEVICES>
        $<$<BOOL:${ENABLE_QRD_INTEGRATION}>:ENABLE_QRD_INTEGRATION>
)

# Демонстрационные приложения
if(BUILD_EXAMPLES)
    add_executable(anantasound_demo
        examples/anantasound_demo.cpp
    )
    target_link_libraries(anantasound_demo PRIVATE anantasound_core)
    
    add_executable(quantum_acoustic_demo
        examples/quantum_acoustic_demo.cpp
    )
    target_link_libraries(quantum_acoustic_demo PRIVATE anantasound_core)
    
    if(ENABLE_MECHANICAL_DEVICES)
        add_executable(mechanical_devices_demo
            examples/mechanical_devices_demo.cpp
        )
        target_link_libraries(mechanical_devices_demo PRIVATE anantasound_core)
    endif()
endif()

# Тесты
if(BUILD_TESTS)
    enable_testing()
    
    add_executable(anantasound_tests
        tests/test_anantasound_core.cpp
        tests/test_quantum_feedback.cpp
        tests/test_consciousness.cpp
        tests/test_mechanical_devices.cpp
    )
    target_link_libraries(anantasound_tests PRIVATE anantasound_core)
    
    add_test(NAME anantasound_tests COMMAND anantasound_tests)
endif()

# Установка
install(TARGETS anantasound_core
    EXPORT anantasoundTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/anantasound
)

# Установка заголовочных файлов
install(DIRECTORY src/
    DESTINATION include/anantasound
    FILES_MATCHING PATTERN "*.hpp"
)

# Экспорт целей
install(EXPORT anantasoundTargets
    FILE anantasoundTargets.cmake
    NAMESPACE anantasound::
    DESTINATION lib/cmake/anantasound
)

# Конфигурационный файл
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    anantasoundConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/anantasoundConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/anantasoundConfig.cmake"
    INSTALL_DESTINATION lib/cmake/anantasound
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/anantasoundConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/anantasoundConfigVersion.cmake"
    DESTINATION lib/cmake/anantasound
)
