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

    kenbakMachineState->oneStepMode = 0;
}

void LoadKenbakMachineMemory(struct KenbakMachineState *kenbakMachineState, UINT8 *memory)
{
    for (UINT16 cptMemoryByte = 0; cptMemoryByte < TOTAL_MEMORY; cptMemoryByte++)
    {
        kenbakMachineState->memory[cptMemoryByte] = memory[cptMemoryByte];
    }
}

void SetKenbakMachinePower(struct KenbakMachineState *kenbakMachineState, BOOLEAN set)
{
    kenbakMachineState->powerButton = set;
    kenbakMachineState->powerSignal = set;
    if (set == 0)
    {
        // TODO: clear machine state on power down
        //InitKenbakMachineState(kenbakMachineState);
        SetKenbakMachineLock(kenbakMachineState, 0);
        SetKenbakMachineRun(kenbakMachineState, 0);
        kenbakMachineState->outputValue = 0;
        kenbakMachineState->addressSignal = 0;
        kenbakMachineState->clearSignal = 0;
        kenbakMachineState->memorySignal = 0;
    }
}

void SetKenbakMachineLock(struct KenbakMachineState *kenbakMachineState, BOOLEAN set)
{
    kenbakMachineState->lockButton = set;
    kenbakMachineState->lockSignal = set;
}

void SetKenbakMachineRun(struct KenbakMachineState *kenbakMachineState, BOOLEAN set)
{
    kenbakMachineState->runSignal = set;
}

void SetKenbakMachineOneStep(struct KenbakMachineState *kenbakMachineState, BOOLEAN set)
{
    kenbakMachineState->oneStepMode = set;
    kenbakMachineState->lockSignal = set;
}

void ToggleKenbakMachinePower(struct KenbakMachineState *kenbakMachineState)
{
    if (kenbakMachineState->powerSignal == 0)
    {
        SetKenbakMachinePower(kenbakMachineState, 1);
    }
    else
    {
        SetKenbakMachinePower(kenbakMachineState, 0);
    }
}
void ToggleKenbakMachineLock(struct KenbakMachineState *kenbakMachineState)
{
    if (kenbakMachineState->lockSignal == 0)
    {
        SetKenbakMachineLock(kenbakMachineState, 1);
    }
    else
    {
        SetKenbakMachineLock(kenbakMachineState, 0);
    }
}
void ToggleKenbakMachineRun(struct KenbakMachineState *kenbakMachineState)
{
    if (kenbakMachineState->runSignal == 0)
    {
        SetKenbakMachineRun(kenbakMachineState, 1);
    }
    else
    {
        SetKenbakMachineRun(kenbakMachineState, 0);
    }
}
void ToggleKenbakMachineOneStep(struct KenbakMachineState *kenbakMachineState)
{
    if (kenbakMachineState->oneStepMode == 0)
    {
        SetKenbakMachineOneStep(kenbakMachineState, 1);
    }
    else
    {
        SetKenbakMachineOneStep(kenbakMachineState, 0);
    }
}

UINT8 GetKenbakMachineRegisterFromInstruction(UINT8 codedInstruction)
{
    if ((codedInstruction & 0300) == 0100)
        return B_REGISTER;
    else if ((codedInstruction & 0300) == 0200)
        return X_REGISTER;
    else if ((codedInstruction & 0300) == 0300)
        return UNCONDITIONAL;
    return A_REGISTER;
}

UINT8 GetKenbakMachineAddressingFromInstruction(UINT8 codedInstruction)
{
    if ((codedInstruction & 0007) == 0004)
        return MEMORY_ADDRESSING;
    else if ((codedInstruction & 0007) == 0005)
        return INDIRECT_ADDRESSING;
    else if ((codedInstruction & 0007) == 0006)
        return INDEXED_ADDRESSING;
    else if ((codedInstruction & 0007) == 0007)
        return INDIRECT_INDEXED_ADDRESSING;
    return CONST_ADDRESSING;
}

