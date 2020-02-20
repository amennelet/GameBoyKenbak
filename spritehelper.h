#include <types.h>

#define LIGHT_ON_SPRITE_INDEX 0x01;
#define SWITCH_ON_SPRITE_INDEX 0x02;
#define BUTTON_BLACK_SPRITE_INDEX 0x03;
#define BUTTON_WHITE_SPRITE_INDEX 0x04;
#define CURSOR_SPRITE_INDEX 0x05;

#define HIDE_SPRITE 0x18U
#define SHOW_SPRITE 0x10U

struct SpriteDisplay
{
    UINT8 spriteId;
    UINT8 spriteIndex;
    UINT8 x;
    UINT8 y;
    UINT8 show;
};

void initSpriteDisplay(struct SpriteDisplay *);
void ShowSprite(struct SpriteDisplay *);
void HideSprite(struct SpriteDisplay *);