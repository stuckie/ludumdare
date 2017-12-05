/// @description Step Logic

switch (mState) {
	case GameState.CountDown: {
	};
	break;
	case GameState.GamePlay: {
		if (0 == object_exists(objCheese))
			alarm[1] = 1;
	};
	break;
	case GameState.Paused: {
	};
	break;
	case GameState.Results: {
	};
}