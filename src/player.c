#include <allegro.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include "header.h"

void displayLife(game3d_t *game)
{
    char life[10];

    for (int i = 0; i < game->nbNpc; i++) {
        if (game->opps[i].attacking == 1) {
            game->player->life -= game->opps[i].dps;
            game->opps[i].attacking = 2;
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

int isCollision(int x, int y, char **map)
{
    x = x / 64;
    y = y / 64;
    if (map[y][x] != '*')
        return 1;
    return 0;
}

void movePlayer(game3d_t *game)
{
    if (game->oldMouseX < mouse_x) {
        game->player->angle -= game->player->sensitivity * (mouse_x - game->oldMouseX);
        game->skyX -= 15;
        game->skyX2 -= 15;
    }else if (game->oldMouseX > mouse_x) {
        game->player->angle += game->player->sensitivity * (game->oldMouseX - mouse_x);
        game->skyX += 15;
        game->skyX2 += 15;
    }

    if (key[KEY_UP] && !isCollision(game->player->screenX + round(cos(game->player->angle)) * 10, game->player->screenY - round(sin(game->player->angle)) * 10, game->map)) {
        game->player->screenX += round(cos(game->player->angle)) * 2;
        game->player->screenY -= round(sin(game->player->angle)) * 2;
        // game->player->guns[game->player->indexGun]->offset += game->player->guns[game->player->indexGun]->typeOffset;
    }
    if (key[KEY_DOWN] && !isCollision(game->player->screenX - round(cos(game->player->angle)) * 10, game->player->screenY + round(sin(game->player->angle)) * 10, game->map)) {
        game->player->screenX -= round(cos(game->player->angle)) * 2;
        game->player->screenY += round(sin(game->player->angle)) * 2;
        // game->player->guns[game->player->indexGun]->offset += game->player->guns[game->player->indexGun]->typeOffset;
    }
    if (key[KEY_RIGHT] && !isCollision(game->player->screenX + round(cos(game->player->angle - (PI / 2))) * 10, game->player->screenY - round(sin(game->player->angle - (PI / 2))) * 10, game->map)) {
        game->player->screenX += round(cos(game->player->angle - (PI / 2)));
        game->player->screenY -= round(sin(game->player->angle - (PI / 2)));
        // game->player->guns[game->player->indexGun]->offset += game->player->guns[game->player->indexGun]->typeOffset;
    }
    if (key[KEY_LEFT] && !isCollision(game->player->screenX - round(cos(game->player->angle - (PI / 2))) * 10, game->player->screenY + round(sin(game->player->angle - (PI / 2))) * 10, game->map)) {
        game->player->screenX -= round(cos(game->player->angle - (PI / 2)));
        game->player->screenY += round(sin(game->player->angle - (PI / 2)));
        // game->player->guns[game->player->indexGun]->offset += game->player->guns[game->player->indexGun]->typeOffset;
    }
}

player_t *createPlayer(void)
{
    player_t *player = malloc(sizeof(player_t));

    checkPtrNull(player, "Exit Failure: malloc failed\n");

    player->guns = loadGuns(player->guns);
    player->sensitivity = 0.0175; // 0.0175 radius = 1°
    player->angle = 0.01;
    player->life = 100;
    player->screenX = 200;
    player->screenY = 135;
    player->isWalked = false;
    player->indexGun = 0;
    player->indexSpriteGun = 0;
    player->speedAnim = 7;
    player->currentAnim = 0;

    return player;
}
