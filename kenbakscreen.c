#include <gb.h>
#include "main.h"
#include "kenbakscreen.h"
#include "Asset\KenbakBackgroundMap.h"
#include "Asset\KenbakMenuMap.h"

void InitKenbakSprites()
{
    sprites[0].spriteId = 0;
    sprites[0].spriteIndex = LIGHT_ON_SPRITE_INDEX;
    sprites[0].x = 12;
    sprites[0].y = 3;
    sprites[0].show = SHOW_SPRITE;

    sprites[1].spriteId = 1;
    sprites[1].spriteIndex = SWITCH_ON_SPRITE_INDEX;
    sprites[1].x = 16;
    sprites[1].y = 4;
    sprites[1].show = SHOW_SPRITE;

    sprites[2].spriteId = 2;
    sprites[2].spriteIndex = BUTTON_BLACK_SPRITE_INDEX;
    sprites[2].x = 3;
    sprites[2].y = 4;
    sprites[2].show = SHOW_SPRITE;

    sprites[3].spriteId = 3;
    sprites[3].spriteIndex = BUTTON_WHITE_SPRITE_INDEX;
    sprites[3].x = 8;
    sprites[3].y = 4;
    sprites[3].show = SHOW_SPRITE;

    sprites[4].spriteId = 4;
    sprites[4].spriteIndex = CURSOR_SPRITE_INDEX;
    sprites[4].x = 4;
    sprites[4].y = 4;
    sprites[4].show = SHOW_SPRITE;

    initSpriteDisplay(&(sprites[0]));
    initSpriteDisplay(&(sprites[1]));
    initSpriteDisplay(&(sprites[2]));
    initSpriteDisplay(&(sprites[3]));
    initSpriteDisplay(&(sprites[4]));
}

void UpdateKenbakScreen(UINT8 changeScreen)
{
    if (changeScreen == CHANGE_SCREEN)
    {
        HIDE_BKG;
        HIDE_WIN;
        HIDE_SPRITES;

        set_bkg_tiles(0, 0, KenbakBackgroundMapWidth, KenbakBackgroundMapHeight, KenbakBackgroundMap);
        set_win_tiles(0, 0, KenbakMenuMapWidth, KenbakMenuMapHeight, KenbakMenuMap);
        move_win(7, 136);
        InitKenbakSprites();

        SHOW_BKG;
        SHOW_WIN;
        SHOW_SPRITES;
    }
}