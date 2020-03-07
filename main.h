#include <types.h>
#include "kenbakmachine.h"

/* Do instruction every MACHINE_SPEED frames */
const UINT8 MACHINE_SPEED = 5;

void updateScreen(UINT8, UINT8, struct KenbakMachineState *);