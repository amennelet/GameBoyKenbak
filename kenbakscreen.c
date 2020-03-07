#include <gb.h>
#include "globaldefine.h"
#include "kenbakscreen.h"
#include "Asset\KenbakBackgroundMap.h"
#include "Asset\KenbakMenuMap.h"
#include "spritehelper.h"
#include "kenbakmachine.h"

struct SpriteDisplay ledDisplay[8];
struct SpriteDisplay ledPower[1];
struct SpriteDisplay ledAddress[1];
struct SpriteDisplay ledClear[1];
struct SpriteDisplay ledLock[1];
struct SpriteDisplay ledMemory[1];
struct SpriteDisplay ledRun[1];

struct SpriteDisplay buttonDisplay[8];
struct SpriteDisplay buttonPower[1];
struct SpriteDisplay buttonAddressDisplay[1];
struct SpriteDisplay buttonAddressSet[1];
struct SpriteDisplay buttonClear[1];
struct SpriteDisplay buttonLock[1];
struct SpriteDisplay buttonMemoryRead[1];
struct SpriteDisplay buttonMemoryStore[1];
struct SpriteDisplay buttonRun[1];
struct SpriteDisplay cursor[1];

struct CusorPosition cusorPositionButtonDisplay[8];
struct CusorPosition cusorPositionButtonPower[1];
struct CusorPosition cusorPositionButtonAddressDisplay[1];
struct CusorPosition cusorPositionButtonAddressSet[1];
struct CusorPosition cusorPositionButtonMemoryRead[1];
struct CusorPosition cusorPositionButtonMemoryStore[1];
struct CusorPosition cusorPositionButtonClear[1];
struct CusorPosition cusorPositionButtonLock[1];
struct CusorPosition cusorPositionButtonRun[1];

struct CusorPosition *currentCursorPosition;

