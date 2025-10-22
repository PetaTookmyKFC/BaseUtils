cmake_minimum_required(VERSION 3.20)
project(BaseUtils VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)
install(DIRECTORY . DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/base_utils FILES_MATCHING PATTERN "*.h")

add_executable(base_utils_test test_main.cpp
        formatting_Refactor.h
        test_main.cpp
        test_main.cpp
        StyleCodes.h
)  # Create a test_main.cpp below
target_include_directories(base_utils_test PRIVATE .)