cmake_minimum_required( VERSION 3.28 )

#set(CMAKE_CXX_STANDARD 20)

project( "imcord" 
    LANGUAGES
        C
        CXX
)

add_executable( ${PROJECT_NAME} )

add_subdirectory( "src" )
add_subdirectory( thirdparty/spdlog )

include( cmake/imgui.cmake )

find_package( OpenGL REQUIRED )

target_link_libraries( imcord PUBLIC
    SDL3-static
    OpenGL::GL
    imgui
    spdlog::spdlog
)