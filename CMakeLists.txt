cmake_minimum_required(VERSION 3.1)

project(OpenglTest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
find_package(Qt5 COMPONENTS Core Quick REQUIRED)

# create static OpenGLPlugin library
# we try to avoid recompilation for tests and for application
# and organize things nicely
set(opengl_plugin_lib_sources
    include/oglTriangle.h
)
ADD_LIBRARY(OpenGlPlugin STATIC ${opengl_plugin_lib_sources})
target_link_libraries(OpenGlPlugin PRIVATE Qt5::Core Qt5::Quick)

# main app
add_executable(${PROJECT_NAME} "main.cpp" "qml.qrc")
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)