void InitKenbakSprites()
{
    UINT8 show = SHOW_SPRITE;
    UINT8 spriteId = 0;

    cursor[0].spriteId = spriteId++;
    cursor[0].spriteIndex = CURSOR_SPRITE_INDEX;
    cursor[0].x = currentCursorPosition->x;
    cursor[0].y = currentCursorPosition->y;
    cursor[0].show = show;
    initCusorDisplay(cursor);

    UINT8 displayX = 12;
    for (UINT8 cptLedDisplay = 0; cptLedDisplay < 8; cptLedDisplay++)
    {
        ledDisplay[cptLedDisplay].spriteId = spriteId;
        ledDisplay[cptLedDisplay].spriteIndex = LIGHT_ON_SPRITE_INDEX;
        ledDisplay[cptLedDisplay].x = displayX;
        ledDisplay[cptLedDisplay].y = 3;
        ledDisplay[cptLedDisplay].show = show;

        spriteId++;
        displayX--;
        if (cptLedDisplay == 2 || cptLedDisplay == 5)
            displayX--;
    }
    initSpriteDisplay(ledDisplay, 8);

    ledPower[0].spriteId = spriteId++;
    ledPower[0].spriteIndex = LIGHT_ON_SPRITE_INDEX;
    ledPower[0].x = 16;
    ledPower[0].y = 3;
    ledPower[0].show = show;
    initSpriteDisplay(ledPower, 1);

    ledAddress[0].spriteId = spriteId++;
    ledAddress[0].spriteIndex = LIGHT_ON_SPRITE_INDEX;
    ledAddress[0].x = 6;
    ledAddress[0].y = 7;
    ledAddress[0].show = show;
    initSpriteDisplay(ledAddress, 1);

    ledClear[0].spriteId = spriteId++;
    ledClear[0].spriteIndex = LIGHT_ON_SPRITE_INDEX;
    ledClear[0].x = 12;
    ledClear[0].y = 7;
    ledClear[0].show = show;
    initSpriteDisplay(ledClear, 1);

    ledLock[0].spriteId = spriteId++;
    ledLock[0].spriteIndex = LIGHT_ON_SPRITE_INDEX;
    ledLock[0].x = 16;
    ledLock[0].y = 7;
    ledLock[0].show = show;
    initSpriteDisplay(ledLock, 1);

    ledMemory[0].spriteId = spriteId++;
    ledMemory[0].spriteIndex = LIGHT_ON_SPRITE_INDEX;
    ledMemory[0].x = 6;
    ledMemory[0].y = 11;
    ledMemory[0].show = show;
    initSpriteDisplay(ledMemory, 1);

    ledRun[0].spriteId = spriteId++;
    ledRun[0].spriteIndex = LIGHT_ON_SPRITE_INDEX;
    ledRun[0].x = 16;
    ledRun[0].y = 11;
    ledRun[0].show = show;
    initSpriteDisplay(ledRun, 1);

    UINT8 buttonSpriteIndex = BUTTON_WHITE_SPRITE_INDEX;
    displayX = 12;
    for (UINT8 cptButtonDisplay = 0; cptButtonDisplay < 8; cptButtonDisplay++)
    {
        buttonDisplay[cptButtonDisplay].spriteId = spriteId;
        buttonDisplay[cptButtonDisplay].spriteIndex = buttonSpriteIndex;
        buttonDisplay[cptButtonDisplay].x = displayX;
        buttonDisplay[cptButtonDisplay].y = 4;
        buttonDisplay[cptButtonDisplay].show = show;

        spriteId++;
        displayX--;
        if (cptButtonDisplay == 2 || cptButtonDisplay == 5)
            displayX--;
        if (cptButtonDisplay == 3)
            buttonSpriteIndex = BUTTON_BLACK_SPRITE_INDEX;
    }
    initSpriteDisplay(buttonDisplay, 8);

    buttonPower[0].spriteId = spriteId++;
    buttonPower[0].spriteIndex = SWITCH_ON_SPRITE_INDEX;
    buttonPower[0].x = 16;
    buttonPower[0].y = 4;
    buttonPower[0].show = show;
    initSpriteDisplay(buttonPower, 1);

    buttonAddressDisplay[0].spriteId = spriteId++;
    buttonAddressDisplay[0].spriteIndex = BUTTON_WHITE_SPRITE_INDEX;
    buttonAddressDisplay[0].x = 4;
    buttonAddressDisplay[0].y = 8;
    buttonAddressDisplay[0].show = show;
    initSpriteDisplay(buttonAddressDisplay, 1);

    buttonAddressSet[0].spriteId = spriteId++;
    buttonAddressSet[0].spriteIndex = BUTTON_BLACK_SPRITE_INDEX;
    buttonAddressSet[0].x = 8;
    buttonAddressSet[0].y = 8;
    buttonAddressSet[0].show = show;
    initSpriteDisplay(buttonAddressSet, 1);

    buttonClear[0].spriteId = spriteId++;
    buttonClear[0].spriteIndex = BUTTON_BLACK_SPRITE_INDEX;
    buttonClear[0].x = 12;
    buttonClear[0].y = 8;
    buttonClear[0].show = show;
    initSpriteDisplay(buttonClear, 1);

    buttonLock[0].spriteId = spriteId++;
    buttonLock[0].spriteIndex = SWITCH_ON_SPRITE_INDEX;
    buttonLock[0].x = 16;
    buttonLock[0].y = 8;
    buttonLock[0].show = show;
    initSpriteDisplay(buttonLock, 1);

    buttonMemoryRead[0].spriteId = spriteId++;
    buttonMemoryRead[0].spriteIndex = BUTTON_WHITE_SPRITE_INDEX;
    buttonMemoryRead[0].x = 4;
    buttonMemoryRead[0].y = 12;
    buttonMemoryRead[0].show = show;
    initSpriteDisplay(buttonMemoryRead, 1);

    buttonMemoryStore[0].spriteId = spriteId++;
    buttonMemoryStore[0].spriteIndex = BUTTON_BLACK_SPRITE_INDEX;
    buttonMemoryStore[0].x = 8;
    buttonMemoryStore[0].y = 12;
    buttonMemoryStore[0].show = show;
    initSpriteDisplay(buttonMemoryStore, 1);

    buttonRun[0].spriteId = spriteId++;
    buttonRun[0].spriteIndex = BUTTON_WHITE_SPRITE_INDEX;
    buttonRun[0].x = 16;
    buttonRun[0].y = 12;
    buttonRun[0].show = show;
    initSpriteDisplay(buttonRun, 1);
}

