#include <gb.h>
#include "main.h"
#include "asset\BackgroundTiles.h"
#include "asset\SpriteTiles.h"
#include "kenbakscreen.h"

void main(void)
{
    UINT8 currentScreen = KENBAK_SCREEN;
    UINT8 changeScreen = CHANGE_SCREEN;

    set_bkg_data(0, 110, BackgroundTiles);
    set_sprite_data(0, 6, SpriteTiles);

    // manage input
    // update machine state
    updateScreen(currentScreen, changeScreen);

    changeScreen = CURRENT_SCREEN;
}

void updateScreen(UINT8 currentScreen, UINT8 changeScreen)
{
    if (currentScreen == KENBAK_SCREEN)
    {
        UpdateKenbakScreen(changeScreen);
    }
    else if (currentScreen == MEMORY_SCREEN)
    {
        //UpdateMemoryScreen(changeScreen);
    }
    else if (currentScreen == FILE_SCREEN)
    {
        //UpdateFileScreen(changeScreen);
    }
    else if (currentScreen == MANUAL_SCREEN)
    {
        //UpdateManualScreen(changeScreen);
    }
}