ig.module(
	'game.entities.cutscenedata'
)
.requires(
	'game.gamemanager',
	'impact.entity'
)
.defines(function(){
	
EntityCutscenedata = ig.Entity.extend({
	size: {x: 16, y: 16},
	_wmDrawBox: true,
	_wmBoxColor: 'rgba(196, 255, 0, 0.7)',
	
	cutscene: 'StartScreen',

	type: ig.Entity.TYPE.NONE,
	checkAgainst: ig.Entity.TYPE.A,
	collides: ig.Entity.COLLIDES.NEVER,
	
	
	init: function( x, y, settings ) {
		this.parent( x, y, settings );
		MainGameManager.cutsceneData = this;
	},
	
	
	update: function() {
	}
});

});