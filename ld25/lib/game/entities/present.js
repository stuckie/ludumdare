ig.module(
	'game.entities.present'
)
.requires(
	'game.gamemanager',
	'impact.entity',
	'impact.sound'
)
.defines(function(){
	
EntityPresent = ig.Entity.extend({
	size: {x: 10, y: 10},
	maxVel: {x: 250, y: 250},
	friction: {x: 150, y: 0},
	
	type: ig.Entity.TYPE.B, // Evil enemy group
	checkAgainst: ig.Entity.TYPE.A, // Check against friendly
	collides: ig.Entity.COLLIDES.PASSIVE,
	
	health: 1,
	
	speed: 50,
	flip: false,
	
	collectSound: new ig.Sound( 'media/Pickup.*' ),
	
	animSheet: new ig.AnimationSheet( 'media/present.png', 10, 10 ),
	
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
		MainGameManager.addScore(1);
		MainGameManager.addPresent();
		this.collectSound.play();
		this.parent();
	},
	
	check: function( other ) {
		this.kill();
	}
});

});
