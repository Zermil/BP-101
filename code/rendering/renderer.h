#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

#include "../types.h"

#include "../ui/gui.h"
#include "../ui/indicator.h"
#include "camera.h"
#include "../events/event_handler.h"

#define RENDER_TIME_STEP (1.0f / 60.0f)

class Renderer {
public:
    Renderer(const Renderer& r) = delete;
    Renderer(const char *title, u32 width, u32 height);
    ~Renderer();

    void update();
    void render();
    void handle_events();

    void draw_circle(f32 cx, f32 cy, f32 r);
    void draw_curve(u32 max_points, f32 r, f32 xangle, f32 yangle, s32 xspeed, s32 yspeed);

    void setup_dependencies(GUI_Layer *gui, Camera *camera, Event_Handler *event_handler);
    
private:
    bool m_should_quit;
    u32 m_width;
    u32 m_height;

    u32 m_current_time;
    u32 m_old_time;
    f32 m_accumulator;

    SDL_Renderer *m_renderer;
    SDL_Window *m_window;

    Indicator m_indicator;
    
    // https://en.wikipedia.org/wiki/Dependency_injection
    GUI_Layer *m_gui;
    Camera *m_camera;
    Event_Handler *m_event_handler;
};

#endif // RENDERER_H
