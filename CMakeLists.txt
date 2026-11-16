cmake_minimum_required(VERSION 3.16)

project(FloodReliefManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Crow needs the standalone Asio library. It is header-only, so we only
# download it (SOURCE_SUBDIR points at a folder that does not exist, which
# stops CMake from trying to build it) and tell Crow where the headers are.
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-30-2
    GIT_SHALLOW TRUE
    SOURCE_SUBDIR no_cmake_build
)

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

FetchContent_MakeAvailable(asio)
set(ASIO_INCLUDE_DIR "${asio_SOURCE_DIR}/asio/include" CACHE PATH "Asio headers" FORCE)

# We only need the Crow library, not its examples and unit tests.
set(CROW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CROW_BUILD_TESTS OFF CACHE BOOL "" FORCE)

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

# Windows needs the socket libraries that Asio uses.
if(WIN32)
    target_compile_definitions(flood_relief PRIVATE _WIN32_WINNT=0x0A00)
    target_link_libraries(flood_relief PRIVATE ws2_32 mswsock)
endif()
