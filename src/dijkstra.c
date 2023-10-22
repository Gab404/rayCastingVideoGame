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

    while (nextSommet->pred->dist != 0)
        nextSommet = nextSommet->pred;

    if (nextSommet->y < startSommet->y) {
        if (nextSommet->x < startSommet->x) // diagonale en haut à gauche
            angle = -0.75;
        else if (nextSommet->x == startSommet->x) {
            if (playerX < opps->x)
                angle = -1.5;
            else
                angle = 1.5;
        } else
            angle = 0.75;
    } else if (nextSommet->y > startSommet->y) {
        if (nextSommet->x < startSommet->x)
            angle = 0.75;
        else if (nextSommet->x == startSommet->x) {
            if (playerX > opps->x)
                angle = -1.5;
            else
                angle = 1.5;
        } else
            angle = -0.75;
    } else if (nextSommet->x < startSommet->x)
        angle = 0.00;
    else
        angle = 0.00;

    if (opps->x < playerX) {
        *x = cos(angle) * opps->speed;
        *y = -sin(angle) * opps->speed;
    } else {
        *x = -opps->speed * cos(angle);
        *y = opps->speed * sin(angle);
    }
}

void myDijkstra(game3d_t *game, npc_t *opps, double *xOpps, double *yOpps)
{
    int xDep = opps->x / 64, yDep = opps->y / 64;
    int xFin = game->player->posMapX, yFin = game->player->posMapY;
    sommet_t *currNode = game->sommets[yDep][xDep];
    file_t *file = creerFile();
    double currDist = 0.00;

    if ((xDep == xFin && yDep == yFin) || (game->map[yDep][xDep] != '*')) {
        free(file);
        return;
    }

    initSommet(game->sommets);
    currNode->dist = currDist;
    enfiler(file, currNode);
    while (!allVisited(file, game->sommets[yFin][xFin])) {
        currNode->color = 1; // Marquage du sommet courant
        defiler(file, currNode);
        checkNeighbor(currNode, currDist, file); // Parcours de chaque sommets liés au sommet courant
        currNode = sortDist(file, currNode, &currDist); // Algo de trie pour choisir le sommet avec le chemin le plus court
    }

    getFirstStep(game->buffer, game->sommets[yFin][xFin], game->sommets[yDep][xDep], xOpps, yOpps, opps, game->player->screenX);
    free(file);
}