#include <allegro.h>
#include <math.h>
#include <stdio.h>
#include "header.h"

void displayScore(game3d_t *game)
{
    char score[10];

    sprintf(score, "%d", game->player->score);
    textout_ex(game->buffer, font, "Score:", SCREEN_W - 110, 50, makecol(255, 255, 255), -1);
    textout_ex(game->buffer, font, score, SCREEN_W - 50, 50, makecol(255, 255, 255), -1);
}

void displayLife(game3d_t *game)
{
    char life[10];

    for (int i = 0; i < game->nbNpc; i++) {
        if (game->opps[i].attacking == 1) {
            game->player->life -= game->opps[i].dps;
            game->opps[i].attacking = 2;
            game->player->timeAttackedHeal = time(NULL);
        }
    }
    if (game->player->life < 0)
        game->player->life = 0;
    sprintf(life, "%d", game->player->life);
    rectfill(game->buffer, 12, SCREEN_H - 23, 217, SCREEN_H - 7, makecol(0, 0, 0));
    rectfill(game->buffer, 15, SCREEN_H - 20, 15 + game->player->life * 2, SCREEN_H - 10, makecol(255, 0, 0));
    textout_ex(game->buffer, font, life, 18, SCREEN_H - 18, makecol(255, 255, 255), -1);
    textout_ex(game->buffer, font, "%", 43, SCREEN_H - 18, makecol(255, 255, 255), -1);
}

void displayTarget(game3d_t *game)
{
    line(game->buffer, game->midScreenW - 20, game->midScreenH, game->midScreenW + 20, game->midScreenH, makecol(255, 0, 0));
    line(game->buffer, game->midScreenW, game->midScreenH - 20, game->midScreenW, game->midScreenH + 20, makecol(255, 0, 0));
}

void displayMiniMap(game3d_t *game)
{
    int sizeTile = 200 / game->col;
    
    for (int i = 0; game->map[i] != NULL; i++)
        for (int j = 0; game->map[i][j] != '\0'; j++) {
            if (game->map[i][j] == '*')
                rectfill(game->buffer, j * sizeTile, i * sizeTile, j * sizeTile + sizeTile, i * sizeTile + sizeTile, makecol(255, 255, 255));
            else
                rectfill(game->buffer, j * sizeTile, i * sizeTile, j * sizeTile + sizeTile, i * sizeTile + sizeTile, makecol(0, 0, 0));
        }

    circlefill(game->buffer, game->player->posMapX * sizeTile + ((game->player->posxCase / 64) * sizeTile), (game->player->posMapY + 1) * sizeTile - ((game->player->posyCase / 64) * sizeTile), 2, makecol(0, 255, 0));
    for (int i = 0; i < game->nbNpc; i++) {
        if (game->opps[i].IndexAnim != 2) {
            circlefill(game->buffer, game->opps[i].x / 64 * sizeTile + sizeTile / 2, game->opps[i].y / 64 * sizeTile + sizeTile / 2, 2, makecol(255, 0, 0));
        }
    }

    line(game->buffer, game->player->posMapX * sizeTile + ((game->player->posxCase / 64) * sizeTile), (game->player->posMapY + 1) * sizeTile - ((game->player->posyCase / 64) * sizeTile), game->player->posMapX * sizeTile + ((game->player->posxCase / 64) * sizeTile) + cos((double)game->player->angle) * 15, (game->player->posMapY + 1) * sizeTile - ((game->player->posyCase / 64) * sizeTile) - sin((double)game->player->angle) * 15, makecol(0, 0, 0));
}

void displayFps(int *fps, char *str, BITMAP *buffer, time_t *fpsClock)
{
    if (time(NULL) - *fpsClock >= 1) {
        *fpsClock = time(NULL);
        sprintf(str, "%d", *fps);
        *fps = 0;
    }
    *fps += 1;
    textout_ex(buffer, font, "FPS:", 30, 150, makecol(255, 255, 255), -1);
    if (str[0] != '0')
        textout_ex(buffer, font, str, 70, 150, makecol(255, 255, 255), -1);
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
        if (game->allPosTexture[i] < 0 && game->allDist[i] < 800) { // display sprite
            tmpOpps = (game->allPosTexture[i] + 1) * -1;
            indexOpps = game->allTypeWall[i];
            tmpSprite = game->oppsAnim[tmpOpps][game->opps[indexOpps].IndexAnim][game->opps[indexOpps].indexSprite];
            projWidth = (20000 / game->allDist[i]); // => projWidth / 2
            projHeight = 40000 / game->allDist[i];
            if (game->opps[indexOpps].life != 0)
                rectfill(game->buffer, game->midScreenW + (game->allPos[i] * 4) - projWidth / 2 + game->allDist[i] / 15, game->midScreenH - projHeight / 3, game->midScreenW + (game->allPos[i] * 4) - projWidth / 2 + (game->opps[indexOpps].life * projWidth) / game->opps[indexOpps].maxLife + game->allDist[i] / 15, game->midScreenH - projHeight / 3 + projHeight / 50, makecol(255, 0, 0));
            stretch_sprite(game->buffer, tmpSprite, game->midScreenW + (game->allPos[i] * 4) - projWidth + game->allDist[i] / 15, game->midScreenH - projHeight / 3, projWidth * 2, projHeight);
        } else if (game->allPosTexture[i] >= 0) { // display wall
            
            distWall = game->allDist[i] * cos((initAngle - game->allPos[i] * 0.004375) - game->player->angle); // enlever l'aspect de fish-eye
            heightWall = round(40000.00 / distWall);
            stretch_blit(game->texture[(char)game->allTypeWall[i] - 'a'], game->buffer, game->allPosTexture[i], 0, 1, 64, game->allPos[i] * 4, game->midScreenH - heightWall / 2, 4, heightWall);
            rectfill(game->buffer, game->allPos[i] * 4, game->midScreenH + heightWall / 2, game->allPos[i] * 4 + 4, game->midScreenH + heightWall + 300, makecol(30, 30, 30));
        }
    }
}