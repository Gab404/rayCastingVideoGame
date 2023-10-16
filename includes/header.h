#ifndef HEADER_H
    #define HEADER_H

#include "struct.h"

#define PI 3.14159265358979323846
#define SIZE 64

BITMAP **loadTexture(char *filepath);

void myDijkstra(game3d_t *game, npc_t *opps, double *xOpps, double *yOpps);

void freeSommets(sommet_t ***sommets);
sommet_t ***createAllSommet(char **map, int col, int row);

file_t *creerFile(void);
void enfiler(file_t *file, sommet_t *sommet);
void defiler(file_t *file, sommet_t *target);
int isEmpty(file_t *file);

int getNumNpc(char **map);

void pauseMenu(game3d_t *game);

void generateSpawnCoord(game3d_t *game, int *x, int *y);

void animOpps(npc_t *opps, BITMAP ****anim);
void loadOpps(game3d_t *game);
void calcSprite(game3d_t *game, int index);

void displayTarget(game3d_t *game);
void displayMiniMap(game3d_t *game);
void displaySky(game3d_t *game);
void display3D(game3d_t *game);
void displayLife(game3d_t *game);
void displayScore(game3d_t *game);
void displayFps(int *fps, char *str, BITMAP *buffer, time_t *fpsClock);

game3d_t *createGame(void);
void gameLoop(void);

void quickSort(int arr[], int label1[], int label2[], int label3[], int left, int right);

gun_t **loadGuns(gun_t **guns);
void displayGun(game3d_t *game);

void movePlayer(game3d_t *game);
player_t *createPlayer(void);
void playerHeal(game3d_t *game);

void raycasting(game3d_t *game);

char **loadMap(char *filepath, int *row, int *col);

void checkPtrNull(void *ptr, char *error);

void freeArray(char **array);
void freePlayer(player_t *player);
void freeGame(game3d_t *game);

#endif /*HEADER_H*/