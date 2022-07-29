cmake_minimum_required(VERSION 3.21)
project(sim)

set(CMAKE_CXX_STANDARD 14)
if(APPLE)
    set(suffix "macosx")
elseif(WIN32)
    set(suffix "x64")
elseif(CMAKE_SYSTEM MATCHES "Linux")
    set(suffix "linux")
endif()

message("list" ${CMAKE_CURRENT_LIST_DIR})
message("suffix" ${suffix} ${CMAKE_GENERATOR_PLATFORM} " " "${CMAKE_CURRENT_LIST_DIR}/../include")
find_library(SDL2_LIBRARY REQUIRED
        NAMES SDL2
        PATHS "${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/${suffix}" "${CMAKE_CURRENT_LIST_DIR}/${suffix}"
        NO_DEFAULT_PATH
        NO_CMAKE_FIND_ROOT_PATH
        )
message("suffix" ${SDL2_LIBRARY})
include_directories("SDL2/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/../include")
include_directories(${CMAKE_CURRENT_LIST_DIR})
add_definitions(-DSIMULATOR)
add_executable(sim Arduino.cpp device.c track.c Adafruit_GFX.cpp Adafruit_SSD1306.cpp main.cpp )
target_link_libraries(sim ${SDL2_LIBRARY})

if(WIN32)
    target_link_libraries(sim wsock32 ws2_32)
endif()

add_custom_command(TARGET sim POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/${suffix}/SDL2.dll"      # <--this is in-file
        $<TARGET_FILE_DIR:sim>/SDL2.dll)                 # <--this is out-file path