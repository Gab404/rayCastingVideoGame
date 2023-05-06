#include <allegro.h>
#include "header.h"

#include <stdio.h>

BITMAP **loadTexture(char *filepath)
{
    BITMAP *tmpTexture = load_bitmap(filepath, NULL);
    BITMAP **texture;
    int nbTexture;

    checkPtrNull(tmpTexture, "Exit Failure: error at texture creation\n");
    nbTexture = tmpTexture->h / 64;
    texture = malloc(sizeof(BITMAP *) * (nbTexture + 1));

    for (int i = 0; i < nbTexture; i++) {
        texture[i] = create_bitmap(64, 64);
        stretch_blit(tmpTexture, texture[i], 0, i * 64, 64, 64, 0, 0, 64, 64);
    }
    texture[nbTexture] = NULL;

    return texture;
}

int isBadPos(game3d_t *game, int x ,int y)
{
    for (int i = 0; i < game->nbNpc; i++) {
        if (game->badPosX[i] == x * SIZE + 20 && game->badPosY[i] == y * SIZE + 20)
            return 1;
    }
    return 0;
}

void generateSpawnCoord(game3d_t *game, int *x, int *y)
{
    int col = 0, row = 0;

    while (game->map[row] != NULL)
        row++;
    while(game->map[0][col] != '\0')
        col++;

    do {
        *x = rand() % ((col - 1) - 1) + 1;
        *y = rand() % ((row - 1) - 1) + 1;
    } while (game->map[*y][*x] != '*' || isBadPos(game, *x, *y));
}

game3d_t *createGame(void)
{
    game3d_t *game = malloc(sizeof(game3d_t));

    checkPtrNull(game, "Exit Failure: malloc failed\n");
    game->buffer = create_bitmap(SCREEN_W, SCREEN_H);
    game->skyX = 0;
    game->skyX2 = SCREEN_W + 10;
    game->oldMouseX = mouse_x;
    game->map = loadMap("./conf/map.conf", &game->row, &game->col);
    game->sky = load_bitmap("./assets/skyNight.bmp", NULL);
    game->texture = loadTexture("./assets/texture.bmp");
    game->player = createPlayer();
    game->munLogo = load_bitmap("./assets/munLogo.bmp", NULL);
    loadOpps(game);

    checkPtrNull(game->munLogo, "Exit Failure: loading munition logo bitmap failed\n");
    checkPtrNull(game->texture, "Exit Failure: creation texture failed\n");
    checkPtrNull(game->sky, "Exit Failure: creation sky failed\n");
    checkPtrNull(game->buffer, "Exit Failure: creation buffer failed\n");

    game->indexSaveData = 0;
    game->midScreenW = SCREEN_W / 2;
    game->midScreenH = SCREEN_H / 2;
    game->volume = 200;
    game->nbNpc = 30;
    
    return game;
}