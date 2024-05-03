set(SDL_SHARED OFF)
set(SDL_STATIC ON)

add_subdirectory( thirdparty/sdl EXCLUDE_FROM_ALL )

set( IMGUI_DIR ${CMAKE_SOURCE_DIR}/thirdparty/imgui )

set(IMGUI_SOURCES 
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library( imgui STATIC ${IMGUI_SOURCES} )

include_directories(
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries( imgui PUBLIC
    SDL3::SDL3
)