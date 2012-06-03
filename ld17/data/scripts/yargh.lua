dofile("data/scripts/config.sgz");
dofile("data/scripts/list.lua");
dofile("data/scripts/graphics.lua");
dofile("data/scripts/game.lua");
--dofile("data/scripts/menu.lua");

InterpretMan = SGZInterpreter();
RenderMan = SGZRenderer();
AudioMan = SGZAudioMan();
TextureMan = SGZTextureManager();
ControlMan = SGZControlManager();
GameTime = SGZTimer();

FRONT_END_STATE = 0;
GAME_STATE = 1;

ThisPlayer = "Unknown";
globalState = GAME_STATE;
DeltaTime = 0.0;
local currentTime = 0.0;

MOUSE_X = 0;
MOUSE_Y = 0;
MOUSE_LEFT = false;
MOUSE_RIGHT = false;
MOUSE_LEFT_DEBOUNCE = false;
MOUSE_RIGHT_DEBOUNCE = false;

GAME_IN_PROGRESS = false;

local startup = function()
	RenderMan:createWindow(WindowName, WindowWidth, WindowHeight, WindowBPP);
	--RenderMan:setFullscreen(true);
	GameTime:Start();
	currentTime = GameTime:Time();
	initialiseFonts();
	initialiseGraphics();
	changeState(GAME_STATE);
end

local updateMouse = function()
	MOUSE_X, MOUSE_Y = ControlMan:getMousePos();
	MOUSE_LEFT = ControlMan:getMouseLeft();
	MOUSE_RIGHT = ControlMan:getMouseRight();
end

local mainLoop = function()
	local running = true;
	while running == true do
		running = InterpretMan:isRunning();		-- Ensure the Engine's still running
		ControlMan:updateControls();
		updateMouse();
		local FrameTime = (GameTime:Time() - currentTime);
		DeltaTime = FrameTime / 1000.0;
		currentTime = GameTime:Time();
		--print("Time: " .. FrameTime);
		if globalState == FRONT_END_STATE then
			updateMenuScreens();
		elseif globalState == GAME_STATE then
			updateGame();
		end
		RenderMan:updateScreen();
	end
end

changeState = function( newState )
	if newState == GAME_STATE then
		if GAME_IN_PROGRESS == false then
			initialiseGame();
		end
	elseif newState == FRONT_END_STATE then
		initialiseMenus();
	end
	
	globalState = newState;
end

local shutdown = function()
	--RenderMan:setFullscreen(false);
	InterpretMan:quit();
	GameTime:Stop();
end

main = function()
	startup();
	mainLoop();
	shutdown();
end
