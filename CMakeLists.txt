cmake_minimum_required(VERSION 3.20)

# set the project name
project(mario LANGUAGES CXX C)

set(CMAKE_C_FLAGS "-O3")

# add the executable
add_executable(mario)

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
        sources/src/sound.c
        sources/src/sprite.c
        sources/src/timer.c)

target_include_directories(mario PRIVATE
    sources/include)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES})