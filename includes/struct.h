#ifndef STRUCT_H
    #define STRUCT_H

#include <stdbool.h>
#include <allegro.h>
#include <time.h>
#include "graphe.h"

typedef struct gun_s {
    BITMAP ***sprite;
    SAMPLE *shootSound;
    SAMPLE *reloadSound;
    int dps;
    int nbShoot;
    int currentShoot;
    int reload;
    int shooting;
    int offset;
    int typeOffset;
} gun_t;

typedef struct player_s {
    gun_t **guns;
    int indexGun;
    int indexSpriteGun;
    int speedAnim;
    int currentAnim;
    float angle;
    int screenX;
    int screenY;
    int mapX;
    int mapY;
    int life;
    float sensitivity;
    bool isWalked;
    int posMapX;
    int posMapY;
    float posxCase;
    float posyCase;
    int screenDist;
    int shooting;
    time_t timeHeal;
    time_t timeAttackedHeal;
    int score;
    long clockStep;
} player_t;

typedef struct npc_s {
    int life;
    int points;
    time_t tempoAttack;
    int maxLife;
    int speed;
    int dps;
    int attacking;
    int walking;
    int indexSprite;
    clock_t tempoAnim;
    int IndexAnim;
    int typeSprite;
    int x;
    int y;
    int screenX;
    int screenY;
    int dead;
    int playerSeen;
    int agro;
    long clockStep;
} npc_t;

typedef struct game3d_s {
    int row;
    int col;
    int oldMouseX;
    int indexSaveData;
    sommet_t ***sommets;
    BITMAP *buffer;
    BITMAP *sky;
    BITMAP *pauseBanner;
    BITMAP **texture;
    BITMAP ****oppsAnim;
    BITMAP *munLogo;
    player_t *player;
    npc_t *opps;
    int *allDist;
    int *allPosTexture;
    int *allTypeWall;
    int *allPos;
    int *badPosX;
    int *badPosY;
    char **map;
    int skyX;
    int skyX2;
    int midScreenW;
    int midScreenH;
    int volume;
    int nbNpc;
    bool centerCursor
}game3d_t;

#endif /*STRUCT_H*/