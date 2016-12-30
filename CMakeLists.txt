cmake_minimum_required(VERSION 3.3)
project(Theatre_Debug)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-std=c++14")

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5Concurrent)

set(P_S
        main.cpp

        TDebug.cpp
        TConfig.cpp
        TDB.cpp

        TDLogin.cpp

        TDump.cpp
        )

set(P_H
        TDebug.h
        TConfig.h
        TDB.h

        TDLogin.h

        TDump.cpp
        )

qt5_wrap_cpp(GENERATED_SOURCES ${P_H})

add_executable(Theatre_Debug ${P_S} ${P_H})
qt5_use_modules(Theatre_Debug Core Widgets Network Concurrent)
target_compile_features(Theatre_Debug PRIVATE cxx_range_for)
target_link_libraries(Theatre_Debug ${Qt5Core_QTMAIN_LIBRARIES})