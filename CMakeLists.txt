cmake_minimum_required(VERSION 3.24)
project(3D-Graphics C)

set(CMAKE_C_STANDARD 17)


add_library(Window STATIC
    src/Window.c
)

add_library(App STATIC
    src/App.c
)

add_library(Renderer STATIC
    src/Renderer.c
)


target_include_directories(App
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )

target_include_directories(Window
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )

target_include_directories(Renderer
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(3D-Graphics src/main.c)


target_link_libraries(
        3D-Graphics PRIVATE App
        Window
        Renderer
        ${SDL2_LIBRARIES} "-framework Cocoa"
)
#target_link_libraries(3D-Graphics PRIVATE Window)
#target_link_libraries(3D-Graphics PRIVATE Renderer)