#include "utils.h"

#include "./ui/gui.h"
#include "./rendering/camera.h"
#include "./events/event_handler.h"

#include "./rendering/renderer.h"

int main(int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);

    // We could also allocate those through smart-pointers if C++14
    //
    // std::unique_pointer<Camera> camera = std::make_unique<Camera>();
    // ...
    
    GUI_Layer *gui = new GUI_Layer;
    Camera *camera = new Camera;
    Event_Handler *event_handler = new Event_Handler;
    
    Renderer renderer("Lissajous", 1280, 720);
    renderer.setup_dependencies(gui, camera, event_handler);
    
    renderer.render();

    return 0;
}
