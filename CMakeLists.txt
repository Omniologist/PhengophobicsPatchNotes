cmake_minimum_required(VERSION 4.1)
project(PhengophobicsPatchNotes)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(PhengophobicsPatchNotes
        main.cpp
        weather_api.cpp)

target_link_libraries(PhengophobicsPatchNotes PRIVATE
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
        cpr::cpr
        nlohmann_json::nlohmann_json)

add_custom_command(TARGET PhengophobicsPatchNotes POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:PhengophobicsPatchNotes>/assets)