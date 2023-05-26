#include <allegro.h>
#include <stdbool.h>
#include <math.h>
#include "header.h"

void resetAngle(float *angle)
{
    if (*angle > (2 * PI))
        *angle -= (2 * PI);
    else if (*angle < 0)
        *angle += (2 * PI);
}

void getPosCase(player_t *player)
{
    player->posMapX = (player->screenX) / 64;
    player->posMapY = (player->screenY) / 64;
    player->posxCase = player->screenX - (player->screenX) / 64 * 64;
    player->posyCase = 63 - (player->screenY - (player->screenY) / 64 * 64);
}

float rayCast(game3d_t *game, float angle, int *posTexture, int *typeWall)
{
    float x_vert, y_vert;
    float y_hor, x_hor;
    int tile_vert_x, tile_vert_y;
    int tile_hor_x, tile_hor_y;
    float dx, dy;
    float depth_vert, delta_depth;
    int ox = game->player->screenX;
    int oy = game->player->screenY;
    float depth_hor;
    int texture_hor = 1, texture_vert = 1;

    float sin_a = -sin(angle);
    float cos_a = cos(angle);

    // Horizontals
    if (sin_a >= 0) {
        y_hor = (game->player->posMapY * 64) + 64;
        dy = 64;
    } else {
        y_hor = (game->player->posMapY * 64) - 0.0064;
        dy = -64;
    }

    depth_hor = (y_hor - oy) / sin_a;
    x_hor = ox + depth_hor * cos_a;

    delta_depth = dy / sin_a;
    dx = delta_depth * cos_a;

    while (1) {
        tile_hor_x = (int)(x_hor) / 64;
        tile_hor_y = (int)(y_hor) / 64;
        if (tile_hor_x < 0)
            tile_hor_x = 0;
        else if (tile_hor_x > game->col)
            tile_hor_x = game->col;
        if (tile_hor_y > game->row)
            tile_hor_y = game->row;
        else if (tile_hor_y < 0)
            tile_hor_y = 0;
        if (game->map[tile_hor_y][tile_hor_x] != '*')
            break;
        x_hor += dx;
        y_hor += dy;
        depth_hor += delta_depth;
    }

    // Vericals
    if (cos_a > 0) {
        x_vert = (game->player->posMapX * 64) + 64;
        dx = 64;
    } else {
        x_vert = (game->player->posMapX * 64) - 0.0064;
        dx = -64;
    }

    delta_depth = dx / cos_a;
    depth_vert = (x_vert - ox) / cos_a;

    y_vert = oy + depth_vert * sin_a;
    dy = delta_depth * sin_a;
    while (1) {
        tile_vert_x = (int)(x_vert) / 64;
        tile_vert_y = (int)(y_vert) / 64;
        if (tile_vert_y < 0)
            tile_vert_y = 0;
        else if (tile_vert_y > game->row)
            tile_vert_y = game->row;
        if (tile_vert_x > game->col)
            tile_vert_x = game->col;
        else if (tile_vert_x < 0)
            tile_vert_x = 0;
        if (game->map[tile_vert_y][tile_vert_x] != '*')
            break;
        x_vert += dx;
        y_vert += dy;
        depth_vert += delta_depth;
    }

    if (depth_vert < depth_hor) { // choice the shortest vector
        *posTexture = 64 - ((int)(y_vert) - (tile_vert_y * 64));
        *typeWall = (int)game->map[tile_vert_y][tile_vert_x];
        return depth_vert;
    } else {
        *posTexture = (int)(x_hor) - (tile_hor_x * 64);
        *typeWall = (int)game->map[tile_hor_y][tile_hor_x];
        return depth_hor;
    }
}

void raycasting(game3d_t *game)
{
    float distWall = 0;
    int heightWall;
    int j = -1;

    getPosCase(game->player);
    for (float i = game->player->angle + ((0.0175 * 60) / 2.00); i > game->player->angle - ((0.0175 * 60) / 2.00); i -= 0.004375) {
        j++;
        game->allDist[j] = rayCast(game, i, &game->allPosTexture[j], &game->allTypeWall[j]);
        game->allPos[j] = j;
    }
    resetAngle(&game->player->angle);
    game->player->mapX = ((game->player->screenX) / 64);
    game->player->mapY = ((game->player->screenY) / 64);
    game->indexSaveData = j;
}