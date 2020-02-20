#include <gb.h>
#include "main.h"
#include "kenbakscreen.h"
#include "Asset\KenbakBackgroundMap.h"
#include "Asset\KenbakMenuMap.h"

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

        SHOW_BKG;
        SHOW_WIN;
        SHOW_SPRITES;
    }
}