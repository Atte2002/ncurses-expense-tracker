cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(raha LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Curses REQUIRED)

include(FetchContent)
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)


add_executable(main 
    src/main.cpp
    src/window.cpp
    src/app.cpp)

target_link_libraries(main PRIVATE ncursesw nlohmann_json::nlohmann_json)
target_include_directories(main PRIVATE ${CURSES_INCLUDE_DIRS})
