cmake_minimum_required(VERSION 3.15)
project(SFMLApp VERSION 1.0.0)

# Set macOS-specific options
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO")
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO")

# Add source files
set(SOURCE_FILES
    main.cpp
    Particle.hpp
    Particle.cpp
    Solver.hpp
    Solver.cpp
    Utils.hpp
    Utils.cpp
    Link.hpp
    Link.cpp
)

# Create the .app bundle
add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCE_FILES})

# Set the RPATH so it looks for libraries inside the app bundle
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist
    INSTALL_RPATH "@executable_path/../Frameworks"
)

# Find SFML
find_package(SFML 3.0 COMPONENTS System Window Graphics Audio REQUIRED)
target_link_libraries(${PROJECT_NAME} SFML::System SFML::Window SFML::Graphics SFML::Audio)

# Copy SFML libraries to the .app bundle after building
if(APPLE)
    set(SFML_ROOT "/opt/homebrew/Cellar/sfml/3.0.0")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        # Create Frameworks directory inside the .app bundle
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Frameworks"

        # Copy SFML libraries
        COMMAND ${CMAKE_COMMAND} -E copy "${SFML_ROOT}/lib/libsfml-system.3.0.dylib" "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Frameworks/"
        COMMAND ${CMAKE_COMMAND} -E copy "${SFML_ROOT}/lib/libsfml-window.3.0.dylib" "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Frameworks/"
        COMMAND ${CMAKE_COMMAND} -E copy "${SFML_ROOT}/lib/libsfml-graphics.3.0.dylib" "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Frameworks/"
        COMMAND ${CMAKE_COMMAND} -E copy "${SFML_ROOT}/lib/libsfml-audio.3.0.dylib" "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Frameworks/"

        # Optionally copy resources (e.g., fonts, images)
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Resources" "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Resources"
    )
endif()