void DecodeKenbakMachineInstruction(UINT8 codedInstruction, UINT8 nextByte, struct KenbakMachineInstruction *kenbakMachineInstruction)
{
    kenbakMachineInstruction->codedInstruction = codedInstruction;
    if ((codedInstruction & 0007) == 0000)
    {
        // Halt or Noop
        if ((codedInstruction & 0002) == 0002)
            kenbakMachineInstruction->instruction = NOOP_KENBAK_INST;
        else
            kenbakMachineInstruction->instruction = HALT_KENBAK_INST;
        kenbakMachineInstruction->pRegisterInc = 1;
    }
    else if ((codedInstruction & 0007) == 0001)
    {
        // Shift or rotate
        kenbakMachineInstruction->instructionRegister = A_REGISTER;
        kenbakMachineInstruction->rotateShift = PLACE_4_ROTATESHIFT;

        if ((codedInstruction & 0300) == 0000)
            kenbakMachineInstruction->instruction = SHIFT_RIGHT_KENBAK_INST;
        else if ((codedInstruction & 0300) == 0100)
            kenbakMachineInstruction->instruction = ROTATE_RIGHT_KENBAK_INST;
        else if ((codedInstruction & 0300) == 0200)
            kenbakMachineInstruction->instruction = SHIFT_LEFT_KENBAK_INST;
        else if ((codedInstruction & 0300) == 0300)
            kenbakMachineInstruction->instruction = ROTATE_LEFT_KENBAK_INST;

        if ((codedInstruction & 0040) == 0040)
            kenbakMachineInstruction->instructionRegister = B_REGISTER;

        if ((codedInstruction & 0010) == 0010)
            kenbakMachineInstruction->rotateShift = PLACE_1_ROTATESHIFT;
        else if ((codedInstruction & 0020) == 0020)
            kenbakMachineInstruction->rotateShift = PLACE_2_ROTATESHIFT;
        else if ((codedInstruction & 0030) == 0030)
            kenbakMachineInstruction->rotateShift = PLACE_3_ROTATESHIFT;

        kenbakMachineInstruction->pRegisterInc = 1;
    }
    else if ((codedInstruction & 0007) == 0002)
    {
        // Bit test and maniplation
        if ((codedInstruction & 0300) == 0000)
            kenbakMachineInstruction->instruction = BITSET_0_KENBAK_INST;
        else if ((codedInstruction & 0300) == 0100)
            kenbakMachineInstruction->instruction = BITSET_1_KENBAK_INST;
        else if ((codedInstruction & 0300) == 0200)
            kenbakMachineInstruction->instruction = BITSKIP_0_KENBAK_INST;
        else if ((codedInstruction & 0300) == 0300)
            kenbakMachineInstruction->instruction = BITSKIP_1_KENBAK_INST;

        kenbakMachineInstruction->bitIndex = (codedInstruction & 0070) >> 3;

        kenbakMachineInstruction->secondByte = nextByte;

        kenbakMachineInstruction->pRegisterInc = 2;
    }
    else if ((codedInstruction & 0700) == 0003)
    {
        // And, Or, Lneg
        if ((codedInstruction & 0030) == 0000)
            kenbakMachineInstruction->instruction = OR_KENBAK_INST;
        else if ((codedInstruction & 0030) == 0010)
            kenbakMachineInstruction->instruction = NOOP_KENBAK_INST;
        else if ((codedInstruction & 0030) == 0020)
            kenbakMachineInstruction->instruction = AND_KENBAK_INST;
        else if ((codedInstruction & 0030) == 0030)
            kenbakMachineInstruction->instruction = LNEG_KENBAK_INST;

        kenbakMachineInstruction->addressing = GetKenbakMachineAddressingFromInstruction(codedInstruction);

        kenbakMachineInstruction->secondByte = nextByte;

        kenbakMachineInstruction->pRegisterInc = 1;
        if (kenbakMachineInstruction->instruction != NOOP_KENBAK_INST)
            kenbakMachineInstruction->pRegisterInc = 2;
    }
    else if ((codedInstruction & 0040) == 0040)
    {
        // Jump
        if ((codedInstruction & 0070) == 0040)
            kenbakMachineInstruction->instruction = JPD_KENBAK_INST;
        else if ((codedInstruction & 0070) == 0050)
            kenbakMachineInstruction->instruction = JPI_KENBAK_INST;
        else if ((codedInstruction & 0070) == 0060)
            kenbakMachineInstruction->instruction = JMD_KENBAK_INST;
        else if ((codedInstruction & 0070) == 0070)
            kenbakMachineInstruction->instruction = JMI_KENBAK_INST;

        kenbakMachineInstruction->jumping = NOTEQUAL_JUMPING;
        if ((codedInstruction & 0007) == 0004)
            kenbakMachineInstruction->jumping = EQUAL_JUMPING;
        else if ((codedInstruction & 0007) == 0005)
            kenbakMachineInstruction->jumping = INFERIOR_JUMPING;
        else if ((codedInstruction & 0007) == 0006)
            kenbakMachineInstruction->jumping = SUPERIOROREQUAL_JUMPING;
        else if ((codedInstruction & 0007) == 0007)
            kenbakMachineInstruction->jumping = SUPERIOR_JUMPING;

        kenbakMachineInstruction->instructionRegister = GetKenbakMachineRegisterFromInstruction(codedInstruction);

        kenbakMachineInstruction->secondByte = nextByte;

        kenbakMachineInstruction->pRegisterInc = 2;
    }
    else
    {
        // Add, Sub, Load, Store
        if ((codedInstruction & 0030) == 0000)
            kenbakMachineInstruction->instruction = ADD_KENBAK_INST;
        else if ((codedInstruction & 0030) == 0010)
            kenbakMachineInstruction->instruction = SUB_KENBAK_INST;
        else if ((codedInstruction & 0030) == 0020)
            kenbakMachineInstruction->instruction = LOAD_KENBAK_INST;
        else if ((codedInstruction & 0030) == 0030)
            kenbakMachineInstruction->instruction = STORE_KENBAK_INST;

        kenbakMachineInstruction->instructionRegister = GetKenbakMachineRegisterFromInstruction(codedInstruction);
        if (kenbakMachineInstruction->instructionRegister == UNCONDITIONAL)
            kenbakMachineInstruction->instructionRegister = A_REGISTER;

        kenbakMachineInstruction->addressing = GetKenbakMachineAddressingFromInstruction(codedInstruction);

        kenbakMachineInstruction->secondByte = nextByte;

        kenbakMachineInstruction->pRegisterInc = 2;
    }
}

