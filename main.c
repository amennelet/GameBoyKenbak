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

    UINT8 currentScreen = KENBAK_SCREEN;
    UINT8 changeScreen = CHANGE_SCREEN;

    set_bkg_data(0, 110, BackgroundTiles);
    set_sprite_data(0, 6, SpriteTiles);

    UINT8 previousKeys = 0;
    UINT8 frame = 0;
    while (1)
    {
        frame++;

        // manage input
        UINT8 keys = joypad();
        if (keys > 0 && keys != previousKeys)
        {
            if (manageUserInput(currentScreen, keys, &kenbakMachineState) != currentScreen)
                changeScreen = CHANGE_SCREEN;
        }
        if (keys == 0 && keys != previousKeys)
        {
            releaseButtons(&kenbakMachineState);
        }
        previousKeys = keys;

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

void releaseButtons(struct KenbakMachineState *kenbakMachineState)
{
    releaseKenbakButtons(kenbakMachineState);
}

UINT8 manageUserInput(UINT8 currentScreen, UINT8 keys, struct KenbakMachineState *kenbakMachineState)
{
    if (currentScreen == KENBAK_SCREEN)
    {
        return manageKenbakScreenUserInput(keys, kenbakMachineState);
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
    return currentScreen;
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