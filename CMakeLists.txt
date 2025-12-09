cmake_minimum_required(VERSION 3.20)  # Minimum for FetchContent_MakeAvailable

project(BaseUtils
        VERSION 0.1.0  # Set your version here; bump as needed
        DESCRIPTION "A simple base utilities library"
        LANGUAGES CXX
)

# Global compile features (adjust as needed for your C++ standard)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the main INTERFACE library target
add_library(baseutils INTERFACE
        include/BaseUtils/All.h
#        tests/types_test.cpp
        include/BaseUtils/types/SemiDynamicArray.h
        include/BaseUtils/types/BaseVectors.h
)


# Set up include directories: Different for build (FetchContent) vs. install
target_include_directories(baseutils INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/baseutils> # For installed mode
)

# Create a namespaced alias for consistent usage (e.g., BaseUtils::baseutils)
add_library(BaseUtils::baseutils ALIAS baseutils)

# Optional: Installation rules (harmless for FetchContent; enables `find_package` too)
include(GNUInstallDirs)
install(TARGETS baseutils
        EXPORT BaseUtilsTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT BaseUtilsTargets
        FILE BaseUtilsTargets.cmake
        NAMESPACE BaseUtils::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BaseUtils
)

# Generate and install config files for find_package support
include(CMakePackageConfigHelpers)
configure_package_config_file(
        cmake/BaseUtilsConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/BaseUtilsConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BaseUtils
)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/BaseUtilsConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/BaseUtilsConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/BaseUtilsConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BaseUtils
)

# Uncomment add_executable and then debug formatting_tests.cpp
#
#add_executable(test_app tests/types_test.cpp)  # Or a new main.cpp
#target_link_libraries(test_app PRIVATE BaseUtils::baseutils)