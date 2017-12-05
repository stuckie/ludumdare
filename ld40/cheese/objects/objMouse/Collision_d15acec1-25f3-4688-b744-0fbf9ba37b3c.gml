/// @description Insert description here
// You can write your code in this editor

instance_create_layer(x, y, "Holes", objOuch);
instance_destroy(other);

mStunned = true;
alarm[2] = room_speed * 2;

mAnimation = mAnimations[Animation.Stunned];
mAnimMax = 4;
mAnimIndex = 0;