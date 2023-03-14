#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "renderer.h"
#include "../utils.h"

Renderer::Renderer(const char *title, u32 width, u32 height)
    : m_width(width), m_height(height), m_should_quit(false),
      m_old_time(SDL_GetTicks()), m_accumulator(0.0f)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        ERROR_EXIT("[ERROR]: Could not initialize SDL\n");
    }

    m_window = SDL_CreateWindow(title,
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                m_width,
                                m_height,
                                SDL_WINDOW_SHOWN);

    if (m_window == 0) {
        ERROR_EXIT("[ERROR]: Could not create SDL window\n");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    
    if (m_renderer == 0) {
        ERROR_EXIT("[ERROR]: Could not create SDL renderer\n");
    }

    m_gui.initialize_gui(m_renderer, m_window);
    m_camera.set_default_offsets(m_width / 2, m_height / 2);
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    
    SDL_Quit();
}

void Renderer::render()
{
    constexpr f32 circle_radius = 15.0f;
    constexpr f32 curve_radius = 200.0f;
    constexpr u32 max_points = 1024;
    
    while (!m_should_quit) {
        m_current_time = SDL_GetTicks();
        m_accumulator += (m_current_time - m_old_time) / 1000.0f;
        m_old_time = m_current_time;

        handle_events();

        while (m_accumulator >= RENDER_TIME_STEP) {
            update();
            m_accumulator -= RENDER_TIME_STEP;
        }
        
        SDL_SetRenderDrawColor(m_renderer, 18, 18, 18, 255);
        SDL_RenderClear(m_renderer);
        m_gui.begin_frame();

        m_gui.draw_control_panel();

        draw_curve(max_points, curve_radius, m_gui.get_xangle(), m_gui.get_yangle(), m_gui.get_xspeed(), m_gui.get_yspeed());

        if (m_gui.get_animate()) {
            m_indicator.update_indicator(m_gui.get_xangle(), m_gui.get_yangle(), m_gui.get_xspeed() / 100.0f, m_gui.get_yspeed() / 100.0f);

            Camera_Coords indicator_coords = m_camera.screen_to_world(curve_radius * sin(m_indicator.get_xpos()),
                                                                      curve_radius * sin(m_indicator.get_ypos()));
            
            draw_circle(indicator_coords.x, indicator_coords.y, circle_radius);
        }

        m_gui.end_frame();
        SDL_RenderPresent(m_renderer);

        // Be nice to the CPU
        SDL_Delay(static_cast<u32>(RENDER_TIME_STEP * 1000.0f));
    }
}

void Renderer::update()
{
    if (ImGui::GetIO().WantCaptureMouse) return;

    if (m_gui.get_animate()) {
        m_indicator.update_pos();
    }
}

void Renderer::handle_events()
{
    SDL_Event e = {0};

    while (SDL_PollEvent(&e)) {
        m_gui.process_events(&e);
        
        switch (e.type) {
            case SDL_QUIT: {
                m_should_quit = true;
            } break;
                
            default: {
                m_event_handler.handle_camera_events(e, m_camera);
            } break;
        }
    }
}

// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void Renderer::draw_circle(f32 cx, f32 cy, f32 r)
{
    f32 x = r;
    f32 y = 0;
    f32 p = 1.25f - r;

    SDL_SetRenderDrawColor(m_renderer, 255, 36, 0, 255);
    SDL_RenderDrawLineF(m_renderer, cx - r, cy, cx + r, cy);

    while (x > y) {
        y += 1;

        if (p <= 0) {
            p += 2 * y + 1;
        } else {
            x -= 1;
            p += 2 * y - 2 * x + 1;
        }
        
        SDL_RenderDrawLineF(m_renderer, cx + x, cy - y, cx - x, cy - y);
        SDL_RenderDrawLineF(m_renderer, cx + x, cy + y, cx - x, cy + y);
        SDL_RenderDrawLineF(m_renderer, cx + y, cy - x, cx - y, cy - x);
        SDL_RenderDrawLineF(m_renderer, cx + y, cy + x, cx - y, cy + x);
    }
}

void Renderer::draw_curve(u32 max_points, f32 r, f32 xangle, f32 yangle, s32 xspeed, s32 yspeed)
{
    f32 x1 = r * sin(xangle);
    f32 y1 = r * sin(yangle);
    
    for (u32 i = 1; i < max_points; ++i) {
        f32 x2 = r * sin(xangle);
        f32 y2 = r * sin(yangle);
        
        Camera_Coords first_point = m_camera.screen_to_world(x1, y1);
        Camera_Coords second_point = m_camera.screen_to_world(x2, y2);

        xangle += xspeed / 100.0f;
        yangle += yspeed / 100.0f;

        SDL_SetRenderDrawColor(m_renderer, 0, 200, 0, 255);
        SDL_RenderDrawLineF(m_renderer, first_point.x, first_point.y, second_point.x, second_point.y);
        
        x1 = x2;
        y1 = y2;
    }
}
