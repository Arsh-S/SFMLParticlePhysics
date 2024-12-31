cmake_minimum_required(VERSION 3.15)
project(SFMLTestCPP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        Particle.h
        Particle.cpp
        Solver.h
        Solver.cpp
        Utils.h
        Utils.cpp
)

add_executable(SFMLTestCPP ${SOURCE_FILES})

find_package(SFML 3.0 COMPONENTS System Window Graphics Network Audio REQUIRED)

include_directories(${SFML_INCLUDE_DIRS})

target_link_libraries(SFMLTestCPP SFML::System SFML::Window SFML::Graphics SFML::Audio SFML::Network)
