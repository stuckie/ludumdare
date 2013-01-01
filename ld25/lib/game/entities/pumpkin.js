ig.module(
	'game.entities.pumpkin'
)
.requires(
	'game.gamemanager',
	'impact.entity'
)
.defines(function(){
	
EntityPumpkin = ig.Entity.extend({
	size: {x: 16, y: 16},
	maxVel: {x: 100, y: 200},
	friction: {x: 150, y: 0},
	jump: 200,
	
	type: ig.Entity.TYPE.B, // Evil enemy group
	checkAgainst: ig.Entity.TYPE.A, // Check against friendly
	collides: ig.Entity.COLLIDES.PASSIVE,
	
	health: 1,
	
	speed: 24,
	flip: false,
	
	animSheet: new ig.AnimationSheet( 'media/pumpkin.png', 16, 16 ),
	
	init: function( x, y, settings ) {
		this.parent( x, y, settings );
		
		this.addAnim( 'idle', 1, [0] );
	},
	
	
	update: function() {
		var xdir = this.flip ? -1 : 1;
		this.vel.x = this.speed * xdir;
		
		this.currentAnim.flip.x = this.flip;
		if( this.standing ) {
			this.vel.y = -this.jump;
		}
		
		if (this.pos.x > 480 - this.size.x)
			this.pos.x = 0;
		if (this.pos.x < 0)
			this.pos.x = 480 - this.size.x;
		
		this.parent();
	},
	
	
	handleMovementTrace: function( res ) {
		this.parent( res );
		
		// collision with a wall? return!
		if( res.collision.x ) {
			this.flip = !this.flip;
		}
	},
	
	kill: function() {
		MainGameManager.addScore(10);
		MainGameManager.addKill(1);
		this.parent();
	},
	
	check: function( other ) {
		other.receiveDamage( 1, this );
	}
});

});