UINT8 GetOperandFromAddressingOrJumpInstruction(struct KenbakMachineState *kenbakMachineState, struct KenbakMachineInstruction *kenbakMachineInstruction)
{
    // if ADD, SUB, LOAD, STORE, AND, OR, LNEG:
    // Get operand from MEMORY, INDIRECT, INDEXED OR INDIRECT_INDEXED_ADDRESSING
    if (kenbakMachineInstruction->instruction == ADD_KENBAK_INST ||
        kenbakMachineInstruction->instruction == SUB_KENBAK_INST ||
        kenbakMachineInstruction->instruction == LOAD_KENBAK_INST ||
        kenbakMachineInstruction->instruction == STORE_KENBAK_INST ||
        kenbakMachineInstruction->instruction == AND_KENBAK_INST ||
        kenbakMachineInstruction->instruction == OR_KENBAK_INST ||
        kenbakMachineInstruction->instruction == LNEG_KENBAK_INST ||
        kenbakMachineInstruction->instruction == JPI_KENBAK_INST ||
        kenbakMachineInstruction->instruction == JMI_KENBAK_INST)
    {
        if (kenbakMachineInstruction->addressing == MEMORY_ADDRESSING ||
            kenbakMachineInstruction->instruction == JPI_KENBAK_INST ||
            kenbakMachineInstruction->instruction == JMI_KENBAK_INST)
        {
            /*In the Memory mode of addressing I the second word of the instruction
            is the addres s of the operand.*/
            return kenbakMachineState->memory[kenbakMachineInstruction->secondByte];
        }
        else if (kenbakMachineInstruction->addressing == INDIRECT_ADDRESSING)
        {
            /*In the Indirect addressing mode I the second word of the instruction
            is the address of the address of the operand.*/
            return kenbakMachineState->memory[kenbakMachineState->memory[kenbakMachineInstruction->secondByte]];
        }
        else if (kenbakMachineInstruction->addressing == INDEXED_ADDRESSING)
        {
            /*In the Indexed mode of addressing, the contents of the second
            word of the instruction are added to the contents of the X Register to form
            the address of the operand.*/
            return kenbakMachineState->memory[kenbakMachineInstruction->secondByte + kenbakMachineState->memory[XRegisterAddress]];
        }
        else if (kenbakMachineInstruction->addressing == INDIRECT_INDEXED_ADDRESSING)
        {
            /*In the Indirect Indexed mode of addressing, the contents of the
            second word of the instruction are used as an address pointer to the
            contents of another I second I location. The contents of this second
            location are added to the contents of the X Register to form the address
            of the operand•*/
            return kenbakMachineState->memory[kenbakMachineState->memory[kenbakMachineInstruction->secondByte] + kenbakMachineState->memory[XRegisterAddress]];
        }
    }
    return kenbakMachineInstruction->secondByte;
}

