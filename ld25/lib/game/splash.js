ig.module(
	'game.splash'
)
.requires(
	'impact.game'
)
	
.defines(function () {
	Splash = ig.Game.extend({
		nextState: null,
		
		update:function () {
			if (ig.input.pressed('continue')) {
				this.exit();
				ig.system.setGame(this.nextState);
			}
			this.parent();
		},
		
		draw:function () {
			this.parent();
			this.drawScreen();
		},
		
		drawScreen: function() {
		},
		
		exit: function() {
		}

	})
});
