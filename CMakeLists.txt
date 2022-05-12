cmake_minimum_required(VERSION 3.20)

project(mario LANGUAGES CXX C)

set(CMAKE_C_FLAGS "-O3")

add_executable(mario)

set_property(TARGET mario PROPERTY C_STANDARD 99)

option(MARIO_ENABLE_SOUND "Enable sound" ON)

target_sources(mario
    PRIVATE
        sources/src/animation.c
        sources/src/collision.c
        sources/src/cursor.c
        sources/src/debug.c
        sources/src/dynamic_objects.c
        sources/src/explosion.c
        sources/src/graphics.c
        sources/src/main.c
        sources/src/map_objects.c
        sources/src/map.c
        sources/src/mario.c
        sources/src/missile.c
        sources/src/object.c
        sources/src/sprite.c
        sources/src/timer.c)
        
if (MARIO_ENABLE_SOUND)
  target_sources(mario PRIVATE sources/src/sound.c)
endif()

target_include_directories(mario PRIVATE
    sources/include)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES})

if (MARIO_ENABLE_SOUND)
  pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer)
  include_directories(${SDL2MIXER_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} ${SDL2MIXER_LIBRARIES})
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(summary)
summary_header()

summary_info("CMAKE_INSTALL_PREFIX" "${CMAKE_INSTALL_PREFIX}" TRUE)

string(APPEND _summary "\n")
summary_info("CMAKE_C_COMPILER" "${CMAKE_C_COMPILER}" TRUE)
summary_info("CMAKE_C_FLAGS" "${CMAKE_C_FLAGS}" TRUE)

string(APPEND _summary "\n")
summary_option("MARIO_ENABLE_SOUND" ${MARIO_ENABLE_SOUND} "")

message(STATUS ${_summary})
