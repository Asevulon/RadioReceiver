cmake_minimum_required(VERSION 3.5)

project(c_uart_interface_example CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_FIND_LIBRARY_PREFIXES "lib")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".so;.a")
set(CMAKE_EXECUTABLE_SUFFIX ".bin")
set(CMAKE_DEBUG_POSTFIX d)

set(OpenCV_DIR "/home/user/workspace/opencv_src/build4-full_armhf")

set(SOURCES
    autopilot_interface.cpp
    mavlink_control.cpp
    serial_port.cpp
    udp_port.cpp
    MyHackrf/src/Detecter.cpp
    MyHackrf/src/general.cpp
    MyHackrf/src/Journal.cpp
    MyHackrf/src/Receiver.cpp
)

include_directories(MyHackrf/inc)
include_directories(CameraLib)
include_directories(MyHackrf/libs/comphackrf/inc)

find_library(HACKRF_LIB NAMES hackrf PATHS "MyHackrf/libs/comphackrf/build" NO_DEFAULT_PATH)

add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC ${HACKRF_LIB} pthread)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
link_libraries( ${OpenCV_LIBS})



target_include_directories(${PROJECT_NAME} PRIVATE mavlink/include/mavlink/v2.0)

target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
