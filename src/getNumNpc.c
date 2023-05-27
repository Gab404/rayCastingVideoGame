#include <allegro.h>

char detectKey(void)
{   
    for (int i = 27; i < 37; i++)
        if (key[i])
            return i - 26 + 47;
    if (key[KEY_BACKSPACE])
        return 1;
    return 0;
}

int getNumNpc(void)
{
    char tmpString[7];
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    char keyPressed;
    int numNpc;
    int indexPath = 0;
    int keyAlreadyPress = 0;

    while (!key[KEY_ESC]) {
        clear_bitmap(buffer);
        textout_ex(buffer, font, "Number of NPC :", 345, 300, makecol(255, 255, 255), -1);
        keyPressed = detectKey();
        if (keyPressed > 0) {
            if (!keyAlreadyPress)
                keyAlreadyPress = 1;
        } else if (!keyPressed && keyAlreadyPress == 2) {
            keyAlreadyPress = 0;
        }

        if (keyAlreadyPress != 2) {
            if (keyPressed > 1) { // number key pressed
                tmpString[indexPath] = keyPressed;
                if (indexPath + 1 < 5)
                    indexPath++;
            } else if (keyPressed == 1) { // backspace pressed
                tmpString[indexPath] = '\0';
                if (indexPath - 1 >= 0)
                    indexPath--;
                tmpString[indexPath] = '\0';
            }
        }

        rect(buffer, 375, 345, 423, 365, makecol(255, 255, 255));
        textout_ex(buffer, font, tmpString, 380, 350, makecol(255, 255, 255), -1);

        numNpc = 0;
        for (int i = 0; i < indexPath; i++) {
            numNpc *= 10;
            numNpc += '0' - tmpString[i];
        }

        if (indexPath != 0 && key[KEY_ENTER] && numNpc != 0 && numNpc < 500) {
                destroy_bitmap(buffer);
                return -1 * numNpc;
        }
        if (keyAlreadyPress)
            keyAlreadyPress = 2;

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    destroy_bitmap(buffer);
    allegro_exit();
    exit(EXIT_SUCCESS);
    return 0;
}