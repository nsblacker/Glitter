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
        Glitter/Sources/GettingStart/HelloWindow/HelloWindow.cpp
        Glitter/Sources/GettingStart/HelloWindow/HelloWindow.h
        Glitter/Sources/GettingStart/HelloTriangle/HelloTriangle.cpp
        Glitter/Sources/GettingStart/HelloTriangle/HelloTriangle.h
        Glitter/Sources/GettingStart/HelloTriangle/HelloTriangleExtend.cpp
        Glitter/Sources/GettingStart/HelloTriangle/HelloTriangleExtend.h
        Glitter/Sources/GettingStart/HelloShader/HelloShader.cpp
        Glitter/Sources/GettingStart/HelloShader/HelloShader.h
        Glitter/Sources/GettingStart/HelloTexture/HelloTexture.cpp
        Glitter/Sources/GettingStart/HelloTexture/HelloTexture.h
        Glitter/Sources/GettingStart/HelloTexture/HelloTextureExtend.cpp
        Glitter/Sources/GettingStart/HelloTexture/HelloTextureExtend.h
        Glitter/Sources/GettingStart/HelloTransform/HelloTransform.cpp
        Glitter/Sources/GettingStart/HelloTransform/HelloTransform.h
        Glitter/Sources/GettingStart/HelloCoordSystem/HelloCoordSystem.cpp
        Glitter/Sources/GettingStart/HelloCoordSystem/HelloCoordSystem.h
        Glitter/Sources/GettingStart/HelloCamera/HelloCamera.cpp
        Glitter/Sources/GettingStart/HelloCamera/HelloCamera.h
        Glitter/Sources/Lighting/HelloColor/HelloColors.cpp
        Glitter/Sources/Lighting/HelloColor/HelloColors.h
        Glitter/Sources/AdvancedOpenGL/HelloFrameBufferObject.cpp
        Glitter/Sources/AdvancedOpenGL/HelloFrameBufferObject.h
)

file(GLOB PROJECT_SERVICE Glitter/Service/*.cpp
        Glitter/Service/*.h
        Glitter/Service/*.hpp
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
source_group("Service" FILES ${PROJECT_SERVICE})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_MEDIA} ${PROJECT_CONFIGS}
                                ${PROJECT_SERVICE}
                               ${VENDORS_SOURCES})
target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
