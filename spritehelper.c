#include <gb.h>
#include "spritehelper.h"

void initSpriteDisplay(struct SpriteDisplay *spriteDisplay, UINT8 count)
{
    for (UINT8 cptSprite = 0; cptSprite < count; cptSprite++)
    {
        set_sprite_tile(spriteDisplay[cptSprite].spriteId, spriteDisplay[cptSprite].spriteIndex);
        MoveSprite(spriteDisplay[cptSprite].x, spriteDisplay[cptSprite].y, &spriteDisplay[cptSprite]);
        ShowSprite(&(spriteDisplay[cptSprite]));
    }
}

void initCusorDisplay(struct SpriteDisplay *spriteDisplay)
{
    set_sprite_tile(spriteDisplay->spriteId, spriteDisplay->spriteIndex);
    MoveSprite(spriteDisplay->x, spriteDisplay->y, spriteDisplay);
    set_sprite_prop(spriteDisplay->spriteId, 0);
}

void ShowSprite(struct SpriteDisplay *spriteDisplay)
{
    set_sprite_prop(spriteDisplay->spriteId, SHOW_SPRITE);
}

void HideSprite(struct SpriteDisplay *spriteDisplay)
{
    set_sprite_prop(spriteDisplay->spriteId, HIDE_SPRITE);
}

void SwitchSprite(BOOLEAN show, struct SpriteDisplay *spriteDisplay)
{
    if (show)
        ShowSprite(spriteDisplay);
    else
        HideSprite(spriteDisplay);
}

void MoveSprite(UINT8 x, UINT8 y, struct SpriteDisplay *spriteDisplay)
{
    move_sprite(spriteDisplay->spriteId, (x * 8) + 8, (y * 8) + 16);
}