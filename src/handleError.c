#include <allegro.h>
#include <stdio.h>

void checkPtrNull(void *ptr, char *error)
{
    if (ptr == NULL) {
        allegro_exit();
        printf("%s", error);
        exit(EXIT_FAILURE);
    }
}