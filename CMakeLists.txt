cmake_minimum_required(VERSION 3.16)

project(FloodReliefManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    Crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.2.1
)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(Crow json)

add_executable(flood_relief
    backend/server.cpp
)

target_include_directories(flood_relief PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms
)

target_compile_definitions(flood_relief PRIVATE
    PROJECT_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data"
    PROJECT_FRONTEND_DIR="${CMAKE_CURRENT_SOURCE_DIR}/frontend"
)

target_link_libraries(flood_relief PRIVATE
    Crow::Crow
    nlohmann_json::nlohmann_json
)
