ig.module(
	'game.entities.leveldata'
)
.requires(
	'game.gamemanager',
	'impact.entity'
)
.defines(function(){
	
EntityLeveldata = ig.Entity.extend({
	size: {x: 16, y: 16},
	_wmDrawBox: true,
	_wmBoxColor: 'rgba(196, 255, 0, 0.7)',
	
	kills: 1,
	nextLevel: 'Level1',
	presents: 0,

	type: ig.Entity.TYPE.NONE,
	checkAgainst: ig.Entity.TYPE.A,
	collides: ig.Entity.COLLIDES.NEVER,
	
	
	init: function( x, y, settings ) {
		this.parent( x, y, settings );
		MainGameManager.levelData = this;
	},
	
	
	update: function() {
	}
});

});