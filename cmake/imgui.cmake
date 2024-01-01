add_subdirectory( thirdparty/sdl )

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
    ${SDL3_INCLUDE_FILES}
)

target_link_libraries( imgui PUBLIC
    SDL3-static
)