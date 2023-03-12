#ifndef GUI_H
#define GUI_H

#include "types.h"
#include <imgui/imgui.h>
#include <SDL2/SDL.h>

class GUI_Layer {
public:
    GUI_Layer(const GUI_Layer& g) = delete;
    GUI_Layer();
    ~GUI_Layer();

    void initialize_gui(SDL_Renderer *renderer, SDL_Window *window);
    
    void begin_frame();
    void end_frame();

    void draw_control_panel();
    void process_events(SDL_Event *e);
    
    inline f32 get_xangle() const noexcept { return(m_xangle); }
    inline f32 get_yangle() const noexcept { return(m_yangle); }

    inline s32 get_xspeed() const noexcept { return(m_xspeed); }
    inline s32 get_yspeed() const noexcept { return(m_yspeed); }

    inline bool get_animate() const noexcept { return(m_animate); }

private:    
    ImFont *m_font;
    
    f32 m_xangle;
    f32 m_yangle;
    
    s32 m_xspeed;
    s32 m_yspeed;

    bool m_animate;
};

#endif // GUI_H
