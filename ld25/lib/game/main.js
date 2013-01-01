ig.module( 
	'game.main' 
)
.requires(
	'impact.game',
	'plugins.impact-splash-loader.impact-splash-loader',
	
	'game.levels.level1',
	'game.levels.level2',
	'game.levels.level3',
	'game.levels.level4',
	'game.levels.level5',
	'game.levels.transition',
	'game.levels.satan',
	'game.levels.level6',
	'game.levels.level7',
	'game.levels.level8',
	'game.levels.level9',
	'game.levels.level10',
	'game.levels.level11',
	'game.levels.level12',
	'game.gamemanager',
	'game.splash'
)
	
.defines(function () {

MyGame = ig.Game.extend( {
	gravity: 300,
	
	init: function() {
		ig.input.bind( ig.KEY.LEFT_ARROW, 'left' );
		ig.input.bind( ig.KEY.RIGHT_ARROW, 'right' );
		ig.input.bind( ig.KEY.UP_ARROW, 'up' );
		ig.input.bind( ig.KEY.DOWN_ARROW, 'down' );
		ig.input.bind( ig.KEY.X, 'jump' );
		ig.input.bind( ig.KEY.C, 'shoot' );
		ig.input.bind( ig.KEY.ESC, 'quit' );
		ig.input.bind( ig.KEY.T, 'skip' );
		
		MainGameManager.init(this);
		MainGameManager.nextLevel();
	},
	
	update: function() {
		this.parent();
		MainGameManager.update();
		if (ig.input.pressed('quit'))
			MainGameManager.quit();
		if (ig.input.pressed('skip'))
			MainGameManager.nextLevel();
	},
	
	draw: function() {
		this.parent();
		MainGameManager.draw();
	}
});

StartScreen = Splash.extend({
	nextState: MyGame,
	background:new ig.Image('media/titlescreen.png'),
	font: new ig.Font( 'media/04b03.font.png' ),
	
	init: function() {
		ig.input.bind( ig.KEY.SPACE, 'continue' );
		ig.input.bind( ig.KEY.C, 'credits' );
		ig.input.bind( ig.KEY.H, 'controls' );
		ig.music.add( 'media/Title.ogg' );
		ig.music.play();
	},
	
	update: function() {
		if (ig.input.pressed('credits')) {
			ig.system.setGame(CreditsScreen);
		}
		
		if (ig.input.pressed('controls')) {
			ig.system.setGame(ControlScreen);
		}
		
		this.parent();
	},
	
	exit: function() {
		ig.music.fadeOut(3);
		this.parent();
	},
	
	drawScreen: function() {
		this.background.draw(0, 0);
		this.font.draw("Press Space to Start", 300, 260);
		this.font.draw("Press H for Help", 300, 280);
		this.font.draw("Press C for Credits", 300, 300);
		this.font.draw("High Score: " + MainGameManager.highscore, 50, 300);
	}
});

ControlScreen = Splash.extend({
	nextState: StartScreen,
	background:new ig.Image('media/controlscreen.png'),
	font: new ig.Font( 'media/04b03.font.png' ),
	
	drawScreen: function() {
		this.background.draw(0, 0);
		this.font.draw("Press Space to Return", 50, 300);
	}

});

CreditsScreen = Splash.extend({
	nextState: StartScreen,
	background:new ig.Image('media/creditsscreen.png'),
	font: new ig.Font( 'media/04b03.font.png' ),
	
	drawScreen: function() {
		this.background.draw(0, 0);
		this.font.draw("Press Space to Return", 50, 300);
	}

});

Cutscene1 = Splash.extend({
	nextState: MyGame,
	background:new ig.Image('media/cutscene1.png'),
	font: new ig.Font( 'media/04b03.font.png' ),
	
	init: function() {
		var levelData = new EntityLeveldata;
		levelData.nextLevel = 'Satan';
		levelData.kills = 5;
		MainGameManager.levelData = levelData;
	},
	
	drawScreen: function() {
		this.background.draw(0, 0);
		this.font.draw("Press Space to Continue", 300, 260);
	}

});

Cutscene2 = Splash.extend({
	nextState: MyGame,
	background:new ig.Image('media/cutscene2.png'),
	font: new ig.Font( 'media/04b03.font.png' ),
	
	init: function() {
		var levelData = new EntityLeveldata;
		levelData.nextLevel = 'Level6';
		levelData.kills = 5;
		MainGameManager.levelData = levelData;
	},
	
	drawScreen: function() {
		this.background.draw(0, 0);
		this.font.draw("Press Space to Continue", 300, 260);
	}

});

CutsceneEnd = Splash.extend({
	nextState: StartScreen,
	font: new ig.Font( 'media/04b03.font.png' ),
	
	init: function() {
		var levelData = new EntityLeveldata;
		levelData.nextLevel = 'Level1';
		levelData.kills = 5;
		levelData.presents = 5;
		MainGameManager.levelData = levelData;
	},
	
	drawScreen: function() {
		this.font.draw("So, Grim has defeated the Zombie Santa!", 50, 50);
		this.font.draw("This has turned Santa back to normal,", 50, 62);
		this.font.draw("along with all the other people that he", 50, 74);
		this.font.draw("reaped while in Hell.", 50, 86);
		
		this.font.draw("Grim has now made it onto Santa's Good List!", 50, 120);
		this.font.draw("So hopefully, Grim can finally get a present.", 50, 132);
		
		this.font.draw("The End", 250, 200);
		
		this.font.draw("Press Space to Restart", 300, 260);
	},
	
	exit: function() {
		MainGameManager.quit();
	}

});

ig.main( '#canvas', StartScreen, 60, 480, 320, 2, ig.ImpactSplashLoader );

});
