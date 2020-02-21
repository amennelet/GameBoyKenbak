#include <types.h>
#include "globaldefine.h"

#define ARegister 0;
#define BRegister 1;
#define XRegister 2;
#define PRegister 3;
#define OutputRegister 0200;
#define OcARegister 0201;
#define OcBRegister 0201;
#define OcCRegister 0201;
#define InputRegister 0377;

#ifndef KenbakMachineStateDefine
#define KenbakMachineStateDefine 0x00;
struct KenbakMachineState
{
    UINT8 memory[TOTAL_MEMORY];

    /* each bit to display on led display */
    UINT8 outputValue;
    BOOLEAN powerSignal;
    BOOLEAN addressSignal;
    BOOLEAN clearSignal;
    BOOLEAN lockSignal;
    BOOLEAN memorySignal;
    BOOLEAN runSignal;

    /* each bit is a button pressed if egal to 1 */
    UINT8 outputButton;
    BOOLEAN powerButton;
    BOOLEAN addressDisplayButton;
    BOOLEAN addressSetButton;
    BOOLEAN clearButton;
    BOOLEAN lockButton;
    BOOLEAN memoryReadButton;
    BOOLEAN memoryStoreButton;
    BOOLEAN runButton;
};
#endif

void InitKenbakMachineState(struct KenbakMachineState *);
