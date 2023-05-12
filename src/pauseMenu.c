#include <allegro.h>
#include "header.h"

void changeVolume(game3d_t *game)
{
    if (key[KEY_LEFT] && game->volume > 0)
        game->volume--;
    else if (key[KEY_RIGHT] && game->volume < 245)
        game->volume++;
}

void changeSensibility(game3d_t *game)
{
    if (key[KEY_DOWN] && game->player->sensitivity > 0.0004)
        game->player->sensitivity -= 0.0001;
    else if (key[KEY_UP] && game->player->sensitivity < 0.0475)
        game->player->sensitivity += 0.0001;    
}

void pauseMenu(game3d_t *game)
{
    BITMAP *tmpBuffer;

    if (key[KEY_H]) {
        tmpBuffer = create_bitmap(SCREEN_W, SCREEN_H);
        
        while (!key[KEY_A]) {
            clear_bitmap(tmpBuffer);
            changeSensibility(game);
            changeVolume(game);
            blit(game->buffer, tmpBuffer, 0, 0, 0, 0, game->buffer->w, game->buffer->h);
            textout_ex(tmpBuffer, font, "Sensitivity", 200, 300, makecol(255, 255, 255), -1);
            rectfill(tmpBuffer, 130, 370, 330, 390, makecol(0, 0, 0));
            rectfill(tmpBuffer, 135, 375, 135 + (game->player->sensitivity * 200) / 0.05, 385, makecol(255, 0, 0));
            textout_ex(tmpBuffer, font, "Volume", 520, 300, makecol(255, 255, 255), -1);
            rectfill(tmpBuffer, 450, 370, 650, 390, makecol(0, 0, 0));
            rectfill(tmpBuffer, 455, 375, 455 + (game->volume * 200) / 255, 385, makecol(255, 0, 0));
            stretch_sprite(tmpBuffer, game->pauseBanner, 300, 130, 200, 50);
            blit(tmpBuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
        destroy_bitmap(tmpBuffer);
    }
}