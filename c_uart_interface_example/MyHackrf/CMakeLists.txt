cmake_minimum_required(VERSION 3.16)
set(CMAKE_FIND_LIBRARY_PREFIXES "lib")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".so;.a")
set(CMAKE_EXECUTABLE_SUFFIX ".bin")
file(GLOB SOURCES "src/*.cpp")

include_directories(inc)
include_directories(libs/comphackrf/inc)

#set(HACKRF_LIB "${PROJECT_DIR}/libs/comphackrf/build/libhackrf.so" "${PROJECT_DIR}/libs/comphackrf/build/libhackrf.so.0" "${PROJECT_DIR}/libs/comphackrf/build/libhackrf.so.0.9.0")

find_library(HACKRF_LIB NAMES hackrf PATHS "libs/comphackrf/build" NO_DEFAULT_PATH)

project(MyHackrf CXX)

add_executable(${PROJECT_NAME} ${SOURCES})

set(CMAKE_DEBUG_POSTFIX d)
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} PUBLIC ${HACKRF_LIB} pthread)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
