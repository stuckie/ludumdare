ig.module(
	'game.entities.player'
)
.requires(
	'game.gamemanager',
	'impact.entity',
	'impact.timer',
	'impact.sound',
	'game.entities.particle'
)
.defines(function(){

EntityPlayer = ig.Entity.extend({
	
	// The players (collision) size is a bit smaller than the animation
	// frames, so we have to move the collision box a bit (offset)
	name: 'player',
	size: {x: 8, y: 14},
	offset: {x: 4, y: 2},
	
	maxVel: {x: 100, y: 1000},
	friction: {x: 600, y: 0},
	
	type: ig.Entity.TYPE.A, // Player friendly group
	checkAgainst: ig.Entity.TYPE.NONE,
	collides: ig.Entity.COLLIDES.PASSIVE,
	
	animSheet: new ig.AnimationSheet( 'media/player.png', 16, 16 ),
	jumpSound: new ig.Sound( 'media/Jump.*' ),
	scytheSound: new ig.Sound( 'media/Hit.*' ),
	deathSound: new ig.Sound( 'media/Death.*' ),
	
	
	// These are our own properties. They are not defined in the base
	// ig.Entity class. We just use them internally for the Player
	flip: false,
	accelGround: 400,
	accelAir: 200,
	jump: 200,
	health: 10,
	scythe: null,
	invincible: true,
	invincibleDelay: 5,
	
	init: function( x, y, settings ) {
		this.parent( x, y, settings );
		
		this.addAnim( 'idle', 1, [0] );
		this.addAnim( 'slash', 1, [1] );
		
		this.invincibleTimer = new ig.Timer();
		this.invincibleTimer.set(this.invincibleDelay);
	},
	
	setInvincible: function() {
		this.invincibleTimer.set(this.invincibleDelay);
		this.invincible = true;
		this.currentAnim.alpha = 0.5;
	},
	
	update: function() {
		if (0 < this.invincibleTimer.delta()) {
			this.invincible = false;
			this.currentAnim.alpha = 1.0;
		}
		
		// move left or right
		var accel = this.standing ? this.accelGround : this.accelAir;
		if ( true == ig.input.state('left') ) {
			this.accel.x = -accel;
			this.flip = true;
		}
		else if( true == ig.input.state('right') ) {
			this.accel.x = accel;
			this.flip = false;
		}
		else {
			this.accel.x = 0;
		}
		
		// jump
		if ( (true == this.standing) && (true == ig.input.pressed('jump') ) ) {
			this.vel.y = -this.jump;
			this.jumpSound.play();
		}
		
		// slash
		if ( true == ig.input.pressed('shoot') ) {
			this.scytheSound.play();
			this.currentAnim = this.anims.slash;
			var flipModifier = this.flip ? 1 : -1;
			this.scythe = ig.game.spawnEntity(EntityPlayerScythe, this.pos.x + ( (this.size.x + this.offset.x) * flipModifier ), this.pos.y, {player:this});
		}
		if ( (true == ig.input.state('shoot')) && (null != this.scythe) ) {
			this.scythe.currentAnim.flip.x = this.flip;
			if ( false == this.flip ) {
				this.scythe.pos.x = this.pos.x + (this.size.x + this.offset.x);
			} else {
				this.scythe.pos.x = this.pos.x - (this.size.x + this.size.x + this.offset.x);
			}
			this.scythe.pos.y = this.pos.y;
		}
		if ( ig.input.released('shoot') ) {
			this.currentAnim = this.anims.idle;
			if (null != this.scythe) {
				this.scythe.kill();
				this.scythe = null;
			}
		}
		
		if (this.pos.x > 480 - this.size.x)
			this.pos.x = 0;
		if (this.pos.x < 0)
			this.pos.x = 480 - this.size.x;
		
		this.currentAnim.flip.x = this.flip;
		
		this.parent();
	},
	
	draw:function () {
		if (this.invincible)
			this.currentAnim.alpha = 1.0 - ( (this.invincibleTimer.delta() * -1) / this.invincibleDelay) + 0.5;

		this.parent();
	},
	
	receiveDamage:function (value, from) {
		if (this.invincible)
			return;
		
		this.parent(value, from);
	},
	
	kill:function() {
		if (null != this.scythe) {
			this.scythe.kill();
			this.scythe = null;
		}
		ig.game.spawnEntity(EntityPlayerDeath, this.pos.x, this.pos.y - (this.size.y + this.offset.y));
		this.parent();
		ig.game.spawnEntity(EntityPlayer, this.pos.x, this.pos.y, {flip:this.flip});
		
		MainGameManager.modifyLives( -1 );
		this.deathSound.play();
		
		for (var i = 0; i < 50; i++)
			ig.game.spawnEntity(EntityParticle, this.pos.x, this.pos.y, {vel: {x: 100, y: 100} });
	}
});

EntityPlayerDeath = ig.Entity.extend({
	size: {x: 16, y: 16},
	offset: {x: 2, y: 2},
	maxVel: {x: 500, y: 200},
	bounciness: 0.5,
	
	type: ig.Entity.TYPE.NONE,
	checkAgainst: ig.Entity.TYPE.NONE,
	collides: ig.Entity.COLLIDES.NEVER,
	
	animSheet: new ig.AnimationSheet( 'media/grimdeath.png', 16, 16 ),
	
	init: function( x, y, settings ) {
		this.parent( x, y, settings );
		
		this.vel.y = -500;
		this.addAnim( 'idle', 1, [0] );
		
		this.killTimer = new ig.Timer();
		this.killTimer.set(5);
	},
	
	update: function() {
		this.parent();
		
		if (this.killTimer.delta() > 0)
			this.kill();
	}
});

EntityPlayerScythe = ig.Entity.extend({
	size: {x: 10, y: 10},
	offset: {x: 0, y: 3},
	
	type: ig.Entity.TYPE.NONE,
	checkAgainst: ig.Entity.TYPE.B,
	collides: ig.Entity.COLLIDES.PASSIVE,
	
	animSheet: new ig.AnimationSheet( 'media/playerscythe.png', 16, 16 ),
	hitSound: new ig.Sound( 'media/Scythe.*' ),
	
	init: function( x, y, settings ) {
		this.parent( x, y, settings );
		
		this.hasHit = false;
		this.hitTimer = new ig.Timer();
		this.addAnim( 'idle', 1, [0] );
	},
	
	update: function() {
		if ( (true == this.hasHit) && (0 < this.hitTimer.delta()) ) {
			this.player.currentAnim = this.player.anims.idle;
			this.kill();
		}
		this.parent();
	},
	
	check: function( other ) {
		if (false == this.hasHit) {
			other.receiveDamage( 1, this );
			this.hasHit = true;
			this.hitTimer.set(0.01);
			this.hitSound.play();
			for (var i = 0; i < 5; i++)
				ig.game.spawnEntity(EntityParticle, this.pos.x, this.pos.y, {vel: {x: 50, y: 100} });
		}
	}
});

});

