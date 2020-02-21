#include <gb.h>
#include "spritehelper.h"

void initSpriteDisplay(struct SpriteDisplay *spriteDisplay, UINT8 count)
{
    for (UINT8 cptSprite = 0; cptSprite < count; cptSprite++)
    {
        set_sprite_tile(spriteDisplay[cptSprite].spriteId, spriteDisplay[cptSprite].spriteIndex);
        move_sprite(spriteDisplay[cptSprite].spriteId, (spriteDisplay[cptSprite].x * 8) + 8, (spriteDisplay[cptSprite].y * 8) + 16);
        ShowSprite(&(spriteDisplay[cptSprite]));
    }
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