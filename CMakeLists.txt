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
        TMainWindow.cpp

        auth/TAuth.cpp
        auth/TDLogin.cpp

        request/TParams.cpp
        request/TResponse.cpp
        request/TRest.cpp
        request/TUrl.cpp

        utils/TConfig.cpp
        utils/TDB.cpp
        utils/TDump.cpp
        utils/TJson.cpp

        widgets/TComboBox.cpp
        widgets/TComboDialog.cpp
        widgets/TTextDialog.cpp
        )

set(P_H
        TMainWindow.h

        auth/TAuth.h
        auth/TDLogin.h

        request/TParams.h
        request/TResponse.h
        request/TRest.h
        request/TUrl.h

        utils/TConfig.h
        utils/TDB.h
        utils/TDump.h
        utils/TJson.h

        widgets/TComboBox.h
        widgets/TComboDialog.h
        widgets/TTextDialog.h
        )

qt5_wrap_cpp(GENERATED_SOURCES ${P_H})
qt5_add_resources(RES res/res.qrc)

add_executable(Theatre_Debug ${P_S} ${P_H} ${RES})
qt5_use_modules(Theatre_Debug Core Widgets Network Concurrent)
target_compile_features(Theatre_Debug PRIVATE cxx_range_for)
target_link_libraries(Theatre_Debug ${Qt5Core_QTMAIN_LIBRARIES})