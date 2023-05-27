#include <allegro.h>
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

game3d_t *createGame(void)
{
    game3d_t *game = malloc(sizeof(game3d_t));

    checkPtrNull(game, "Exit Failure: malloc failed\n");
    game->nbNpc = getNumNpc();
    clear_bitmap(screen);
    game->buffer = create_bitmap(SCREEN_W, SCREEN_H);
    game->skyX = 0;
    game->skyX2 = SCREEN_W + 10;
    game->oldMouseX = mouse_x;
    game->map = loadMap("./conf/map.conf", &game->row, &game->col);
    game->sky = load_bitmap("./assets/skyNight.bmp", NULL);
    game->texture = loadTexture("./assets/texture.bmp");
    game->player = createPlayer();
    game->munLogo = load_bitmap("./assets/munLogo.bmp", NULL);
    game->pauseBanner = load_bitmap("./assets/pause.bmp", NULL);
    loadOpps(game);

    checkPtrNull(game->munLogo, "Exit Failure: loading munition logo bitmap failed\n");
    checkPtrNull(game->texture, "Exit Failure: creation texture failed\n");
    checkPtrNull(game->sky, "Exit Failure: creation sky failed\n");
    checkPtrNull(game->buffer, "Exit Failure: creation buffer failed\n");
    checkPtrNull(game->pauseBanner, "Exit Failure: load pause bitmap failed");

    game->indexSaveData = 0;
    game->midScreenW = SCREEN_W / 2;
    game->midScreenH = SCREEN_H / 2;
    game->volume = 50;
    
    return game;
}