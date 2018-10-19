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
    include/OpenGlPlugin/oglItem.h
    include/OpenGlPlugin/triangleRenderer.h

    src/OpenGlPlugin/oglItem.cpp
    src/OpenGlPlugin/triangleRenderer.cpp
)
ADD_LIBRARY(OpenGlPlugin STATIC ${opengl_plugin_lib_sources})
target_link_libraries(OpenGlPlugin PRIVATE Qt5::Core Qt5::Quick)

# create static Geometry library
set(geometry_lib_sources
    include/GeometryPlugin/polygon.h
    include/GeometryPlugin/utils.h

    src/GeometryPlugin/polygon.cpp
    src/GeometryPlugin/utils.cpp
)
ADD_LIBRARY(GeometryPlugin STATIC ${geometry_lib_sources})
target_link_libraries(GeometryPlugin PRIVATE Qt5::Core)

# main app
add_executable(${PROJECT_NAME} "main.cpp" "qml.qrc")
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick OpenGlPlugin GeometryPlugin)
