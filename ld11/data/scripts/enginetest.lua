-- The Logic Code for Stuckie's Engine Battering Script
-- Written by Steven "Stuckie" Campbell
-- Started 30th January 2008
-- Last Updated 3rd April 2008

-- Since this will more than likely be most people's first look at how to use SGZEngine
-- I'll heavily comment just what's going on, and why.
-- Though it would be beneficial if you know Lua as it's the base language at work here.

-- There are some SGZEngine systems which need to be globalised to your entire script
Render = SGZRender();			-- You need to be able to tell it to update the screen any time you draw something new
Controller = SGZControl();		-- The Controller information
Interpret = SGZInterpret();		-- The Interpretor, for polling the engine event queue for example
Audio = SGZAudio();			-- The Audio Interface - you only need one as it's a manager in it's own right
EntityMan = SGZEntityManager();		-- The Entity Manager - for letting the Engine handle the entities

Sprite = SGZTexture();			-- You can load up Textures manually, but you need to handle them yourself!
Sprite2 = SGZEntity2D("Bob");		-- The same goes for Entities

x = 1;					-- Remember that Lua is typeless!
y = 0;					-- and that these are just throw away variables anyway

function intro() -- Let's setup everything we need
	Render:NewWindow("SGZEngine Loading...",640,480,32);			-- We really need to create a window first before doing ANY graphics

	IntroPic = SGZTexture();						-- Things initialised within a function only last for that function
	IntroPic:Load("data/gfx/loading.png");					-- As said, you need to handle things yourself if you go this route
	IntroPic:Blit(0,0);							-- Right down to the actual blitting and where to on the screen

	Audio:LoadSFX("data/sfx/blirr.wav", "Blirr");				-- SFX and MUS are loaded in much the same way
	Audio:LoadMUS("data/mus/starball.mp3", "Starball");			-- with the filename and an identifier to call back on
--	Audio:LoadMUS("data/mus/eternity.xm", "Eternity");			-- 
	Audio:PlayMUS("Eternity");						--

	done = false;								--
	count1 = 0;								--
	count2 = 0;								--
	while done==false do							--
		Render:NewWindow("SGZEngine Loading...",count1+1,count2+1,32);	--
		IntroPic:Blit(0,0);						--
		Render:UpdateScreen();						--
		if count1==640 then done=true end				
		count1=count1+1;
		count2=count2+1;
		if count2>480 then count2=480 end
	end
	Render:NewWindow("SGZEngine Test",640,480,32);
	Sprite2:CreateAnimation("idle");
	Sprite2:LoadFrame("idle","data/gfx/idle1.png");
	Sprite2:LoadFrame("idle","data/gfx/idle2.png");
	Sprite2:SetAnimation("idle");
	Sprite2:MoveTo(100,100,0);

	EntityMan:Add2DEntity("Fred");
	EntityMan:CreateAnimation("Fred", "idle");
	EntityMan:LoadFrame("Fred", "idle","data/gfx/idle1.png");
	EntityMan:LoadFrame("Fred", "idle","data/gfx/idle2.png");
	EntityMan:SetAnimation("Fred", "idle");
	EntityMan:MoveTo("Fred", 200,200,0);
	EntityMan:Scale("Fred", 1);
	EntityMan:RotateX("Fred", 0);

	EntityMan:Add2DEntity("Fred2");
	EntityMan:CreateAnimation("Fred2", "idle");
	EntityMan:LoadFrame("Fred2", "idle","data/gfx/idle1.png");
	EntityMan:LoadFrame("Fred2", "idle","data/gfx/idle2.png");
	EntityMan:SetAnimation("Fred2", "idle");
	EntityMan:MoveTo("Fred2", 20,200,0);
	EntityMan:Scale("Fred2", 2);
	EntityMan:RotateX("Fred2", 0);

	Audio:RemoveMUS("Eternity");
	Audio:RemoveMUS("Starball");
end

function game()
	running = Interpret:Running();
	while running==true do
		Controller:UpdateControls();
		Interpret:NextEvent();
		Interpret:Update();
		running = Interpret:Running();
		EntityMan:Update();
		Sprite2:Update();
		Sprite2:Scale(x);
		Sprite2:RotateX(y);
		if Controller:GetKey("b") == true then Render:NewWindow("ZOMG! B WAS PRESSED!",640,480,32) end
		if Controller:GetKey("w") == true then y=y-1; end
		if Controller:GetKey("s") == true then y=y+1; end
		if Controller:GetKey("a") == true then 
			x=x-1; 
			Audio:SetPanning(1, 128, 10); 
			Audio:SetSFXVolume("Blirr", 10); 
			Audio:PlaySFX("Blirr", 1, 1);
		end
		if Controller:GetKey("d") == true then 
			x=x+1; 
			Audio:SetPanning(1, 10, 128); 
			Audio:SetSFXVolume("Blirr", 10); 
			Audio:PlaySFX("Blirr", 1, 1);
		end
		if Controller:GetKey("p") == true then Audio:PlaySFX("Blirr"); end
		if Controller:GetKey("0") == true then Audio:StopMUS(); end
		if Controller:GetKey("1") == true then Audio:PlayMUS("Eternity"); end
		if Controller:GetKey("2") == true then Audio:PlayMUS("Starball"); end
	end
end

function stop()
	Render:NewWindow("SGZEngine Shutting Down",640,480,32);
end

function main()
	intro();
	game();
	stop();	
end
