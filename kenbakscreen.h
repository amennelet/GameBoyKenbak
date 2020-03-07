#include <types.h>
#include "kenbakmachine.h"

struct CusorPosition
{
    struct CusorPosition *left;
    struct CusorPosition *right;
    struct CusorPosition *up;
    struct CusorPosition *down;

    UINT8 x;
    UINT8 y;

    UINT8 action;
    UINT8 actionIndex;
};

#define BIT_ACTION 1
#define POWER_ACTION 2
#define DISPLAY_ADDRESS_ACTION 3
#define SET_ADDRESS_ACTION 4
#define READ_MEMORY_ACTION 5
#define STORE_MEMORY_ACTION 6
#define CLEAR_ACTION 7
#define LOCK_ACTION 8
#define RUN_ACTION 9

void InitKenbakSprites();
void InitCursor();
void UpdateKenbakScreen(UINT8, struct KenbakMachineState *);
UINT8 manageKenbakScreenUserInput(UINT8, struct KenbakMachineState *);