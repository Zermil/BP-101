#include "utils.h"
#include "renderer.h"

int main(int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);

    Renderer renderer("Lissajous", 1280, 720);    
    renderer.render();

    return 0;
}