UINT8 GetRegisterAddress(UINT8 instructionRegister)
{
    if (instructionRegister == B_REGISTER)
    {
        return BRegisterAddress;
    }
    else if (instructionRegister == X_REGISTER)
    {
        return XRegisterAddress;
    }
    return ARegisterAddress;
}

UINT8 GetOcRegisterAddress(UINT8 instructionRegister)
{
    if (instructionRegister == B_REGISTER)
    {
        return OcBRegisterAddress;
    }
    else if (instructionRegister == X_REGISTER)
    {
        return OcXRegisterAddress;
    }
    return OcARegisterAddress;
}

void ExecuteKenbakMachineInstruction(struct KenbakMachineState *kenbakMachineState, struct KenbakMachineInstruction *kenbakMachineInstruction)
{
    UINT8 registerAddress = GetRegisterAddress(kenbakMachineInstruction->instructionRegister);
    UINT8 operand = GetOperandFromAddressingOrJumpInstruction(kenbakMachineState, kenbakMachineInstruction);
    if (kenbakMachineInstruction->instruction == ADD_KENBAK_INST ||
        kenbakMachineInstruction->instruction == SUB_KENBAK_INST)
    {
        UINT8 ocRegisterAddress = GetOcRegisterAddress(kenbakMachineInstruction->instructionRegister);
        kenbakMachineState->memory[ocRegisterAddress] = 0x00;

        UINT16 result = 0;
        if (kenbakMachineInstruction->instruction == ADD_KENBAK_INST)
            result = (UINT16)kenbakMachineState->memory[registerAddress] + (UINT16)operand;
        else // SUB_KENBAK_INST
            result = (UINT16)kenbakMachineState->memory[registerAddress] - (UINT16)operand;

        kenbakMachineState->memory[registerAddress] = (UINT8)result;
        // I don't understand how to calcul Overflow and carry bit
        if (result > 0xFF)
            kenbakMachineState->memory[ocRegisterAddress] = 0x03;
    }
    else if (kenbakMachineInstruction->instruction == LOAD_KENBAK_INST)
    {
        kenbakMachineState->memory[registerAddress] = operand;
    }
    else if (kenbakMachineInstruction->instruction == STORE_KENBAK_INST)
    {
        kenbakMachineState->memory[operand] = kenbakMachineState->memory[registerAddress];
    }
    else if (kenbakMachineInstruction->instruction == AND_KENBAK_INST)
    {
        kenbakMachineState->memory[registerAddress] &= operand;
    }
    else if (kenbakMachineInstruction->instruction == OR_KENBAK_INST)
    {
        kenbakMachineState->memory[registerAddress] |= operand;
    }
    else if (kenbakMachineInstruction->instruction == LNEG_KENBAK_INST)
    {
        kenbakMachineState->memory[registerAddress] = (operand ^ 0xFF) + 1;
    }
    else if (kenbakMachineInstruction->instruction == JPD_KENBAK_INST ||
             kenbakMachineInstruction->instruction == JPI_KENBAK_INST ||
             kenbakMachineInstruction->instruction == JMD_KENBAK_INST ||
             kenbakMachineInstruction->instruction == JMI_KENBAK_INST)
    {
        BOOLEAN doJump = 0;
        if (kenbakMachineInstruction->jumping == NOTEQUAL_JUMPING &&
            kenbakMachineState->memory[registerAddress] != 0x00)
            doJump = 1;
        else if (kenbakMachineInstruction->jumping == EQUAL_JUMPING &&
                 kenbakMachineState->memory[registerAddress] == 0x00)
            doJump = 1;
        else if (kenbakMachineInstruction->jumping == INFERIOR_JUMPING &&
                 kenbakMachineState->memory[registerAddress] & 0x80 == 0x80)
            doJump = 1;
        else if (kenbakMachineInstruction->jumping == SUPERIOROREQUAL_JUMPING &&
                 kenbakMachineState->memory[registerAddress] & 0x80 == 0x00)
            doJump = 1;
        else if (kenbakMachineInstruction->jumping == SUPERIOR_JUMPING &&
                 kenbakMachineState->memory[registerAddress] & 0x80 == 0x00 &&
                 kenbakMachineState->memory[registerAddress] != 0x00)
            doJump = 1;
        if (doJump == 1 || kenbakMachineInstruction->instructionRegister == UNCONDITIONAL)
        {
            kenbakMachineInstruction->pRegisterInc = 0;
            kenbakMachineState->memory[PRegisterAddress] = operand;
            if (kenbakMachineInstruction->instruction == JMD_KENBAK_INST ||
                kenbakMachineInstruction->instruction == JMI_KENBAK_INST)
                kenbakMachineInstruction->pRegisterInc = 1;
        }
    }
    else if (kenbakMachineInstruction->instruction == BITSET_0_KENBAK_INST ||
             kenbakMachineInstruction->instruction == BITSET_1_KENBAK_INST ||
             kenbakMachineInstruction->instruction == BITSKIP_0_KENBAK_INST ||
             kenbakMachineInstruction->instruction == BITSKIP_1_KENBAK_INST)
    {
        UINT8 mask = 0x01 << kenbakMachineInstruction->bitIndex;
        if (kenbakMachineInstruction->instruction == BITSET_0_KENBAK_INST)
            kenbakMachineState->memory[kenbakMachineInstruction->secondByte] &= ~mask;
        else if (kenbakMachineInstruction->instruction == BITSET_1_KENBAK_INST)
            kenbakMachineState->memory[kenbakMachineInstruction->secondByte] |= mask;
        else if (kenbakMachineInstruction->instruction == BITSKIP_0_KENBAK_INST &&
                 (kenbakMachineState->memory[kenbakMachineInstruction->secondByte] & mask) == 0)
            kenbakMachineInstruction->pRegisterInc = 4;
        else if (kenbakMachineInstruction->instruction == BITSKIP_1_KENBAK_INST &&
                 (kenbakMachineState->memory[kenbakMachineInstruction->secondByte] & mask) > 0)
            kenbakMachineInstruction->pRegisterInc = 4;
    }
    else if (kenbakMachineInstruction->instruction == SHIFT_RIGHT_KENBAK_INST)
    {
        kenbakMachineState->memory[registerAddress] <<= kenbakMachineInstruction->rotateShift;
    }
    else if (kenbakMachineInstruction->instruction == SHIFT_LEFT_KENBAK_INST)
    {
        kenbakMachineState->memory[registerAddress] >>= kenbakMachineInstruction->rotateShift;
    }
    else if (kenbakMachineInstruction->instruction == ROTATE_RIGHT_KENBAK_INST)
    {
        for (UINT8 cptRotate = 0; cptRotate < kenbakMachineInstruction->rotateShift; cptRotate++)
        {
            UINT8 rightBit = (kenbakMachineState->memory[registerAddress] & 0x01) << 7;
            kenbakMachineState->memory[registerAddress] >>= 1;
            kenbakMachineState->memory[registerAddress] |= rightBit;
        }
    }
    else if (kenbakMachineInstruction->instruction == ROTATE_LEFT_KENBAK_INST)
    {
        for (UINT8 cptRotate = 0; cptRotate < kenbakMachineInstruction->rotateShift; cptRotate++)
        {
            UINT8 leftBit = (kenbakMachineState->memory[registerAddress] & 0x80) >> 7;
            kenbakMachineState->memory[registerAddress] <<= 1;
            kenbakMachineState->memory[registerAddress] |= leftBit;
        }
    }
    else if (kenbakMachineInstruction->instruction == HALT_KENBAK_INST)
    {
        SetKenbakMachineRun(kenbakMachineState, 0);
    }
}

void DoKenbakMachineNextInstruction(struct KenbakMachineState *kenbakMachineState)
{
    if (!kenbakMachineState->powerSignal || !kenbakMachineState->runSignal)
        return;

    struct KenbakMachineInstruction kenbakMachineInstruction;
    UINT8 nextInstructionAddress = kenbakMachineState->memory[PRegisterAddress];
    DecodeKenbakMachineInstruction(kenbakMachineState->memory[nextInstructionAddress], kenbakMachineState->memory[nextInstructionAddress + 1], &kenbakMachineInstruction);
    ExecuteKenbakMachineInstruction(kenbakMachineState, &kenbakMachineInstruction);
    kenbakMachineState->memory[PRegisterAddress] += kenbakMachineInstruction.pRegisterInc;

    // Normal mode
    kenbakMachineState->outputValue = kenbakMachineState->memory[OutputRegisterAddress];

    if (kenbakMachineState->oneStepMode)
        SetKenbakMachineRun(kenbakMachineState, 0);
}