void InitCursor()
{
    UINT8 displayX = 12;
    for (UINT8 cptButtonDisplay = 0; cptButtonDisplay < 8; cptButtonDisplay++)
    {
        cusorPositionButtonDisplay[cptButtonDisplay].x = displayX;
        cusorPositionButtonDisplay[cptButtonDisplay].y = 4;
        cusorPositionButtonDisplay[cptButtonDisplay].action = BIT_ACTION;
        cusorPositionButtonDisplay[cptButtonDisplay].actionIndex = cptButtonDisplay;

        cusorPositionButtonDisplay[cptButtonDisplay].left = 0;
        if (cptButtonDisplay < 7)
            cusorPositionButtonDisplay[cptButtonDisplay].left = &cusorPositionButtonDisplay[cptButtonDisplay + 1];
        cusorPositionButtonDisplay[cptButtonDisplay].right = cusorPositionButtonPower;
        if (cptButtonDisplay > 0)
            cusorPositionButtonDisplay[cptButtonDisplay].right = &cusorPositionButtonDisplay[cptButtonDisplay - 1];
        cusorPositionButtonDisplay[cptButtonDisplay].up = 0;
        if (cptButtonDisplay < 3)
            cusorPositionButtonDisplay[cptButtonDisplay].down = cusorPositionButtonClear;
        else if (cptButtonDisplay < 6)
            cusorPositionButtonDisplay[cptButtonDisplay].down = cusorPositionButtonAddressSet;
        else
            cusorPositionButtonDisplay[cptButtonDisplay].down = cusorPositionButtonAddressDisplay;

        displayX--;
        if (cptButtonDisplay == 2 || cptButtonDisplay == 5)
            displayX--;
    }

    cusorPositionButtonPower[0].x = 16;
    cusorPositionButtonPower[0].y = 4;
    cusorPositionButtonPower[0].action = POWER_ACTION;
    cusorPositionButtonPower[0].left = &cusorPositionButtonDisplay[0];
    cusorPositionButtonPower[0].right = 0;
    cusorPositionButtonPower[0].up = 0;
    cusorPositionButtonPower[0].down = cusorPositionButtonLock;

    cusorPositionButtonAddressDisplay[0].x = 4;
    cusorPositionButtonAddressDisplay[0].y = 8;
    cusorPositionButtonAddressDisplay[0].action = DISPLAY_ADDRESS_ACTION;
    cusorPositionButtonAddressDisplay[0].left = 0;
    cusorPositionButtonAddressDisplay[0].right = cusorPositionButtonAddressSet;
    cusorPositionButtonAddressDisplay[0].up = &cusorPositionButtonDisplay[6];
    cusorPositionButtonAddressDisplay[0].down = cusorPositionButtonMemoryRead;

    cusorPositionButtonAddressSet[0].x = 8;
    cusorPositionButtonAddressSet[0].y = 8;
    cusorPositionButtonAddressSet[0].action = SET_ADDRESS_ACTION;
    cusorPositionButtonAddressSet[0].left = cusorPositionButtonAddressDisplay;
    cusorPositionButtonAddressSet[0].right = cusorPositionButtonClear;
    cusorPositionButtonAddressSet[0].up = &cusorPositionButtonDisplay[3];
    cusorPositionButtonAddressSet[0].down = cusorPositionButtonMemoryStore;

    cusorPositionButtonMemoryRead[0].x = 4;
    cusorPositionButtonMemoryRead[0].y = 12;
    cusorPositionButtonMemoryRead[0].action = READ_MEMORY_ACTION;
    cusorPositionButtonMemoryRead[0].left = 0;
    cusorPositionButtonMemoryRead[0].right = cusorPositionButtonMemoryStore;
    cusorPositionButtonMemoryRead[0].up = cusorPositionButtonAddressDisplay;
    cusorPositionButtonMemoryRead[0].down = 0;

    cusorPositionButtonMemoryStore[0].x = 8;
    cusorPositionButtonMemoryStore[0].y = 12;
    cusorPositionButtonMemoryStore[0].action = STORE_MEMORY_ACTION;
    cusorPositionButtonMemoryStore[0].left = cusorPositionButtonMemoryRead;
    cusorPositionButtonMemoryStore[0].right = cusorPositionButtonRun;
    cusorPositionButtonMemoryStore[0].up = cusorPositionButtonAddressSet;
    cusorPositionButtonMemoryStore[0].down = 0;

    cusorPositionButtonClear[0].x = 12;
    cusorPositionButtonClear[0].y = 8;
    cusorPositionButtonClear[0].action = CLEAR_ACTION;
    cusorPositionButtonClear[0].left = cusorPositionButtonAddressSet;
    cusorPositionButtonClear[0].right = cusorPositionButtonLock;
    cusorPositionButtonClear[0].up = &cusorPositionButtonDisplay[0];
    cusorPositionButtonClear[0].down = cusorPositionButtonRun;

    cusorPositionButtonLock[0].x = 16;
    cusorPositionButtonLock[0].y = 8;
    cusorPositionButtonLock[0].action = LOCK_ACTION;
    cusorPositionButtonLock[0].left = cusorPositionButtonClear;
    cusorPositionButtonLock[0].right = 0;
    cusorPositionButtonLock[0].up = cusorPositionButtonPower;
    cusorPositionButtonLock[0].down = cusorPositionButtonRun;

    cusorPositionButtonRun[0].x = 16;
    cusorPositionButtonRun[0].y = 12;
    cusorPositionButtonRun[0].action = RUN_ACTION;
    cusorPositionButtonRun[0].left = cusorPositionButtonMemoryStore;
    cusorPositionButtonRun[0].right = 0;
    cusorPositionButtonRun[0].up = cusorPositionButtonLock;
    cusorPositionButtonRun[0].down = 0;

    currentCursorPosition = &cusorPositionButtonDisplay[7];
}

