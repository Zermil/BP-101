#include <imgui/imgui.h>
#include <cstdio>

#include "utils.h"
#include "event_handler.h"

Event_Handler::Event_Handler()
    : m_mouse_held(false)
{
    // ...
}

void Event_Handler::handle_camera_events(SDL_Event event, Camera& camera)
{
    if (ImGui::GetIO().WantCaptureMouse) return;
    
    switch (event.type) {
        case SDL_MOUSEMOTION: {
            if (m_mouse_held) {
                s32 ox = static_cast<s32>((event.motion.x - m_xmouse) / camera.get_scale());
                s32 oy = static_cast<s32>((event.motion.y - m_ymouse) / camera.get_scale());
                
                camera.set_xoffset(camera.get_xoffset() + ox);
                camera.set_yoffset(camera.get_yoffset() + oy);

                m_xmouse = event.motion.x;
                m_ymouse = event.motion.y;
            }
        } break;

        case SDL_MOUSEBUTTONDOWN: {
            if (event.button.button == SDL_BUTTON_LEFT || event.button.button == SDL_BUTTON_MIDDLE) {
                SDL_CaptureMouse(SDL_TRUE);
                
                m_mouse_held = true;
                m_xmouse = event.button.x;
                m_ymouse = event.button.y;
                
                if (event.button.clicks == 2) {
                    s32 default_ox = static_cast<s32>(camera.get_default_xoffset() / camera.get_scale());
                    s32 default_oy = static_cast<s32>(camera.get_default_yoffset() / camera.get_scale());
                    
                    camera.set_xoffset(default_ox);
                    camera.set_yoffset(default_oy);
                }
            }
        } break;

        case SDL_MOUSEBUTTONUP: {
            if (event.button.button == SDL_BUTTON_LEFT || event.button.button == SDL_BUTTON_MIDDLE) {
                SDL_CaptureMouse(SDL_FALSE);
                m_mouse_held = false;
            }
        } break;

        case SDL_MOUSEWHEEL: {
            f32 curr_scale = camera.get_scale();
            f32 scale_step = camera.get_default_scale_step();

            s32 mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            Camera_Coords before = camera.world_to_screen(static_cast<f32>(mouse_x), static_cast<f32>(mouse_y));

            if (event.wheel.y > 0) {
                camera.set_scale(CLAMP_BOT(curr_scale + scale_step, 3));
            } else if (event.wheel.y < 0) {
                camera.set_scale(CLAMP_TOP(curr_scale - scale_step, 1));
            }

            Camera_Coords after = camera.world_to_screen(static_cast<f32>(mouse_x), static_cast<f32>(mouse_y));

            s32 ox = static_cast<s32>(camera.get_xoffset() - (before.x - after.x));
            s32 oy = static_cast<s32>(camera.get_yoffset() - (before.y - after.y));
            camera.set_xoffset(ox);
            camera.set_yoffset(oy);
        } break;
    }
}
