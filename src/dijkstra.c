#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include "header.h"

void initSommet(sommet_t ***sommets)
{
    for (int i = 0; sommets[i] != NULL; i++)
        for (int j = 0; sommets[i][j] != NULL; j++) {
            sommets[i][j]->color = 0;
            sommets[i][j]->dist = __DBL_MAX__;
            sommets[i][j]->pred = NULL;
        }
}

int allVisited(file_t *file, sommet_t *sommetFin)
{
    if (sommetFin->color)
        return 1;

    if (isEmpty(file)) {
        printf("empty\n");
        return 1;
    }

    return 0;
}

sommet_t *sortDist(file_t *file, sommet_t *currNode, double *currDist)
{
    double dist = __DBL_MAX__;
    maillon_t *tmpMaillon = file->start;

    while (tmpMaillon != NULL) {
        if (tmpMaillon->sommet->dist < dist) {
            currNode = tmpMaillon->sommet;
            dist = tmpMaillon->sommet->dist;
        }
        tmpMaillon = tmpMaillon->next;
    }

    *currDist = currNode->dist;
    return currNode;
}

void checkNeighbor(sommet_t *currNode, double currDist, file_t *file)
{
    arc_t *tmpArc = currNode->arc;
    maillon_t *tmpMaillon;
    bool alreadyEnfiler = false;

    while (tmpArc != NULL) {
        if (!tmpArc->sommet->color && currDist + tmpArc->w < tmpArc->sommet->dist) {
            tmpArc->sommet->dist = currDist + tmpArc->w;
            tmpArc->sommet->pred = currNode;
            tmpMaillon = file->start;
            while (tmpMaillon != NULL) {
                if (tmpMaillon->sommet == tmpArc->sommet) {
                    alreadyEnfiler = true;
                    break;
                }
                tmpMaillon = tmpMaillon->next;
            }
            if (!alreadyEnfiler)
                enfiler(file, tmpArc->sommet);
        }
        tmpArc = tmpArc->next;
        alreadyEnfiler = false;
    }
}

void getFirstStep(BITMAP *buffer, sommet_t *endSommet, sommet_t *startSommet, double *x, double *y, npc_t *opps, int playerX)
{
    sommet_t *nextSommet = endSommet;
    double angle;

    if (nextSommet->pred == NULL)
        printf("NULL\n");
    while (nextSommet->pred->dist != 0)
        nextSommet = nextSommet->pred;

    rectfill(buffer, nextSommet->x * 7, nextSommet->y * 7, nextSommet->x * 7 + 7, nextSommet->y * 7 + 7, makecol(213,6, 255));
    if (nextSommet->y < startSommet->y) {
        if (nextSommet->x < startSommet->x) // diagonale en haut à gauche
            angle = (3 * PI) / 4;
        else if (nextSommet->x == startSommet->x)
            angle = PI / 2;
        else
            angle = PI / 4;
    } else if (nextSommet->y > startSommet->y) {
        if (nextSommet->x < startSommet->x)
            angle = (5 * PI) / 4;
        else if (nextSommet->x == startSommet->x)
            angle = (3 * PI) / 2;
        else
            angle = (7 * PI) / 4;
    } else if (nextSommet->x < startSommet->x)
        angle = PI;
    else
        angle = 0.00;

    if (opps->x <= playerX) {
        *x = cos(angle) * opps->speed;
        *y = -sin(angle) * opps->speed;
    } else {
        *x = opps->speed * cos(angle);
        *y = opps->speed * sin(angle);
    }
}

void myDijkstra(game3d_t *game, npc_t *opps, double *xOpps, double *yOpps)
{
    int xDep = opps->x / 64, yDep = opps->y / 64;
    int xFin = game->player->posMapX, yFin = game->player->posMapY;
    sommet_t *currNode = game->sommets[yDep][xDep];
    file_t *file = creerFile();
    double currDist = 0;

    if (xDep == xFin && yDep == yFin) {
        free(file);
        return;
    }

    initSommet(game->sommets);
    currNode->dist = 0;
    enfiler(file, game->sommets[yDep][xDep]);
    while (!allVisited(file, game->sommets[yFin][xFin])) {
        defiler(file, currNode);
        currNode->color = 1; // Marquage du sommet courant
        checkNeighbor(currNode, currDist, file); // Parcours de chaque sommets liés au sommet courant
        currNode = sortDist(file, currNode, &currDist); // Algo de trie pour choisir le sommet avec le chemin le plus court
    }

    getFirstStep(game->buffer, game->sommets[yFin][xFin], game->sommets[yDep][xDep], xOpps, yOpps, opps, game->player->screenX);
    free(file);
}