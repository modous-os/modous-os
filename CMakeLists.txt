cmake_minimum_required(VERSION 3.16)
project(ModuOSCore VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(moduos_core src/core.cpp)
target_include_directories(moduos_core PUBLIC include)
target_compile_options(moduos_core PRIVATE -Wall -Wextra -Wpedantic)

add_executable(moduos_simulator app/simulator.cpp)
target_link_libraries(moduos_simulator PRIVATE moduos_core)

include(CTest)
if(BUILD_TESTING)
    add_executable(moduos_core_tests tests/core_tests.cpp)
    target_link_libraries(moduos_core_tests PRIVATE moduos_core)
    target_compile_options(moduos_core_tests PRIVATE -Wall -Wextra -Wpedantic)
    add_test(NAME moduos_core_tests COMMAND moduos_core_tests)
endif()
