cmake_minimum_required(VERSION 3.28)
project(BABOENGINE)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        glm
        GIT_REPOSITORY "https://github.com/g-truc/glm.git"
        GIT_TAG "1.0.1"
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY "https://github.com/glfw/glfw.git"
        GIT_TAG "3.4"
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        Microsoft-gsl
        GIT_REPOSITORY "https://github.com/microsoft/GSL.git"
        GIT_TAG "v4.0.0"
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Microsoft-gsl)



find_package(Vulkan REQUIRED)

add_executable(BABOENGINE source/main.cpp
        source/glfw_initilazition.h
        source/glfw_initilazition.cpp
        source/precomp.h
        source/glfw_monitor.cpp
        source/glfw_monitor.h
        source/glfw_window.cpp
        source/glfw_window.h
        source/graphics.cpp
        source/graphics.h
)
target_link_libraries(BABOENGINE PRIVATE Vulkan::Vulkan)
target_link_libraries(BABOENGINE PRIVATE glm)
target_link_libraries(BABOENGINE PRIVATE glfw)
target_link_libraries(BABOENGINE PRIVATE Microsoft.GSL::GSL)

target_precompile_headers(BABOENGINE PRIVATE source/precomp.h)

