cmake_minimum_required(VERSION 3.15)
project(fiap_backend_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(Backend_Cpp
    src/main.cpp
    src/registroDragoes.cpp
    src/registroDragoes.h
    src/apiDragoes.cpp
    src/apiDragoes.h
)

target_include_directories(Backend_Cpp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cpp-httplib
)

target_link_libraries(Backend_Cpp PRIVATE
    nlohmann_json::nlohmann_json
)