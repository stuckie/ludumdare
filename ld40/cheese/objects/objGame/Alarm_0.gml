/// @description Countdown Timer

if (0 < mCountDown) {
	--mCountDown;
	alarm[0] = room_speed;
} else {
	if (GameState.CountDown == mState) {
		mState = GameState.GamePlay;
		alarm[1] = room_speed;
		alarm[2] = 5 * room_speed;
	}
}