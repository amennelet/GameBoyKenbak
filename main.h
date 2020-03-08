#include <types.h>
#include "kenbakmachine.h"

/* Do instruction every MACHINE_SPEED frames */
const UINT8 MACHINE_SPEED = 3;

void updateScreen(UINT8, UINT8, struct KenbakMachineState *);
UINT8 manageUserInput(UINT8, UINT8, struct KenbakMachineState *);
void releaseButtons(struct KenbakMachineState *kenbakMachineState);