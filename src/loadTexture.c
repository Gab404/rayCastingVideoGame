#include <allegro.h>
#include "header.h"

BITMAP **loadTexture(char *filepath)
{
    BITMAP *tmpTexture = load_bitmap(filepath, NULL);
    BITMAP **texture;
    int nbTexture;

    checkPtrNull(tmpTexture, "Exit Failure: error at texture creation\n");
    nbTexture = tmpTexture->h / 64;
    texture = malloc(sizeof(BITMAP *) * (nbTexture + 1));

    for (int i = 0; i < nbTexture; i++) {
        texture[i] = create_bitmap(64, 64);
        stretch_blit(tmpTexture, texture[i], 0, i * 64, 64, 64, 0, 0, 64, 64);
    }
    texture[nbTexture] = NULL;

    return texture;
}