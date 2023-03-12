#ifndef INDICATOR_H
#define INDICATOR_H

#include "types.h"

class Indicator {
public:
    Indicator();

    inline f32 get_xpos() const noexcept { return(m_xpos); }
    inline f32 get_ypos() const noexcept { return(m_ypos); }
    
    void update_indicator(f32 xpos, f32 ypos, f32 xspeed, f32 yspeed);
    void update_pos();
    
private:
    f32 m_xpos;
    f32 m_ypos;
    f32 m_xspeed;
    f32 m_yspeed;
    
    f32 m_xstart;
    f32 m_ystart;
};

#endif // INDICATOR_H
