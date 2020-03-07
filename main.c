#include <gb.h>
#include "main.h"
#include "globaldefine.h"
#include "asset\BackgroundTiles.h"
#include "asset\SpriteTiles.h"
#include "kenbakscreen.h"

void main(void)
{
    struct KenbakMachineState kenbakMachineState;
    InitKenbakMachineState(&kenbakMachineState);
    LoadKenbakMachineMemory(&kenbakMachineState, k200ProgramMemory);
    SetKenbakMachinePower(&kenbakMachineState, 1);
    SetKenbakMachineRun(&kenbakMachineState, 1);

    UINT8 currentScreen = KENBAK_SCREEN;
    UINT8 changeScreen = CHANGE_SCREEN;

    set_bkg_data(0, 110, BackgroundTiles);
    set_sprite_data(0, 6, SpriteTiles);

    UINT8 frame = 0;
    while (1)
    {
        frame++;

        // manage input
        // update machine state
        if (frame == MACHINE_SPEED)
        {
            DoKenbakMachineNextInstruction(&kenbakMachineState);
            frame = 0;
        }
        updateScreen(currentScreen, changeScreen, &kenbakMachineState);
        changeScreen = CURRENT_SCREEN;

        // Wait for v-blank (screen refresh)
        wait_vbl_done();
    }
}

void updateScreen(UINT8 currentScreen, UINT8 changeScreen, struct KenbakMachineState *kenbakMachineState)
{
    if (currentScreen == KENBAK_SCREEN)
    {
        UpdateKenbakScreen(changeScreen, kenbakMachineState);
    }
    if (currentScreen == MEMORY_SCREEN)
    {
        //UpdateMemoryScreen(changeScreen);
    }
    if (currentScreen == FILE_SCREEN)
    {
        //UpdateFileScreen(changeScreen);
    }
    if (currentScreen == MANUAL_SCREEN)
    {
        //UpdateManualScreen(changeScreen);
    }
}