void UpdateKenbakScreen(UINT8 changeScreen, struct KenbakMachineState *kenbakMachineState)
{
    if (changeScreen == CHANGE_SCREEN)
    {
        HIDE_BKG;
        HIDE_WIN;
        HIDE_SPRITES;

        set_bkg_tiles(0, 0, KenbakBackgroundMapWidth, KenbakBackgroundMapHeight, KenbakBackgroundMap);
        set_win_tiles(0, 0, KenbakMenuMapWidth, KenbakMenuMapHeight, KenbakMenuMap);
        move_win(7, 136);
        InitCursor();
        InitKenbakSprites();

        SHOW_BKG;
        SHOW_WIN;
        SHOW_SPRITES;
    }

    for (UINT8 cptLedDisplay = 0; cptLedDisplay < 8; cptLedDisplay++)
    {
        SwitchSprite(kenbakMachineState->outputValue & (0x01 << cptLedDisplay), &(ledDisplay[cptLedDisplay]));
    }
    SwitchSprite(kenbakMachineState->powerSignal, &(ledPower[0]));
    SwitchSprite(kenbakMachineState->addressSignal, &(ledAddress[0]));
    SwitchSprite(kenbakMachineState->clearSignal, &(ledClear[0]));
    SwitchSprite(kenbakMachineState->lockSignal, &(ledLock[0]));
    SwitchSprite(kenbakMachineState->memorySignal, &(ledMemory[0]));
    SwitchSprite(kenbakMachineState->runSignal, &(ledRun[0]));

    for (UINT8 cptButtonDisplay = 0; cptButtonDisplay < 8; cptButtonDisplay++)
    {
        SwitchSprite(kenbakMachineState->outputButton & (0x01 << cptButtonDisplay), &(buttonDisplay[cptButtonDisplay]));
    }
    SwitchSprite(kenbakMachineState->powerButton, &(buttonPower[0]));
    SwitchSprite(kenbakMachineState->addressDisplayButton, &(buttonAddressDisplay[0]));
    SwitchSprite(kenbakMachineState->addressSetButton, &(buttonAddressSet[0]));
    SwitchSprite(kenbakMachineState->clearButton, &(buttonClear[0]));
    SwitchSprite(kenbakMachineState->lockButton, &(buttonLock[0]));
    SwitchSprite(kenbakMachineState->memoryReadButton, &(buttonMemoryRead[0]));
    SwitchSprite(kenbakMachineState->memoryStoreButton, &(buttonMemoryStore[0]));
    SwitchSprite(kenbakMachineState->runButton, &(buttonRun[0]));

    MoveSprite(currentCursorPosition->x, currentCursorPosition->y, &cursor[0]);
}

UINT8 manageKenbakScreenUserInput(UINT8 keys, struct KenbakMachineState *kenbakMachineState)
{
    if (keys & J_A)
    {
        // get cursor position and apply action
        if (currentCursorPosition->action == BIT_ACTION)
        {
        }
        else if (currentCursorPosition->action == POWER_ACTION)
        {
            ToggleKenbakMachinePower(kenbakMachineState);
        }
        else if (currentCursorPosition->action == DISPLAY_ADDRESS_ACTION)
        {
        }
        else if (currentCursorPosition->action == SET_ADDRESS_ACTION)
        {
        }
        else if (currentCursorPosition->action == READ_MEMORY_ACTION)
        {
        }
        else if (currentCursorPosition->action == STORE_MEMORY_ACTION)
        {
        }
        else if (currentCursorPosition->action == CLEAR_ACTION)
        {
        }
        else if (currentCursorPosition->action == LOCK_ACTION)
        {
            ToggleKenbakMachineLock(kenbakMachineState);
        }
        else if (currentCursorPosition->action == RUN_ACTION)
        {
            ToggleKenbakMachineRun(kenbakMachineState);
        }
    }
    if (keys & J_START)
    {
        ToggleKenbakMachineRun(kenbakMachineState);
    }
    if (keys & J_SELECT)
    {
        ToggleKenbakMachineOneStep(kenbakMachineState);
    }
    if (keys & J_LEFT)
    {
        if (currentCursorPosition->left != 0)
            currentCursorPosition = currentCursorPosition->left;
    }
    if (keys & J_RIGHT)
    {
        if (currentCursorPosition->right != 0)
            currentCursorPosition = currentCursorPosition->right;
    }
    if (keys & J_UP)
    {
        if (currentCursorPosition->up != 0)
            currentCursorPosition = currentCursorPosition->up;
    }
    if (keys & J_DOWN)
    {
        if (currentCursorPosition->down != 0)
            currentCursorPosition = currentCursorPosition->down;
    }
    return KENBAK_SCREEN;
}