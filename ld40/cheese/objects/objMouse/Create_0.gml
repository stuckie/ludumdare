/// @description Insert description here
// You can write your code in this editor

mBaseSpeed = 3;
mCheeseSpeed = 2;
mSpeedUp = 1;

mSpeedUpPowerUp = false;
mInvinciblePowerUp = false;
mStunned = false;

speed = 0;
direction = 0;
mCarryingCheese = false;

mId = 0;

mAnimations = [];
enum Animation
{	Idle		= 0
,	Walk		= 1
,	Stunned		= 2
};

enum Colours 
{	Gray = 1
,	Green = 2
,	Blue = 3
,	Yellow = 4
,	Red = 5
};

var idleAnim = [];
idleAnim[@ 0] = 0;

var walkAnim = [];
walkAnim[@ 0] = 0;
walkAnim[@ 1] = 1;

var stunnedAnim = [];
stunnedAnim[@ 0] = 2;
stunnedAnim[@ 1] = 3;
stunnedAnim[@ 2] = 4;
stunnedAnim[@ 3] = 5;

mAnimations[@ Animation.Idle] = idleAnim;
mAnimations[@ Animation.Walk] = walkAnim;
mAnimations[@ Animation.Stunned] = stunnedAnim;

mAnimation = mAnimations[Animation.Stunned];
mAnimIndex = 0;
mAnimMax = 4;

mColour = Colours.Gray;