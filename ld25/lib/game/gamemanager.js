ig.module(
	'game.gamemanager'
)
.requires(
	'impact.image',
	'impact.font'

//	'game.entities.leveldata'
)
	
.defines(function () {
	GameManager = ig.Class.extend({
		lives: 3,
		score: 0,
		highscore: 0,
		kills: 0,
		presents: 0,
		levelData: null,
		cutsceneData: null,
		lifeSprite: new ig.Image('media/skull.png'),
		font: new ig.Font( 'media/stat.font.png' ),
		game: null,

		init:function(game) {
			this.game = game;
		},
		
		addScore:function( score ) {
			this.score = this.score + score;
		},
		
		modifyLives:function( lives ) {
			this.lives = this.lives + lives;
		},
		
		addKill:function( kill ) {
			this.kills = this.kills + kill;
		},
		
		addPresent:function() {
			this.presents = this.presents + 1;
		},
		
		setPresents:function(presents) {
			this.levelData.presents = presents;
		},
		
		nextLevel:function() {
			if (this.cutsceneData != null) {
				if ("Cutscene1" == this.cutsceneData.cutscene)
					ig.system.setGame(Cutscene1);
				else if ("Cutscene2" == this.cutsceneData.cutscene)
					ig.system.setGame(Cutscene2);
				else if ("CutsceneEnd" == this.cutsceneData.cutscene)
					ig.system.setGame(CutsceneEnd);
				this.cutsceneData = null;
				this.kills = 0;
				this.presents = 0;
			}
			else {
				if (this.levelData != null) {
					this.loadLevelByFileName(this.levelData.nextLevel);
					this.kills = 0;
					this.presents = 0;
				}
				else {
					this.loadLevelByFileName('Level1');
					this.kills = 0;
					this.presents = 0;
				}
			}
		},
		
		update:function () {
			if (this.levelData != null) {
				if (this.presents == this.levelData.presents) {
					this.nextLevel();
				}
			}
			
			if (this.lives == 0) {
				this.quit();
			}
		},
		
		quit: function() {
			ig.system.setGame(StartScreen);
			this.highscore = this.score;
			this.lives = 3;
			this.score = 0;
			this.levelData = null;
			this.cutsceneData = null;
		},
		
		loadLevelByFileName:function (levelName) {
			ig.game.loadLevelDeferred(ig.global['Level' + levelName]);
		},

		draw:function() {
			this.font.draw("Lives:", 5, 303);
			for(var i=0; i < this.lives; i++)
				this.lifeSprite.draw(((this.lifeSprite.width + 2) * i) + 5, 310);
			
			this.font.draw("Score:", 320, 303);
			this.font.draw(this.score, 320, 310);
		}
	})
	
	MainGameManager = new GameManager();
	
});
