#include <time.h>
#include <allegro.h>
#include "header.h"

int main(void)
{
    allegro_init();
    BITMAP *buffer;
    int numNpc;

    srand(time(NULL));
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_NONE, "");

    set_color_depth(32);
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0) != 0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    set_alpha_blender();

    show_mouse(screen);

    gameLoop();
   
    allegro_exit();
    return 0;
}
END_OF_MAIN();