ig.module(
	'game.controlscreen'
)
.requires(
	'impact.game',
	'game.splash',
	'game.startscreen'
)
	
.defines(function () {
	ControlScreen = Splash.extend({
		nextState: StartScreen,
		background:new ig.Image('media/controlscreen.png'),
		
		drawScreen: function() {
			this.background.draw(0, 0);
		}

	})
});
