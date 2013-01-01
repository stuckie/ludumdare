ig.module(
	'game.entities.evilpresent'
)
.requires(
	'game.gamemanager',
	'impact.entity',
	'impact.timer'
)
.defines(function() {
	
EntityEvilpresent = ig.Entity.extend({
	size: {x: 16, y: 16},
	maxVel: {x: 100, y: 500},
	friction: {x: 150, y: 0},
	jump: 50,
	
	type: ig.Entity.TYPE.B, // Evil enemy group
	checkAgainst: ig.Entity.TYPE.A, // Check against friendly
	collides: ig.Entity.COLLIDES.PASSIVE,
	
	health: 1,
	
	speed: 18,
	flip: false,
	
	animSheet: new ig.AnimationSheet( 'media/evilpresent.png', 16, 16 ),
	
	
	init: function( x, y, settings ) {
		this.parent( x, y, settings );
		this.jumpTimer = new ig.Timer();
		
		this.addAnim( 'idle', 1, [0] );
		this.jumpTimer.set(Math.floor(Math.random()*6));
	},
	
	
	update: function() {
		if( this.standing ) {
			if( !ig.game.collisionMap.getTile(
					this.pos.x + (this.flip ? +4 : this.size.x -4),
					this.pos.y + this.size.y+1
				)
			) {
				this.flip = !this.flip;
			}
		}
		
		var xdir = this.flip ? -1 : 1;
		this.vel.x = this.speed * xdir;
		
		this.currentAnim.flip.x = this.flip;
		if( this.standing ) {
			if (0 < this.jumpTimer.delta()) {
				this.jumpTimer.set(Math.floor(Math.random()*6));
				this.vel.y = -this.jump * 4;
			}
			else {
				this.vel.y = -this.jump;
			}
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