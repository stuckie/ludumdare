/// @description Switch Splash Screens

++oCurrentSplash;

alarm[0] = 5 * room_speed;

switch (oCurrentSplash) {
	case SplashScreen.ArcadeBadgers: {
		sprite_index = sprSplashArcadeBadgers;
	};
	break;
	case SplashScreen.MadeInGM: {
		sprite_index = sprSplashMadeinGM;
	};
	break;
	case SplashScreen.GameLogo: {
		sprite_index = sprGameLogo;
	};
	break;
	case SplashScreen.END_OF_SPLASH: {
		room_goto(rmGame);
	};
	break;
};