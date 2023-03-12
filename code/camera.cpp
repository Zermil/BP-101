#include <cstdio>

#include "camera.h"

Camera::Camera()
    : m_xoffset(0), m_yoffset(0), m_scale(1.0f),
      m_default_xoffset(0), m_default_yoffset(0),
      m_default_scale_step(0.8f)
{
    // ...
}

Camera_Coords Camera::screen_to_world(f32 sx, f32 sy)
{
    Camera_Coords coords = {0};
    coords.x = (sx + m_xoffset) * m_scale;
    coords.y = (sy + m_yoffset) * m_scale;
    
    return(coords);
}

Camera_Coords Camera::world_to_screen(f32 wx, f32 wy)
{
    Camera_Coords coords = {0};
    coords.x = (wx / m_scale) - m_xoffset;
    coords.y = (wy / m_scale) - m_yoffset;

    return(coords);
}
