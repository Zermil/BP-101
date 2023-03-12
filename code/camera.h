#ifndef CAMERA_H
#define CAMERA_H

#include "types.h"

struct Camera_Coords {
    f32 x;
    f32 y;
};

class Camera {
public:
    Camera();

    Camera_Coords screen_to_world(f32 sx, f32 sy);
    Camera_Coords world_to_screen(f32 wx, f32 wy);

    inline void set_default_offsets(s32 xoffset, s32 yoffset) noexcept {
        m_xoffset = xoffset;
        m_default_xoffset = xoffset;

        m_yoffset = yoffset;
        m_default_yoffset = yoffset;
    }

    inline s32 get_default_xoffset() const noexcept { return(m_default_xoffset); }
    inline s32 get_default_yoffset() const noexcept { return(m_default_yoffset); }
    inline f32 get_default_scale_step() const noexcept { return(m_default_scale_step); }

    inline s32 get_xoffset() const noexcept { return(m_xoffset); }
    inline s32 get_yoffset() const noexcept { return(m_yoffset); }
    inline f32 get_scale() const noexcept { return(m_scale); }
    
    inline void set_xoffset(s32 xoffset) noexcept { m_xoffset = xoffset; }
    inline void set_yoffset(s32 yoffset) noexcept { m_yoffset = yoffset; }
    inline void set_scale(f32 scale) noexcept { m_scale = scale; }
    
private:
    s32 m_xoffset;
    s32 m_yoffset;

    s32 m_default_xoffset;
    s32 m_default_yoffset;
    
    f32 m_scale;
    f32 m_default_scale_step;
};

#endif // CAMERA_H
