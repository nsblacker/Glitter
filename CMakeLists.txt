cmake_minimum_required(VERSION 3.0)
project(Glitter)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Glitter/Vendor/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(Glitter/Vendor/assimp)

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(Glitter/Vendor/bullet)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(Glitter/Headers/
                    Glitter/Sources/
                    Glitter/Vendor/assimp/include/
                    Glitter/Vendor/bullet/src/
                    Glitter/Vendor/glad/include/
                    Glitter/Vendor/glfw/include/
                    Glitter/Vendor/glm/
                    Glitter/Vendor/stb/)

file(GLOB VENDORS_SOURCES Glitter/Vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS Glitter/Headers/*.hpp)
file(GLOB PROJECT_SOURCES
        Glitter/Sources/*.cpp
        Glitter/Sources/HelloWindow/HelloWindow.cpp
        Glitter/Sources/HelloWindow/HelloWindow.h
        Glitter/Sources/HelloTriangle/HelloTriangle.cpp
        Glitter/Sources/HelloTriangle/HelloTriangle.h
        Glitter/Sources/HelloTriangle/HelloTriangleExtend.cpp
        Glitter/Sources/HelloTriangle/HelloTriangleExtend.h
        Glitter/Sources/HelloShader/HelloShader.cpp
        Glitter/Sources/HelloShader/HelloShader.h
        Glitter/Sources/HelloShader/ShaderMgr.cpp
        Glitter/Sources/HelloShader/ShaderMgr.h
        Glitter/Sources/HelloTexture/HelloTexture.cpp
        Glitter/Sources/HelloTexture/HelloTexture.h
        Glitter/Sources/HelloTexture/HelloTextureExtend.cpp
        Glitter/Sources/HelloTexture/HelloTextureExtend.h
        )
file(GLOB PROJECT_MEDIA Glitter/Meida/Shaders/*.comp
                        Glitter/Media/Shaders/*.frag
                        Glitter/Media/Shaders/*.geom
                        Glitter/Media/Shaders/*.vert
                        Glitter/Media/Images/*.jpeg
                        Glitter/Media/Images/*.jpg
                        Glitter/Media/Images/*.png
)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)



source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Media" FILES ${PROJECT_MEDIA})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_MEDIA} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES} Glitter/Sources/HelloTransform/HelloTransform.cpp Glitter/Sources/HelloTransform/HelloTransform.h Glitter/Sources/HelloCoordSystem/HelloCoordSystem.cpp Glitter/Sources/HelloCoordSystem/HelloCoordSystem.h)
target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
