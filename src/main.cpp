#include "application.h"
#include <stdio.h>

// Credits:
// https://gist.github.com/dele256/901dd1e8f920327fc457a538996f2a29
#define MOUSE_GRAB_PADDING 5
SDL_HitTestResult HitTestCallback(SDL_Window *Window, const SDL_Point *Area,
                                  void *Data) {
    int Width, Height;
    SDL_GetWindowSize(Window, &Width, &Height);

    int x, y;
    x = Area->x;
    y = Area->y;

    if (Area->y < MOUSE_GRAB_PADDING) {
        if (Area->x < MOUSE_GRAB_PADDING) {
            return SDL_HITTEST_RESIZE_TOPLEFT;
        } else if (Area->x > Width - MOUSE_GRAB_PADDING) {
            return SDL_HITTEST_RESIZE_TOPRIGHT;
        } else {
            return SDL_HITTEST_RESIZE_TOP;
        }
    } else if (Area->y > Height - MOUSE_GRAB_PADDING) {
        if (Area->x < MOUSE_GRAB_PADDING) {
            return SDL_HITTEST_RESIZE_BOTTOMLEFT;
        } else if (Area->x > Width - MOUSE_GRAB_PADDING) {
            return SDL_HITTEST_RESIZE_BOTTOMRIGHT;
        } else {
            return SDL_HITTEST_RESIZE_BOTTOM;
        }
    } else if (Area->x < MOUSE_GRAB_PADDING) {
        return SDL_HITTEST_RESIZE_LEFT;
    } else if (Area->x > Width - MOUSE_GRAB_PADDING) {
        return SDL_HITTEST_RESIZE_RIGHT;
    } else if (Area->y < 22) {
        return SDL_HITTEST_DRAGGABLE;
    }

    return SDL_HITTEST_NORMAL; // SDL_HITTEST_NORMAL <- Windows behaviour
}

static int SDLCALL ExposeEventWatcher(void*, SDL_Event *event) {
    if (event->type == SDL_EVENT_WINDOW_EXPOSED)
        // Do app updates even when resizing
        Tick();
    return 0;
}

// Main code
int main(int, char **) {
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD) != 0) {
        printf("Error: SDL_Init(): %s\n", SDL_GetError());
        return -1;
    }

    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Enable native IME.
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

    // Needed for borderless resizing to work
    // https://github.com/libsdl-org/SDL/issues/8586
    SDL_SetHint("SDL_BORDERLESS_RESIZABLE_STYLE", "1");

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    g_State.window = SDL_CreateWindow("Dear ImGui SDL3+OpenGL3 example", 1280, 720,
                              SDL_WINDOW_OPENGL | /*SDL_WINDOW_RESIZABLE |*/
                                  SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS);
    if (g_State.window == nullptr) {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }

    SDL_SetWindowResizable(g_State.window, SDL_TRUE);
    SDL_SetWindowHitTest(g_State.window, HitTestCallback, 0);

    SDL_SetWindowPosition(g_State.window, SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED);
    SDL_GLContext gl_context = SDL_GL_CreateContext(g_State.window);
    SDL_GL_MakeCurrent(g_State.window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync
    SDL_ShowWindow(g_State.window);
    SDL_AddEventWatch(ExposeEventWatcher, NULL);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForOpenGL(g_State.window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Main loop
    bool done = false;

    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                done = true;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
                event.window.windowID == SDL_GetWindowID(g_State.window))
                done = true;
        }

        Tick();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(g_State.window);
    SDL_Quit();

    return 0;
}
