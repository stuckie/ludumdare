ig.module(
	'game.entities.cross'
)
.requires(
	'game.gamemanager',
	'impact.sound',
	'impact.entity'
)
.defines(function(){
	
EntityCross = ig.Entity.extend({
	size: {x: 8, y: 8},
	maxVel: {x: 100, y: 100},
	friction: {x: 150, y: 0},
	
	type: ig.Entity.TYPE.B, // Evil enemy group
	checkAgainst: ig.Entity.TYPE.A, // Check against friendly
	collides: ig.Entity.COLLIDES.PASSIVE,
	
	health: 1,
	
	speed: 100,
	flip: false,

	collectSound: new ig.Sound( 'media/Stun.*' ),
	
	animSheet: new ig.AnimationSheet( 'media/cross.png', 8, 8 ),
	
	init: function( x, y, settings ) {
		this.parent( x, y, settings );
		
		this.addAnim( 'idle', 1, [0] );
	},
	
	
	update: function() {
		if (this.standing)
			this.vel.y = -this.speed;
		
		if (this.pos.x > 480 - this.size.x)
			this.pos.x = 0;
		if (this.pos.x < 0)
			this.pos.x = 480 - this.size.x;
		
		this.parent();
	},
	
	kill: function() {
		this.collectSound.play();
		var player = ig.game.getEntityByName('player');
		player.setInvincible();
		this.parent();
		MainGameManager.addScore(100);
	},
	
	check: function( other ) {
		this.kill();
	}
});

});
