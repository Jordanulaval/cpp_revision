cmake_minimum_required(VERSION 3.29)
project(cpp_revision)

set(CMAKE_CXX_STANDARD 14)

include_directories(TP2/Include)

add_executable(cpp_revision
    TP2/Include/Personne.h
    TP2/Source/Personne.cpp
        TP2/Source/Utilisation.cpp
        TP2/Source/Date.cpp
        TP2/Source/ContratException.cpp
        TP2/Include/Candidat.h
        TP2/Source/Candidat.cpp)
