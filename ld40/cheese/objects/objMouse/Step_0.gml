/// @description Move Mouse and Update Animation

var controller = global.Controllers[mId];

var stopped = true;
if (true == controller[Controller.Left]) {
	stopped = false;
	direction = 180;
} else if (true == controller[Controller.Right]) {
	stopped = false;
	direction = 0;
}

if (true == controller[Controller.Up]) { 
	stopped = false;
	if (0 == direction) direction = 45;
	else if (180 == direction) direction = 135;
	else direction = 90;
} else if (true == controller[Controller.Down]) {
	stopped = false;
	if (0 == direction) direction = 315;
	else if (180 == direction) direction = 225;
	else direction = 270;
}

if (true == mStunned) || (GameState.CountDown == objGame.mState)
	stopped = true;
	
if (false == stopped) {
	if (true == mCarryingCheese) speed = mCheeseSpeed else speed = mBaseSpeed;
	if (true == mSpeedUpPowerUp) speed += mSpeedUp;
	mAnimation = mAnimations[Animation.Walk];
	mAnimMax = 2;
} else {
	if (false == mStunned) {
		mAnimation = mAnimations[Animation.Idle];
		mAnimMax = 1;
	}
	speed = 0;
}

image_angle = direction;
mAnimIndex += 0.1;