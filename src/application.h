#ifndef APPLICATION_H
#define APPLICATION_H

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

enum Screens {
    Loading,
    Login,
    Main,
};

struct UserData {
    // servers
    // dms
};

struct ApplicationState {
    SDL_Window* window;
    Screens current_screen;
};

extern struct ApplicationState g_State;

void Tick();

#endif