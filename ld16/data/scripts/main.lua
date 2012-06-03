-- derelict_
-- Made for LudumDare 16
-- 12-13th December 2009
-- Steven "Stuckie" Campbell

-- yay for standard setup stuff...
dofile ("data/scripts/config.sgz");
dofile ("data/scripts/list.lua");
dofile ("data/scripts/graphics.lua");
dofile ("data/scripts/loader.lua");
dofile ("data/scripts/player.lua");
dofile ("data/scripts/camera.lua");
dofile ("data/scripts/menus.lua");
dofile ("data/scripts/gameMain.lua");
dofile ("data/scripts/hudElements.lua");

Interpret = SGZInterpreter();
Renderer = SGZRenderer();
AudioMan = SGZAudioMan();
TextureMan = SGZTextureManager();
ControlMan = SGZControlManager();

FRONT_STATE = 0;
GAME_STATE = 1;

state = FRONT_STATE;

ACTIVE_PLAYER = 0;
MAX_PLAYERS = 0;

GAME_IN_PROGRESS = false

function main ( )
	startup();
	mainLoop();
	quit();
end

function startup( )
	Renderer:createWindow(WindowName, WindowWidth, WindowHeight, WindowBPP);
	initialiseFonts();
	initialiseStarfield();
	initialiseMenus();
end

function changeState ( newState )
	if newState == GAME_STATE then
		if GAME_IN_PROGRESS == false then
			initialiseGame();
		end
	elseif
		newState == FRONT_STATE then
		initialiseMenus();
	end
	state = newState;
end

function mainLoop( )
	local running = true;
	while running == true do
		running = Interpret:isRunning();
		if state == FRONT_STATE then
			updateMenuScreens();
		elseif state == GAME_STATE then
			updateGame();
		end
		ControlMan:updateControls();
		Renderer:updateScreen();
	end
end

function quit ( )
	Renderer:setFullscreen(false);
	Renderer:createWindow("Shutting Down...", WindowWidth, WindowHeight, WindowBPP);
	Interpret:quit();
end
