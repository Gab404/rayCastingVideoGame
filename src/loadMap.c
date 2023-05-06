#include <stdio.h>
#include <stdlib.h>

void checkPtrNull(void *ptr, char *error);

char **loadMap(char *filepath, int *row, int *col)
{
    char **map;
    FILE *fp = fopen(filepath, "r");

    checkPtrNull(fp, "Exit Failure: error when opening file\n");

    fscanf(fp, "%d", row);
    fscanf(fp, "%d", col);

    map = malloc(sizeof(char *) * (*row + 1));
    checkPtrNull(map, "Exit Failure: malloc failed\n");
    for (int i = 0; i < *row; i++) {
        map[i] = malloc(sizeof(char) * (*col + 1));
        checkPtrNull(map[i], "Exit Failure: malloc failed\n");
        fscanf(fp, "%s", map[i]);
        map[i][*col] = '\0';
    }
    map[*row] = NULL;
    *row -= 1;
    *col -= 1;
    return map;
}