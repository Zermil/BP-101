#include "indicator.h"

Indicator::Indicator()
    : m_xpos(0.0f), m_ypos(0.0f),
      m_xstart(0.0f), m_ystart(0.0f)
{
    // ...
}

void Indicator::update_indicator(f32 xpos, f32 ypos, f32 xspeed, f32 yspeed)
{    
    if (m_xstart != xpos || m_ystart != ypos ||
        m_xspeed != xspeed || m_yspeed != yspeed)
    {
        m_xpos = xpos;
        m_ypos = ypos;
        m_xspeed = xspeed;
        m_yspeed = yspeed;
        
        m_xstart = xpos;
        m_ystart = ypos;
    }
}

void Indicator::update_pos()
{
    m_xpos += m_xspeed;
    m_ypos += m_yspeed;
}
