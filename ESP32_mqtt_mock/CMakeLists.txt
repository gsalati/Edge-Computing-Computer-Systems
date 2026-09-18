cmake_minimum_required(VERSION 3.15)
project(hello_cpp20 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ESP32Mock
src/main.cpp 
src/serial/serial.cpp
src/esp32.cpp
src/esp32.h
src/utils/utils.h
src/utils/utils.cpp
src/serial/serialMock.cpp
src/serial/serialMock.h
src/mqtt/mqtt.cpp
src/mqtt/mqtt.h
)

target_link_libraries(ESP32Mock
    PRIVATE
    paho-mqttpp3
    paho-mqtt3as
)