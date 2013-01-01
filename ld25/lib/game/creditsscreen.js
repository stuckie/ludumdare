ig.module(
	'game.creditsscreen'
)
.requires(
	'impact.game',
	'game.splash',
	'game.startscreen'
)
	
.defines(function () {
	CreditsScreen = Splash.extend({
		nextState: StartScreen,
		background:new ig.Image('media/creditsscreen.png'),
		
		drawScreen: function() {
			this.background.draw(0, 0);
		}

	})
});
