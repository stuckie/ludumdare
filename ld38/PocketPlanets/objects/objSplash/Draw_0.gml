/// @description Draw Current Splash

var sprite = undefined;

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

draw_sprite(sprite_index, 0, room_width / 2 - sprite_width / 2, room_height / 2 - sprite_height / 2);