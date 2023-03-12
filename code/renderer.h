#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

#include "types.h"
#include "gui.h"
#include "indicator.h"

#define RENDER_TIME_STEP (1.0f / 60.0f)

class Renderer {
public:
    Renderer(const Renderer& r) = delete;
    Renderer(const char *title, u32 width, u32 height);
    ~Renderer();

    void update();
    void render();
    void handle_events();

    void draw_circle(u32 cx, u32 cy, u32 r);
    void draw_curve(u32 max_points, f32 r, f32 xangle, f32 yangle, s32 xspeed, s32 yspeed);
    
private:
    bool m_should_quit;
    u32 m_width;
    u32 m_height;

    u32 m_current_time;
    u32 m_old_time;
    f32 m_accumulator;

    SDL_Renderer *m_renderer;
    SDL_Window *m_window;

    // Good place for dependency injection in case any of these grows larger
    // https://en.wikipedia.org/wiki/Dependency_injection
    GUI_Layer m_gui;
    Indicator m_indicator;
};

#endif // RENDERER_H
