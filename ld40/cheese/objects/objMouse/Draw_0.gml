/// @description Insert description here
// You can write your code in this editor

var anim = mAnimation[0];
if (0 < mAnimMax)
	anim = mAnimation[mAnimIndex % mAnimMax];
draw_sprite_ext(sprMouse, anim * mColour, x, y, image_xscale, image_yscale, image_angle, image_blend, image_alpha);
if (true == mCarryingCheese)
	draw_sprite(sprCheese, 0, x, y);