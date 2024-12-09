cmake_minimum_required(VERSION 3.29)
project(cpp_revision)

set(CMAKE_CXX_STANDARD 14)

include_directories(TP2/Include)

add_executable(cpp_revision
    TP2/Include/Personne.h
    TP2/Source/Personne.cpp
        TP2/Source/Utilisation.cpp
        TP2/Source/Date.cpp
        TP2/Source/ContratException.cpp)

# Fetch Google Tests
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

# Add Test Executable
add_executable(MyTests TP2/Tests/PersonneTesteur.cpp ${SOURCE_FILES})

# Link Google Test Libraries
target_link_libraries(MyTests gtest gtest_main)