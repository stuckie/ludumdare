-- GEvOlve
-- Written by Steven "Stuckie" Campbell
-- Started 19th April 2008
-- For LD11 and AI Coursework

-- There are some SGZEngine systems which need to be globalised to your entire script
Render = SGZRender();			-- You need to be able to tell it to update the screen any time you draw something new
Controller = SGZControl();		-- The Controller information
Interpret = SGZInterpret();		-- The Interpretor, for polling the engine event queue for example
Audio = SGZAudio();			-- The Audio Interface - you only need one as it's a manager in it's own right
EntityMan = SGZEntityManager();		-- The Entity Manager - for letting the Engine handle the entities
TextureMan = SGZTextureManager();	-- The Texture Manager - for loading in new Textures!

MaxEntities = 100;

EntityMan:SetMaxEntities(MaxEntities);
math.randomseed(os.time());
Entities = nil;

loadfile ("data/scripts/config.sgz");
dofile ("data/scripts/ai/pleb.lua");
dofile ("data/scripts/ai/attacker.lua");
dofile ("data/scripts/ai/defender.lua");
dofile ("data/scripts/ai/healer.lua");
dofile ("data/scripts/ai/cpuplayer.lua");
dofile ("data/scripts/spawndemo.lua");

Unit = {
	Total = 0;
	Squares = 0;
	Circles = 0;
};

function intro()
	Render:NewWindow("Loading...",WindowWidth,WindowHeight,WindowBPP);
	-- Load initial assets up in here...

	local IntroPic = SGZTexture();
	IntroPic:Load("data/gfx/title.png");
	IntroPic:LoadMask("data/gfx/titlemask.png");

	done = false;
	fade = 0.0;
	while done==false do
		fade = fade + 0.005;
		IntroPic:SetColour(fade/5,fade/10,fade/3);
		IntroPic:Blit(0,0,-1);
		Render:UpdateScreen();
		if fade>=1.0 then done=true end			
	end
	IntroPic:Delete();
	Render:NewWindow("stuckieGAMEZ : GEvOlve | " .. Interpret:SystemInfo() .. " - " .. Interpret:RenderInfo() ,WindowWidth,WindowHeight,WindowBPP);
end

function game()
	running = Interpret:Running();
	while running==true do
		Controller:UpdateControls();
		Interpret:NextEvent();
		Interpret:Update();
		EntityMan:Update();
		
		running = Interpret:Running();
	end
end

function stop()
	Render:NewWindow("Shutting Down...",WindowWidth,WindowHeight,WindowBPP);
	-- Clean up anything we need to...
end

function menu()
	done = false;
	Interpret:LogDebug("Starting Menu\n");
	while done==false do
		Controller:UpdateControls();
		if Controller:GetKey("q") == true then AddCircleAttacker(); end
		if Controller:GetKey("w") == true then AddSquareAttacker(); end
		if Controller:GetKey("e") == true then AddCircleDefender(); end
		if Controller:GetKey("r") == true then AddSquareDefender(); end
		if Controller:GetKey("t") == true then AddCircleHealer(); end
		if Controller:GetKey("y") == true then AddSquareHealer(); end
		--if Controller:GetKey("u") == true then AddCircle(); end
		--if Controller:GetKey("i") == true then AddSquare(); end
		Interpret:NextEvent();
		Interpret:Update();
		EntityMan:Update();
		SpawnDemo();
		running = Interpret:Running();
		if running==false then done = true; end;
	end
	-- New Game
	-- Options
	-- Quit Game
end

function main()
	intro();
	menu();
	stop();	
end
