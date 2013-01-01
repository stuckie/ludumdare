ig.module(
	'game.entities.zombiesanta'
)
.requires(
	'game.gamemanager',
	'impact.entity',
	'impact.timer',
	'impact.sound',
	
	'game.entities.pumpkin'
)
.defines(function(){
	
EntityZombiesanta = ig.Entity.extend({
	size: {x: 32, y: 32},
	maxVel: {x: 100, y: 200},
	friction: {x: 150, y: 0},
	
	type: ig.Entity.TYPE.B, // Evil enemy group
	checkAgainst: ig.Entity.TYPE.A, // Check against friendly
	collides: ig.Entity.COLLIDES.PASSIVE,
	
	health: 50,
	
	speed: 50,
	flip: false,
	
	animSheet: new ig.AnimationSheet( 'media/zombiesanta.png', 32, 32 ),
	deathSound: new ig.Sound( 'media/BossKill.*' ),
	
	init: function( x, y, settings ) {
		this.parent( x, y, settings );
		
		//this.addAnim( 'idle', 1, [0] );
		this.addAnim( 'stomp', 0.08, [0,1] );
		//this.addAnim( 'walk', 0.08, [0, 2, 0, 3]);
		
		this.jumpTimer = new ig.Timer();
		this.fireTimer = new ig.Timer();
		this.jumpTimer.set(Math.floor(Math.random()*6));
		this.fireTimer.set(Math.floor(Math.random()*8));
	},
	
	
	update: function() {
		// near an edge? return!
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
		
		if (this.standing) {
			if ( 0 < this.jumpTimer.delta() ) {
				this.jumpTimer.set(Math.floor(Math.random()*6));
				this.vel.y = -this.maxVel.y;
			}
		}
		
		if ( 0 < this.fireTimer.delta() ) {
			this.fireTimer.set(Math.floor(Math.random()*8));
			ig.game.spawnEntity(EntityPumpkin, this.pos.x, this.pos.y, {flip:this.flip});
			MainGameManager.levelData.kills = MainGameManager.levelData.kills + 1;
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
		MainGameManager.addScore(10000);
		MainGameManager.addKill(1);
		MainGameManager.setPresents(15);
		for (var i = 0; i < 15; i++)
			ig.game.spawnEntity(EntityPresent, this.pos.x, this.pos.y, {vel: {x:  (Math.random() * 2 - 1) * 250, y:  (Math.random() * 2 - 1) * 250} });
		this.deathSound.play();
		this.parent();
	},
	
	check: function( other ) {
		other.receiveDamage( 1, this );
	}
});

});