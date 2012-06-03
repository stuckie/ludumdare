-- GEvOlve Spawn Demo for Menu Screen
-- All we do is get the creatures to continually breed and over run the screen!

SpawnSetup = false;

function SpawnDemo()
	if SpawnSetup == false then 
		TextureMan:AddTexture("circle", "data/gfx/circle.png");
		TextureMan:AddTexMask("circle", "data/gfx/circlemask.png");
		Current = AddCircle();
		EntityMan:MoveTo(Current, math.random(64)-32, math.random(64)-32, -64);
		EntityMan:NewVar(Current, "Task");
		EntityMan:ChangeVar(Current, "Task", "Male");
		EntityMan:NewVar(Current, "Race");
		EntityMan:ChangeVar(Current, "Race", "Circle");
		EntityMan:NewVar(Current, "Status");
		EntityMan:ChangeVar(Current, "Status", "Idle");
		EntityMan:NewVar(Current, "Cooldown");
		EntityMan:ChangeVar(Current, "Cooldown", "10");
		EntityMan:NewVar(Current, "Hunting");
		EntityMan:Colour(Current, 0, 0, 1);
		Entities = { next = Entities, id = Current };

		Current = AddCircle();
		EntityMan:MoveTo(Current, math.random(64)-32, math.random(64)-32, -64);
		EntityMan:NewVar(Current, "Task");
		EntityMan:ChangeVar(Current, "Task", "Female");
		EntityMan:NewVar(Current, "Race");
		EntityMan:ChangeVar(Current, "Race", "Circle");
		EntityMan:NewVar(Current, "Status");
		EntityMan:ChangeVar(Current, "Status", "Idle");
		EntityMan:NewVar(Current, "Cooldown");
		EntityMan:ChangeVar(Current, "Cooldown", "10");
		EntityMan:NewVar(Current, "Hunting");
		EntityMan:Colour(Current, 1, 0, 1);
		Entities = { next = Entities, id = Current };

		TextureMan:AddTexture("square", "data/gfx/square.png");
		TextureMan:AddTexMask("square", "data/gfx/squaremask.png");
		Current = AddSquare();
		EntityMan:MoveTo(Current, math.random(64)-32, math.random(64)-32, -64);
		EntityMan:NewVar(Current, "Task");
		EntityMan:ChangeVar(Current, "Task", "Male");
		EntityMan:NewVar(Current, "Race");
		EntityMan:ChangeVar(Current, "Race", "Square");
		EntityMan:NewVar(Current, "Status");
		EntityMan:ChangeVar(Current, "Status", "Idle");
		EntityMan:NewVar(Current, "Cooldown");
		EntityMan:ChangeVar(Current, "Cooldown", "10");
		EntityMan:NewVar(Current, "Hunting");
		EntityMan:Colour(Current, 0, 0, 1);
		Entities = { next = Entities, id = Current };

		Current = AddSquare();
		EntityMan:MoveTo(Current, math.random(64)-32, math.random(64)-32, -64);
		EntityMan:NewVar(Current, "Task");
		EntityMan:ChangeVar(Current, "Task", "Female");
		EntityMan:NewVar(Current, "Race");
		EntityMan:ChangeVar(Current, "Race", "Square");
		EntityMan:NewVar(Current, "Status");
		EntityMan:ChangeVar(Current, "Status", "Idle");
		EntityMan:NewVar(Current, "Cooldown");
		EntityMan:ChangeVar(Current, "Cooldown", "10");
		EntityMan:NewVar(Current, "Hunting");
		EntityMan:Colour(Current, 1, 0, 1);
		Entities = { next = Entities, id = Current };

		SpawnSetup = true;
	end
	
	UpdateEntities();
end

function Boundaries ( EntityID )
	local X =  EntityMan:GetX(EntityID);
	local Y =  EntityMan:GetY(EntityID);
	local Z =  EntityMan:GetZ(EntityID);

	if X > 32 then X = 32; end
	if X < -32 then X = -32; end
	if Y > 32 then Y = 32; end
	if Y < -32 then Y = -32; end
	if Z > -64 then Z = -64; end
	if Z < -64 then Z = -64; end

	EntityMan:MoveTo(EntityID, X, Y, Z);
end

function UpdateEntities()
	local list = Entities;
	while list do
		EntityExists = EntityMan:CheckExist(list.id);
		if EntityExists == false then list.id = -1; end;
		if EntityExists == true then
			EntityTask = EntityMan:CheckVar(list.id, "Task");
			if EntityTask == "Attacker" then Attacker(list.id); end
			if EntityTask == "Defender" then Defender(list.id); end
			if EntityTask == "Healer" then Healer(list.id); end
			if EntityTask == "Male" then MalePleb(list.id); end
			if EntityTask == "Female" then FemalePleb(list.id); end
			Boundaries(list.id);
		end
		if list.id == -1 then list.next = nil; end
		list = list.next;
	end
end
