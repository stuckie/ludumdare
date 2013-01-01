ig.module(
	'game.entities.jelly'
)
.requires(
	'game.gamemanager',
	'impact.entity'
)
.defines(function(){
	
EntityJelly = ig.Entity.extend({
	size: {x: 16, y: 16},
	maxVel: {x: 100, y: 100},
	friction: {x: 150, y: 0},
	
	type: ig.Entity.TYPE.B, // Evil enemy group
	checkAgainst: ig.Entity.TYPE.A, // Check against friendly
	collides: ig.Entity.COLLIDES.PASSIVE,
	
	health: 1,
	
	speed: 14,
	flip: false,
	
	animSheet: new ig.AnimationSheet( 'media/jelly.png', 16, 16 ),
	
	
	init: function( x, y, settings ) {
		this.parent( x, y, settings );
		
		this.addAnim( 'walk', 0.08, [0,1] );
	},
	
	
	update: function() {
		// near an edge? return!
		if( !ig.game.collisionMap.getTile(
				this.pos.x + (this.flip ? +4 : this.size.x -4),
				this.pos.y + this.size.y+1
			)
		) {
			this.flip = !this.flip;
		}
		
		var xdir = this.flip ? -1 : 1;
		this.vel.x = this.speed * xdir;
		
		this.currentAnim.flip.x = this.flip;
		
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