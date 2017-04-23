/// @description Draw Current Splash

var sprite = undefined;

switch (oCurrentSplash) {
	case SplashScreen.ArcadeBadgers: {
		sprite = sprSplashArcadeBadgers;
	};
	break;
	case SplashScreen.MadeInGM: {
		sprite = sprSplashMAdeInGM;
	};
	break;
	case SplashScreen.GameLogo: {
		sprite = sprSplashGameLogo;
	};
	break;
	case SplashScreen.END_OF_SPLASH: {
		room_goto(rmGame);
	};
	break;
};

draw_sprite(sprite, 0, 0, 0);