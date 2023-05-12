#include <time.h>
#include <allegro.h>

#include <stdio.h>
#include <winalleg.h>
#include "header.h"

void gameLoop(void)
{
    game3d_t *game = createGame();

    PlaySound("./assets/background.wav", NULL, SND_ASYNC | SND_LOOP);

    while (!key[KEY_ESC]) {
        clear_bitmap(game->buffer);

        playerHeal(game);
        displaySky(game);
        movePlayer(game);
        raycasting(game);
        for (int i = 0; i < game->nbNpc; i++) {
            calcSprite(game, i);
            animOpps(&game->opps[i], game->oppsAnim);
        }
        display3D(game);
        displayGun(game);
        displayMiniMap(game);
        displayTarget(game);
        displayLife(game);
        displayScore(game);
        game->oldMouseX = mouse_x;
        game->indexSaveData = 0;
        pauseMenu(game);

        blit(game->buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    PlaySound(NULL, NULL, SND_ASYNC | SND_LOOP);
    freeGame(game);
}

int main(void)
{
    allegro_init();
    BITMAP *buffer;

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

    gameLoop();
   
    allegro_exit();
    return 0;
}
END_OF_MAIN();