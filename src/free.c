#include <stdlib.h>
#include "header.h"

void freePlayer(player_t *player)
{
    for (int i = 0; player->guns[i] != NULL; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; player->guns[i]->sprite[j][k] != NULL; k++)
                destroy_bitmap(player->guns[i]->sprite[j][k]);
            free(player->guns[i]->sprite[j]);
        }
        free(player->guns[i]->sprite);
        destroy_sample(player->guns[i]->reloadSound);
        destroy_sample(player->guns[i]->shootSound);
        free(player->guns[i]);
    }
    free(player->guns);
    free(player);
}

void freeArray(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

void freeOppsSprite(game3d_t *game)
{
    for (int i = 0; game->oppsAnim[i] != NULL; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; game->oppsAnim[i][j][k] != NULL; k++)
                destroy_bitmap(game->oppsAnim[i][j][k]);
            free(game->oppsAnim[i][j]);
        }
        free(game->oppsAnim[i]);
    }
    free(game->oppsAnim);
}

void freeGame(game3d_t *game)
{
    destroy_bitmap(game->buffer);
    freeArray(game->map);
    freeSommets(game->sommets);
    destroy_bitmap(game->munLogo);
    destroy_bitmap(game->sky);
    for (int i = 0; game->texture[i] != NULL; i++)
        destroy_bitmap(game->texture[i]);
    freePlayer(game->player);
    freeOppsSprite(game);
    free(game->texture);
    free(game->allDist);
    free(game->allPos);
    free(game->allPosTexture);
    free(game->allTypeWall);
    free(game->opps);
    free(game->badPosX);
    free(game->badPosY);
    free(game);
}