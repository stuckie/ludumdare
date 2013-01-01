ig.module(
	'game.startscreen'
)
.requires(
	'impact.game',
	'game.splash'
)
	
.defines(function () {
	StartScreen = Splash.extend({
		nextState: MyGame,
		background:new ig.Image('media/titlescreen.png'),
		
		init: function() {
			ig.input.bind( ig.KEY.SPACE, 'continue' );
			ig.input.bind( ig.KEY.C, 'credits' );
			ig.input.bind( ig.KEY.H, 'controls' );
		},
		
		update: function() {
			if (ig.input.pressed('credits')) {
				ig.system.setGame(CreditsScreen);
			}
			
			if (ig.input.pressed('controls')) {
				ig.system.setGame(ControlScreen);
			}
			
			this.parent();
		},
		
		drawScreen: function() {
			this.background.draw(0, 0);
		}
	});
});
