#include <types.h>
#include "globaldefine.h"

#ifndef KenbakMachineStateDefine

#define KenbakMachineStateDefine 0x00;

const UINT8 ARegisterAddress = 0000;
const UINT8 BRegisterAddress = 0001;
const UINT8 XRegisterAddress = 0002;
const UINT8 PRegisterAddress = 0003;
const UINT8 OutputRegisterAddress = 0200;
const UINT8 OcARegisterAddress = 0201;
const UINT8 OcBRegisterAddress = 0201;
const UINT8 OcXRegisterAddress = 0201;
const UINT8 InputRegisterAddress = 0377;

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

    BOOLEAN oneStepMode;
};

struct KenbakMachineInstruction
{
    UINT8 codedInstruction;
    UINT8 instruction;
    UINT8 instructionRegister;
    UINT8 addressing;
    UINT8 jumping;
    UINT8 rotateShift;
    UINT8 bitIndex;
    UINT8 secondByte;

    UINT8 pRegisterInc;
};
#endif

// processor register
#define A_REGISTER 1
#define B_REGISTER 2
#define X_REGISTER 3
#define UNCONDITIONAL 4

// processor instruction set
#define ADD_KENBAK_INST 1
#define SUB_KENBAK_INST 2
#define LOAD_KENBAK_INST 3
#define STORE_KENBAK_INST 4
#define OR_KENBAK_INST 5
#define AND_KENBAK_INST 6
#define LNEG_KENBAK_INST 7
#define JPD_KENBAK_INST 8
#define JPI_KENBAK_INST 9
#define JMD_KENBAK_INST 10
#define JMI_KENBAK_INST 11
#define BITSET_0_KENBAK_INST 12
#define BITSET_1_KENBAK_INST 13
#define BITSKIP_0_KENBAK_INST 14
#define BITSKIP_1_KENBAK_INST 15
#define SHIFT_RIGHT_KENBAK_INST 16
#define SHIFT_LEFT_KENBAK_INST 17
#define ROTATE_RIGHT_KENBAK_INST 18
#define ROTATE_LEFT_KENBAK_INST 19
#define HALT_KENBAK_INST 20
#define NOOP_KENBAK_INST 21

// addressing
#define CONST_ADDRESSING 1
#define MEMORY_ADDRESSING 2
#define INDIRECT_ADDRESSING 3
#define INDEXED_ADDRESSING 4
#define INDIRECT_INDEXED_ADDRESSING 5

// Jumping
#define NOTEQUAL_JUMPING 1
#define EQUAL_JUMPING 2
#define INFERIOR_JUMPING 3
#define SUPERIOROREQUAL_JUMPING 4
#define SUPERIOR_JUMPING 5

// RotateShift
#define PLACE_1_ROTATESHIFT 1
#define PLACE_2_ROTATESHIFT 2
#define PLACE_3_ROTATESHIFT 3
#define PLACE_4_ROTATESHIFT 4

void InitKenbakMachineState(struct KenbakMachineState *);
void LoadKenbakMachineMemory(struct KenbakMachineState *, UINT8 *);
void SetKenbakMachinePower(struct KenbakMachineState *, BOOLEAN);
void SetKenbakMachineLock(struct KenbakMachineState *, BOOLEAN);
void SetKenbakMachineRun(struct KenbakMachineState *, BOOLEAN);
void SetKenbakMachineOneStep(struct KenbakMachineState *, BOOLEAN);
void DoKenbakMachineNextInstruction(struct KenbakMachineState *);
UINT8 GetKenbakMachineRegister(struct KenbakMachineState *, UINT8);

void DecodeKenbakMachineInstruction(UINT8, UINT8, struct KenbakMachineInstruction *);
UINT8 GetKenbakMachineRegisterFromInstruction(UINT8);
UINT8 GetKenbakMachineAddressingFromInstruction(UINT8);

void ExecuteKenbakMachineInstruction(struct KenbakMachineState *, struct KenbakMachineInstruction *);
UINT8 GetOperandFromAddressingOrJumpInstruction(struct KenbakMachineState *, struct KenbakMachineInstruction *);
UINT8 GetRegisterAddress(UINT8);
UINT8 GetOcRegisterAddress(UINT8);