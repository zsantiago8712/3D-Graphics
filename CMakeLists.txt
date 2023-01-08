cmake_minimum_required(VERSION 3.11...3.24)

project(3D-Graphics C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(Window STATIC src/Window.c)

add_library(App STATIC src/App.c)

add_library(Renderer STATIC src/Renderer.c)

add_library(Math STATIC src/Vector.c)

add_library(Camera STATIC src/Camera.c)

add_library(Files STATIC src/Files.c)

add_library(Mesh STATIC src/Mesh.c)

add_library(Entity STATIC src/Entity.c)

add_library(Memory STATIC src/Memory.c)

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

target_include_directories(Math
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )


target_include_directories(Camera
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )



target_include_directories(Files
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )

target_include_directories(Memory
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )


target_include_directories(Mesh
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )



    target_include_directories(Entity
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
        Math
        Camera
        Files
        Mesh
        Entity
        Memory
        ${SDL2_LIBRARIES} "-framework Cocoa"
)
