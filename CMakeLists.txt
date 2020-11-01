cmake_minimum_required(VERSION 3.14)

project(libprotocolrf LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_library(libprotocolrf STATIC
  libprotocolrf.cpp
  libprotocolrf.h
  fio.h
  packed.h
  packed.cpp
  messeng.h
  messeng.cpp
  config.h
  microjson.h
  microjson.cpp
)

target_link_libraries(libprotocolrf PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(libprotocolrf PRIVATE LIBPROTOCOLRF_LIBRARY)
