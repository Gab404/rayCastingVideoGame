#include <stdio.h>
#include <stdlib.h>
#include "header.h"

file_t *creerFile(void)
{
    file_t *file = malloc(sizeof(file_t));

    checkPtrNull(file, "Exit Failure: malloc failed");
    file->start = NULL;
    file->end = NULL;

    return file;
}

void enfiler(file_t *file, sommet_t *sommet)
{
    maillon_t *tmpMaillon = file->start;

    if (tmpMaillon == NULL) {
        file->start = malloc(sizeof(maillon_t));
        checkPtrNull(file->start, "Exit Failure: malloc failed");
        file->start->next = NULL;
        file->start->sommet = sommet;
        return;
    }

    while (tmpMaillon->next != NULL)
        tmpMaillon = tmpMaillon->next;    
    tmpMaillon->next = malloc(sizeof(maillon_t));
    checkPtrNull(tmpMaillon->next, "Exit Failure: malloc failed");
    tmpMaillon = tmpMaillon->next;
    tmpMaillon->next = NULL;
    tmpMaillon->sommet = sommet;
}

void defiler(file_t *file, sommet_t *target)
{
    maillon_t *tmpMaillon = file->start;
    maillon_t *lastMaillon;

    if (file->start->sommet == target) {
        file->start = file->start->next;
        free(tmpMaillon);
        return;
    }

    while (tmpMaillon->sommet != target) {
        lastMaillon = tmpMaillon;
        tmpMaillon = tmpMaillon->next;
    }

    lastMaillon->next = tmpMaillon->next;
    
    free(tmpMaillon);
}

int isEmpty(file_t *file)
{
    if (!file->start)
        return 1;
    return 0;
}