cmake_minimum_required(VERSION 3.10) 

project(graphics_implementation)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(X11 REQUIRED)
find_package(assimp REQUIRED)

# Main executable
add_executable(
    app
    src/main.c
    src/graphics.c
)

# Library files
add_library(
    render_lib 
    lib/render/render.c
    lib/render/camera.c
)

add_library(
    graphics_math_lib lib/graphics_math/graphics_math.c
)
target_link_libraries(graphics_math_lib PRIVATE m)

add_library(
    display_lib lib/display/display.c
)
target_link_libraries(display_lib PRIVATE ${X11_LIBRARIES} Xrandr)
target_include_directories(display_lib PUBLIC ${X11_INCLUDE_DIR})

add_library(
    mesh_lib lib/mesh/mesh.c
)
target_link_libraries(mesh_lib PRIVATE assimp)

target_include_directories(render_lib PUBLIC
    lib/graphics_math
)

target_include_directories(app PUBLIC
    lib/graphics_math
    lib/render
    lib/display
    lib/mesh
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Og -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -DNDEBUG")
endif()

target_link_libraries(app PRIVATE display_lib graphics_math_lib render_lib mesh_lib)
