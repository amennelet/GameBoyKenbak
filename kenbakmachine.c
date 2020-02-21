#include "kenbakmachine.h"

void InitKenbakMachineState(struct KenbakMachineState *kenbakMachineState)
{
    for (UINT16 cptMemoryByte = 0; cptMemoryByte < TOTAL_MEMORY; cptMemoryByte++)
    {
        kenbakMachineState->memory[cptMemoryByte] = 0;
    }
    kenbakMachineState->outputValue = 0;
    kenbakMachineState->powerSignal = 0;
    kenbakMachineState->addressSignal = 0;
    kenbakMachineState->clearSignal = 0;
    kenbakMachineState->lockSignal = 0;
    kenbakMachineState->memorySignal = 0;
    kenbakMachineState->runSignal = 0;

    kenbakMachineState->outputButton = 0;
    kenbakMachineState->powerButton = 0;
    kenbakMachineState->addressDisplayButton = 0;
    kenbakMachineState->addressSetButton = 0;
    kenbakMachineState->clearButton = 0;
    kenbakMachineState->lockButton = 0;
    kenbakMachineState->memoryReadButton = 0;
    kenbakMachineState->memoryStoreButton = 0;
    kenbakMachineState->runButton = 0;
}
