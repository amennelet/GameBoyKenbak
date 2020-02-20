#include <gb.h>
#include "spritehelper.h"

void initSpriteDisplay(struct SpriteDisplay *spriteDisplay)
{
    set_sprite_tile(spriteDisplay->spriteId, spriteDisplay->spriteIndex);
    move_sprite(spriteDisplay->spriteId, (spriteDisplay->x * 8) + 8, (spriteDisplay->y * 8) + 16);
    ShowSprite(spriteDisplay);
}

void ShowSprite(struct SpriteDisplay *spriteDisplay)
{
    set_sprite_prop(spriteDisplay->spriteId, SHOW_SPRITE);
}

void HideSprite(struct SpriteDisplay *spriteDisplay)
{
    set_sprite_prop(spriteDisplay->spriteId, HIDE_SPRITE);
}