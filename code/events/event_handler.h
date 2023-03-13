#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>

#include "../types.h"
#include "../rendering/camera.h"

class Event_Handler {
public:
    Event_Handler();
    
    void handle_camera_events(SDL_Event event, Camera& camera);
    
private:
    bool m_mouse_held;

    s32 m_xmouse;
    s32 m_ymouse;
};

#endif // EVENT_HANDLER_H
