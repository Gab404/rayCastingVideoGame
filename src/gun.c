#include <allegro.h>
#include <stdio.h>
#include "header.h"

void changeGun(player_t *player)
{
    if (!player->guns[player->indexGun]->reload && !player->guns[player->indexGun]->shooting) {
        if (key[KEY_1] && player->indexGun != 0) {
            player->indexGun--;
            player->indexSpriteGun = 0;
        } else if (key[KEY_2] && player->guns[player->indexGun + 1] != NULL) {
            player->indexGun++;
            player->indexSpriteGun = 0;
        }
    }
}

void animWalk(player_t *player)
{
    if (player->guns[player->indexGun]->offset >= 20)
        player->guns[player->indexGun]->typeOffset = -1;
    else if (player->guns[player->indexGun]->offset <= 0)
        player->guns[player->indexGun]->typeOffset = 1;
}

void handleAnimGun(player_t *player, int volume)
{
    int i = player->indexGun;

    if (mouse_b & 1 && !player->guns[i]->shooting && !player->guns[i]->reload) {
        if (player->guns[i]->currentShoot == player->guns[i]->nbShoot) { // plus de munition
            player->guns[i]->currentShoot = 0;
            player->guns[i]->reload = 1;
            player->guns[i]->shooting = 0;
            player->guns[i]->offset = 0;
            play_sample(player->guns[i]->reloadSound, volume, 128, 1000, 0);
        } else {
            player->guns[i]->currentShoot++; 
            player->guns[i]->reload = 0;
            player->guns[i]->shooting = 1;
            player->guns[i]->offset = 0;
            player->shooting = 1;
            play_sample(player->guns[i]->shootSound, volume, 128, 1000, 0);
        }
    }

    if (player->guns[i]->shooting) { // si on tire
        if (player->guns[i]->sprite[player->guns[i]->reload][player->indexSpriteGun + 1] == NULL) {
            player->indexSpriteGun = 0;
            player->guns[i]->shooting = 0;
        } else if (player->currentAnim == player->speedAnim){
            player->indexSpriteGun++;
            player->currentAnim = 0;
            player->shooting = 0;
        } else
            player->currentAnim++;
    } else if (player->guns[i]->reload) { // si on recharge
        if (player->guns[i]->sprite[player->guns[i]->reload][player->indexSpriteGun + 1] == NULL) {
            player->indexSpriteGun = 0;
            player->guns[i]->reload = 0;
        } else if (player->currentAnim == player->speedAnim){
            player->indexSpriteGun++;
            player->currentAnim = 0;
        } else
            player->currentAnim++;
    }
}

void displayGun(game3d_t *game)
{
    char munition[10];

    animWalk(game->player);
    handleAnimGun(game->player, game->volume);
    changeGun(game->player);

    stretch_sprite(game->buffer, game->player->guns[game->player->indexGun]->sprite[game->player->guns[game->player->indexGun]->reload][game->player->indexSpriteGun], 0, game->player->guns[game->player->indexGun]->offset, SCREEN_W, SCREEN_H);
    sprintf(munition, "%d", game->player->guns[game->player->indexGun]->nbShoot - game->player->guns[game->player->indexGun]->currentShoot);
    textout_ex(game->buffer, font, munition, SCREEN_W - 60, SCREEN_H - 20, makecol(255, 255, 255), -1);
    sprintf(munition, "%d", game->player->guns[game->player->indexGun]->nbShoot);
    textout_ex(game->buffer, font, "/", SCREEN_W - 40, SCREEN_H - 20, makecol(255, 255, 255), -1);
    textout_ex(game->buffer, font, munition, SCREEN_W - 25, SCREEN_H - 20, makecol(255, 255, 255), -1);
    stretch_sprite(game->buffer, game->munLogo, SCREEN_W - 110, SCREEN_H - 40, 40, 40);
}

