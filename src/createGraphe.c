#include <allegro.h>
#include <stdlib.h>
#include <limits.h>
#include "header.h"

void freeSommets(sommet_t ***sommets)
{
    arc_t *tmpArc, *tmpArc2;

    for (int i = 0; sommets[i] != NULL; i++) {
        for (int j = 0; sommets[i][j] != NULL; j++) {
            tmpArc = sommets[i][j]->arc;
            while (tmpArc != NULL) {
                tmpArc2 = tmpArc;
                tmpArc = tmpArc->next;
                free(tmpArc2);
            }
            free(sommets[i][j]);
        }
        free(sommets[i]);
    }
    free(sommets);
}

arc_t *addArc(arc_t *arc, sommet_t *nextNode, double weight)
{
    arc_t *tmpArc = arc;

    if (arc == NULL){
        arc = malloc(sizeof(arc_t));
        checkPtrNull(arc, "Exit Failure: Malloc failed");
        arc->sommet = nextNode;
        arc->next = NULL;
        arc->w = weight;
        return arc;
    }

    while (tmpArc->next != NULL)
        tmpArc = tmpArc->next;

    tmpArc->next = malloc(sizeof(arc_t));
    checkPtrNull(tmpArc->next, "Exit Failure: Malloc failed");
    tmpArc->next->next = NULL;
    tmpArc->next->w = weight;
    tmpArc->next->sommet = nextNode;
    return arc;
}

sommet_t ***createAllSommet(char **map, int col, int row)
{
    sommet_t ***sommets = malloc(sizeof(sommet_t **) * (row + 1));

    checkPtrNull(sommets, "Exit Failure: Malloc failed");
    sommets[row] = NULL;
    for (int i = 0; i < row; i++) {
        sommets[i] = malloc(sizeof(sommet_t *) * (col + 1));
        checkPtrNull(sommets[i], "Exit Failure: Malloc failed");
        for (int j = 0; j < col; j++) {
            sommets[i][j] = malloc(sizeof(sommet_t));
            checkPtrNull(sommets[i][j], "Exit Failure: Malloc failed");
        }
        sommets[i][col] = NULL;
    }

    for (int i = 0; sommets[i] != NULL; i++) {
        for (int j = 0; sommets[i][j] != NULL; j++) {
            sommets[i][j]->arc = NULL;
            sommets[i][j]->color = 0;
            sommets[i][j]->dist = __DBL_MAX__;
            sommets[i][j]->pred = NULL;
            sommets[i][j]->x = j;
            sommets[i][j]->y = i;
            // Proches
            if (map[i][j] == '*') {
                sommets[i][j]->pred = malloc(sizeof(sommet_t));
                checkPtrNull(sommets[i][j]->pred, "Exit Failure: Malloc failed");
                if (map[i][j + 1] == '*')
                    sommets[i][j]->arc = addArc(sommets[i][j]->arc, sommets[i][j + 1], 1);
                if (map[i][j - 1] == '*')
                    sommets[i][j]->arc = addArc(sommets[i][j]->arc, sommets[i][j - 1], 1);
                if (map[i - 1][j] == '*')
                    sommets[i][j]->arc = addArc(sommets[i][j]->arc, sommets[i - 1][j], 1);
                if (map[i + 1][j] == '*')
                    sommets[i][j]->arc = addArc(sommets[i][j]->arc, sommets[i + 1][j], 1);

                // Diagonales
                if (map[i + 1][j + 1] == '*' && (map[i + 1][j] == '*' && map[i][j + 1] == '*'))
                    sommets[i][j]->arc = addArc(sommets[i][j]->arc, sommets[i + 1][j + 1], 1.5);
                if (map[i + 1][j - 1] == '*' && (map[i + 1][j] == '*' && map[i][j - 1] == '*'))
                    sommets[i][j]->arc = addArc(sommets[i][j]->arc, sommets[i + 1][j - 1], 1.5);
                if (map[i - 1][j - 1] == '*' && (map[i - 1][j] == '*' && map[i][j - 1] == '*'))
                    sommets[i][j]->arc = addArc(sommets[i][j]->arc, sommets[i - 1][j - 1], 1.5);
                if (map[i - 1][j + 1] == '*' && (map[i - 1][j] == '*' && map[i][j + 1] == '*'))
                    sommets[i][j]->arc = addArc(sommets[i][j]->arc, sommets[i - 1][j + 1], 1.5);
            }
        }
    }

    return sommets;
}