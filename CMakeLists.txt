


cmake_minimum_required(VERSION 3.20)
project(BaseUtils VERSION 1.0.0 LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library target
add_library(baseutils INTERFACE include/ColouredFormatting.h
        include/PrefixFormatting.h
        include/SuffixFormatting.h
        include/FullFormatting.h)
target_include_directories(baseutils INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Make sure formatting.h is in include directory
target_sources(baseutils INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ColouredFormatting.h>
)

# Option to build tests
option(BASEUTILS_BUILD_TESTS "Build BaseUtils tests" ON)

if(BASEUTILS_BUILD_TESTS)
    enable_testing()

    # Test executable
    add_executable(formatting_tests
            tests/formatting_test.cpp
    )

    target_link_libraries(formatting_tests PRIVATE baseutils)

    target_include_directories(formatting_tests PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/tests
    )

    # Add test to CTest
    add_test(NAME FormattingTests COMMAND formatting_tests)

    # Optional: Add compile definitions for testing different modes
    # Uncomment to test with NO_COLOUR
    # target_compile_definitions(formatting_tests PRIVATE NO_COLOUR)

    # Uncomment to test with NO_FORMAT
    # target_compile_definitions(formatting_tests PRIVATE NO_FORMAT)

    # Uncomment to test with NO_DEBUG
    # target_compile_definitions(formatting_tests PRIVATE NO_DEBUG)
endif()

# Installation rules
include(GNUInstallDirs)

install(TARGETS baseutils
        EXPORT BaseutilsTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES include/ColouredFormatting.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/baseutils
)

install(EXPORT BaseutilsTargets
        FILE BaseutilsTargets.cmake
        NAMESPACE BaseUtils::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BaseUtils
)

# Create config file
include(CMakePackageConfigHelpers)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/BaseutilsConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/BaseutilsConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BaseUtils
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/BaseutilsConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/BaseutilsConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/BaseutilsConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BaseUtils
)