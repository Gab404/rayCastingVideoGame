#include <allegro.h>
#include <math.h>
#include "header.h"

void displayTarget(game3d_t *game)
{
    line(game->buffer, game->midScreenW - 20, game->midScreenH, game->midScreenW + 20, game->midScreenH, makecol(255, 0, 0));
    line(game->buffer, game->midScreenW, game->midScreenH - 20, game->midScreenW, game->midScreenH + 20, makecol(255, 0, 0));
}

void displayMiniMap(game3d_t *game)
{
    for (int i = 0; game->map[i] != NULL; i++)
        for (int j = 0; game->map[i][j] != '\0'; j++) {
            if (game->map[i][j] == '*')
                rectfill(game->buffer, j * 7, i * 7, j * 7 + 7, i * 7 + 7, makecol(255, 255, 255));
            else
                rectfill(game->buffer, j * 7, i * 7, j * 7 + 7, i * 7 + 7, makecol(0, 0, 0));
        }
    circlefill(game->buffer, game->player->posMapX * 7 + 3, game->player->posMapY * 7 + 3, 2, makecol(0, 255, 0));
    for (int i = 0; i < game->nbNpc; i++) {
        if (game->opps[i].IndexAnim != 2)
            circlefill(game->buffer, game->opps[i].x / 64 * 7 + 3, game->opps[i].y / 64 * 7 + 3, 2, makecol(255, 0, 0));
    }
}

void displaySky(game3d_t *game)
{
    if (game->skyX < 0)
        game->skyX2 = game->skyX + SCREEN_W + 10;
    else if (game->skyX > 0)
        game->skyX2 = game->skyX - (SCREEN_W + 10);
    if (game->skyX2 < 0)
        game->skyX = game->skyX2 + SCREEN_W + 10;
    else if (game->skyX2 > 0)
        game->skyX = game->skyX2 - (SCREEN_W + 10);

    stretch_blit(game->sky, game->buffer, 0, 0, game->sky->w, game->sky->h, game->skyX, 0, game->buffer->w + 10, game->buffer->h * 0.8);
    stretch_blit(game->sky, game->buffer, 0, 0, game->sky->w, game->sky->h, game->skyX2, 0, game->buffer->w + 10, game->buffer->h * 0.8);
}

void display3D(game3d_t *game)
{
    int tmpOpps;
    int projWidth, projHeight;
    float distWall;
    int heightWall;
    int offset;
    int indexOpps;
    float initAngle = game->player->angle + (0.0175 * 60) / 2.00;
    BITMAP *tmpSprite;

    quickSort(game->allDist, game->allPosTexture, game->allTypeWall, game->allPos, 0, game->indexSaveData - 1);

    for (int i = 0; i < game->indexSaveData; i++) {
        if (game->allPosTexture[i] < 0) { // display sprite
            
            tmpOpps = (game->allPosTexture[i] + 1) * -1;
            indexOpps = (int)game->allTypeWall[i];
            tmpSprite = game->oppsAnim[tmpOpps][game->opps[indexOpps].IndexAnim][game->opps[indexOpps].indexSprite];
            projWidth = (20000 / game->allDist[i]); // => projWidth / 2
            projHeight = 40000 / game->allDist[i];
            if (game->opps[indexOpps].life != 0)
                rectfill(game->buffer, game->midScreenW + (game->allPos[i] * 4) - projWidth / 2, game->midScreenH - projHeight / 3, game->midScreenW + (game->allPos[i] * 4) - projWidth / 2 + (game->opps[indexOpps].life * projWidth) / game->opps[indexOpps].maxLife, game->midScreenH - projHeight / 3 + projHeight / 50, makecol(255, 0, 0));
            stretch_sprite(game->buffer, tmpSprite, game->midScreenW + (game->allPos[i] * 4) - projWidth, game->midScreenH - projHeight / 3, projWidth * 2, projHeight);
        } else { // display wall
            distWall = game->allDist[i] * cos((initAngle - game->allPos[i] * 0.004375) - game->player->angle); // enlever l'aspect de fish-eye
            heightWall = round(40000.00 / distWall);
            stretch_blit(game->texture[game->allTypeWall[i] - 'a'], game->buffer, game->allPosTexture[i], 0, 1, 64, game->allPos[i] * 4, game->midScreenH - heightWall / 2, 4, heightWall);
            rectfill(game->buffer, game->allPos[i] * 4, game->midScreenH + heightWall / 2, game->allPos[i] * 4 + 4, game->midScreenH + heightWall + 300, makecol(30, 30, 30));
        }
    }
}
