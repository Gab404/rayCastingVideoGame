#include <allegro.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include "header.h"

void playerHeal(game3d_t *game)
{
    time_t currentTime = time(NULL);

    if (currentTime - game->player->timeAttackedHeal >= 5) {
        if (currentTime - game->player->timeHeal >= 1 && game->player->life < 100) {
            game->player->timeHeal = currentTime;
            game->player->life++;
        }
    }
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
    int moved = 0;

    if (game->oldMouseX < mouse_x && !game->centerCursor) {
        game->player->angle -= game->player->sensitivity * (mouse_x - game->oldMouseX);
        game->skyX -= 15;
        game->skyX2 -= 15;
    }else if (game->oldMouseX > mouse_x && !game->centerCursor) {
        game->player->angle += game->player->sensitivity * (game->oldMouseX - mouse_x);
        game->skyX += 15;
        game->skyX2 += 15;
    }

    if ((key[KEY_UP] || key[KEY_W]) && !isCollision(game->player->screenX + round(cos(game->player->angle)) * 10, game->player->screenY - round(sin(game->player->angle)) * 10, game->map) && clock() - game->player->clockStep >= 5) {
        game->player->screenX += round(cos(game->player->angle)) * 2;
        game->player->screenY -= round(sin(game->player->angle)) * 2;
        game->player->guns[game->player->indexGun]->offset += game->player->guns[game->player->indexGun]->typeOffset;
        moved = 1;
    }
    if ((key[KEY_DOWN] || key[KEY_S]) && !isCollision(game->player->screenX - round(cos(game->player->angle)) * 10, game->player->screenY + round(sin(game->player->angle)) * 10, game->map) && clock() - game->player->clockStep >= 5) {
        game->player->screenX -= round(cos(game->player->angle)) * 2;
        game->player->screenY += round(sin(game->player->angle)) * 2;
        game->player->guns[game->player->indexGun]->offset += game->player->guns[game->player->indexGun]->typeOffset;
        moved = 1;
    }
    if ((key[KEY_RIGHT] || key[KEY_D]) && !isCollision(game->player->screenX + round(cos(game->player->angle - (PI / 2))) * 10, game->player->screenY - round(sin(game->player->angle - (PI / 2))) * 10, game->map) && clock() - game->player->clockStep >= 5) {
        game->player->screenX += round(cos(game->player->angle - (PI / 2)));
        game->player->screenY -= round(sin(game->player->angle - (PI / 2)));
        game->player->guns[game->player->indexGun]->offset += game->player->guns[game->player->indexGun]->typeOffset;
        moved = 1;
    }
    if ((key[KEY_LEFT] || key[KEY_A]) && !isCollision(game->player->screenX - round(cos(game->player->angle - (PI / 2))) * 10, game->player->screenY + round(sin(game->player->angle - (PI / 2))) * 10, game->map) && clock() - game->player->clockStep >= 5) {
        game->player->screenX -= round(cos(game->player->angle - (PI / 2)));
        game->player->screenY += round(sin(game->player->angle - (PI / 2)));
        game->player->guns[game->player->indexGun]->offset += game->player->guns[game->player->indexGun]->typeOffset;
        moved = 1;
    }
    if (moved)
        game->player->clockStep = clock();
}

player_t *createPlayer(void)
{
    player_t *player = malloc(sizeof(player_t));

    checkPtrNull(player, "Exit Failure: malloc failed\n");

    player->guns = loadGuns(player->guns);
    player->sensitivity = 0.0175; // 0.0175 radius = 1°
    player->angle = 0.01;
    player->life = 100;
    player->screenX = 250;
    player->screenY = 135;
    player->isWalked = false;
    player->indexGun = 0;
    player->indexSpriteGun = 0;
    player->speedAnim = 7;
    player->currentAnim = 0;
    player->timeHeal = time(NULL);
    player->timeAttackedHeal = 0;
    player->score = 0;
    player->clockStep = clock();

    return player;
}