BITMAP ***fillGun(BITMAP ***sprite, int nbSpriteShoot, int nbSpriteReload, char filepath[50])
{
    int lenFilepath = strlen(filepath);

    strcat(filepath, "a.bmp\0");
    sprite[0] = malloc(sizeof(BITMAP *) * (nbSpriteShoot + 1));
    sprite[1] = malloc(sizeof(BITMAP *) * (nbSpriteReload + 1));

    for (char c = '1'; c - '1' < nbSpriteShoot; c += 1) {
        filepath[lenFilepath] = c;
        sprite[0][c - '1'] = load_bitmap(filepath, NULL);
        checkPtrNull(sprite[0][c - '1'], "Exit Failure: error when loading gun bitmap\n");
    }
    sprite[0][nbSpriteShoot] = NULL;

    for (int c = 'a'; c - 'a' < nbSpriteReload; c += 1) {
        filepath[lenFilepath] = c;
        sprite[1][c - 'a'] = load_bitmap(filepath, NULL);
        checkPtrNull(sprite[1][c - 'a'], "Exit Failure: error when loading gun bitmap\n");
    }
    sprite[1][nbSpriteReload] = NULL;
    return sprite;
}

gun_t **loadGuns(gun_t **guns)
{
    int indexLoading = 0;
    int nbGuns;
    int nbSpriteReload, nbSprireShoot;
    char filepath[50];
    FILE *fp = fopen("../conf/guns.conf", "r");

    checkPtrNull(fp, "Exit Failure: error at guns.conf opening\n");
    fscanf(fp, "%d", &nbGuns);
    guns = malloc(sizeof(gun_t *) * (nbGuns + 1));
    for (int i = 0; i < nbGuns; i++) {
        textout_ex(screen, font, "3D Engine loading...", SCREEN_W / 2 - 70, SCREEN_H / 2 - 35, makecol(255, 255, 255), -1);
        indexLoading++;
        rect(screen, SCREEN_W / 2 - 105, SCREEN_H / 2 - 15, SCREEN_W / 2 - 100 + 205, SCREEN_H / 2 + 15, makecol(255, 255, 255));
        rectfill(screen, SCREEN_W / 2 - 100, SCREEN_H / 2 - 10, SCREEN_W / 2 - 100 + indexLoading * (200 / (nbGuns * 3)), SCREEN_H / 2 + 10, makecol(255, 255, 255));
        guns[i] = malloc(sizeof(gun_t));
        checkPtrNull(guns[i], "Exit Failure: malloc failed\n");
        guns[i]->sprite = malloc(sizeof(BITMAP **) * 2);
        fscanf(fp, "%s", filepath);
        fscanf(fp, "%d", &nbSprireShoot);
        fscanf(fp, "%d", &nbSpriteReload);
        fscanf(fp, "%d", &guns[i]->dps);
        fscanf(fp, "%d", &guns[i]->nbShoot);
        indexLoading++;
        rectfill(screen, SCREEN_W / 2 - 100, SCREEN_H / 2 - 10, SCREEN_W / 2 - 100 + indexLoading * (200 / (nbGuns * 3)), SCREEN_H / 2 + 10, makecol(255, 255, 255));
        guns[i]->sprite = fillGun(guns[i]->sprite, nbSprireShoot, nbSpriteReload, filepath);
        guns[i]->currentShoot = 0;
        guns[i]->reload = 0;
        guns[i]->shooting = 0;
        guns[i]->offset = 0;
        fscanf(fp, "%s", filepath);
        guns[i]->reloadSound = load_wav(filepath);
        checkPtrNull(guns[i]->reloadSound, "Exit Failure: failed to load shoot sound");
        fscanf(fp, "%s", filepath);
        guns[i]->shootSound = load_wav(filepath);
        checkPtrNull(guns[i]->shootSound, "Exit Failure: failed to load reload sound");
        indexLoading++;
        rectfill(screen, SCREEN_W / 2 - 100, SCREEN_H / 2 - 10, SCREEN_W / 2 - 100 + indexLoading * (200 / (nbGuns * 3)), SCREEN_H / 2 + 10, makecol(255, 255, 255));
    }
    guns[nbGuns] = NULL;
    fclose(fp);

    return guns;
}