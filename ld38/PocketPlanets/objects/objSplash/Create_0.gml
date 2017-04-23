/// @description Setup Splash

enum SplashScreen
{	ArcadeBadgers
,	MadeInGM
,	GameLogo
,	END_OF_SPLASH
};

oCurrentSplash = SplashScreen.ArcadeBadgers;

alarm[0] = 5 * room_speed; // 5 seconds