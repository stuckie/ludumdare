ig.module(
	'game.entities.collectspawner'
)
.requires(
	'impact.entity',
	'game.entities.cross',
	'game.entities.skull',
	'game.entities.scroll'
)
.defines(function(){

EntityCollectspawner = ig.Entity.extend({
	_wmScalable: true,
	_wmDrawBox: true,
	_wmBoxColor: 'rgba(255, 170, 66, 0.7)',
	
	size: {x: 8, y: 8},
	duration: 60,
	count: 3,
	
	durationTimer: null,
	nextEmit: null,
	
	
	init: function( x, y, settings ) {
		this.parent( x, y, settings );
		
		this.durationTimer = new ig.Timer();
		this.nextEmit = new ig.Timer();
		
		this.durationTimer.set(this.duration);
	},
	
	update: function(){	
		if( this.durationTimer.delta() < 0 && this.nextEmit.delta() >= 0 ) {
			this.nextEmit.set( this.duration / this.count );
			
			var x = Math.random().map( 0,1, this.pos.x, this.pos.x+this.size.x );
			var y = Math.random().map( 0,1, this.pos.y, this.pos.y+this.size.y );
			var check = Math.random() * 100;
			if (check < 50)
				ig.game.spawnEntity( EntityScroll, x, y );
			else if (check < 85)
				ig.game.spawnEntity( EntityCross, x, y );
			else
				ig.game.spawnEntity( EntitySkull, x, y );
		}
	}
});

});
