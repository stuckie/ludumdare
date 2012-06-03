-- derelict_ change loadout screen

WEAPON_NONE = 0;
EQUIPMENT_NONE = 0;

WEAPON_PISTOL = 10;		WEAPON_SPIT = 20;			EQUIPMENT_BIOEYE = 30;
WEAPON_SHOTGUN = 11;	WEAPON_ACID_SPLASH = 21;	EQUIPMENT_LIMB = 31;
WEAPON_AUTOMATIC = 12;	WEAPON_ACID_STREAM = 22;
WEAPON_ROCKET = 13;		WEAPON_PLASMA = 23;
WEAPON_SWORD = 14;		WEAPON_CLAWS = 24;

local currentSpawn = 0;
local maxSpawns = 10;

function initialiseLoadoutMenu( )
	addTextWriter("derelict_", 240, 50, "defaultFont16", "derelict_", 0, 16);
	addTextWriter("LoadOut", 240, 150, "defaultFont16", "Load Out", 1, 16);
	addTextWriter("Press Return", 210, 350, "defaultFont16", "Press Return", 2, 16);
end

local debounce = false;
function updateLoadoutMenu( )
	-- My God It's Full of Stars!
	renderStarfield();
	updateTextWriters();

	displayText(150, 170, "defaultFont16", 16, "Player "..ACTIVE_PLAYER);
	displayText(50, 200, "defaultFont16", 16, "Choose Spawn:");
	displayText(300, 200, "defaultFont16", 16, "" .. currentSpawn);

	if ControlMan:getSTART() == true and debounce == true then
		debounce = false;
		local player = getPlayer("Player"..ACTIVE_PLAYER);
		if player.faction == FACTION_HUMAN then
			loadOutChooseSpawnPointHuman(currentSpawn);
		else
			loadOutChooseSpawnPointAlien(currentSpawn);
		end
		currentSpawn = 0;
		if ACTIVE_PLAYER < MAX_PLAYERS - 1 then
			ACTIVE_PLAYER = ACTIVE_PLAYER + 1;
		else
			cleanLoadOutMenu();
			setMenu(CHANGE_PLAYER);
			ACTIVE_PLAYER = 0;
			initialiseMenus();
		end
	elseif ControlMan:getLeft() == true and debounce == true then
		debounce = false;
		if currentSpawn > 0 then
			currentSpawn = currentSpawn - 1;
		end
	elseif ControlMan:getRight() == true and debounce == true then
		debounce = false;
		if currentSpawn < maxSpawns then
			currentSpawn = currentSpawn + 1;
		end
	elseif ControlMan:getSTART() == false and debounce == false 
	and ControlMan:getLeft() == false and ControlMan:getRight() == false then
		debounce = true;
	end
end

function loadOutChooseSpawnPointHuman( number )
	print("humanspawning" .. number);
	local player = getPlayer("Player" .. ACTIVE_PLAYER);
	if number == 0 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i, 2, 0);
		end
	elseif number == 1 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i, 20, 0);
		end
	elseif number == 2 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+110, 20, 0);
		end
	elseif number == 3 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+110, 9, 0);
		end
	elseif number == 4 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i, 23, 1);
		end
	elseif number == 5 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+115, 22, 1);
		end
	elseif number == 6 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+115, 8, 1);
		end
	elseif number == 7 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i, 9, 2);
		end
	elseif number == 8 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i, 28, 2);
		end
	elseif number == 9 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+114, 14, 2);
		end
	elseif number == 10 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+114, 28, 2);
		end
	end
	
end

function loadOutChooseSpawnPointAlien( number )
	print("alienspawning" .. number);
	local player = getPlayer("Player" .. ACTIVE_PLAYER);
	if number == 0 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+71, 7, 0);
		end
	elseif number == 1 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+75, 19, 0);
		end
	elseif number == 2 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+36, 12, 0);
		end
	elseif number == 3 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+33, 23, 0);
		end
	elseif number == 4 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+7, 21, 1);
		end
	elseif number == 5 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+56, 20, 1);
		end
	elseif number == 6 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+39, 4, 1);
		end
	elseif number == 7 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+70, 4, 2);
		end
	elseif number == 8 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+49, 20, 2);
		end
	elseif number == 9 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+24, 4, 2);
		end
	elseif number == 10 then
		for i=1,player:getUnitAmount() do
			local unit = player:getUnit(player:getUnitAmount() - i+1);
 			unit:setPosition(i+16, 6, 2);
		end
	end

end

function cleanLoadOutMenu()
	removeTextWriter("derelict_");
	removeTextWriter("LoadOut");
	removeTextWriter("Press Return");
end

function checkWeaponRange( weapon, distance )
	if weapon == WEAPON_NONE then
		return false;
	elseif weapon == WEAPON_PISTOL then
		if distance < 3 then return true end;
	elseif weapon == WEAPON_SHOTGUN then
		if distance < 4 then return true end;
	elseif weapon == WEAPON_AUTOMATIC then
		if distance < 5 then return true end;
	elseif weapon == WEAPON_ROCKET then
		if distance < 8 then return true end;
	elseif weapon == WEAPON_SWORD then
		if distance < 1 then return true end;
	elseif weapon == WEAPON_SPIT then
		if distance < 3 then return true end;
	elseif weapon == WEAPON_ACID_SPLASH then
		if distance < 4 then return true end;
	elseif weapon == WEAPON_ACID_STREAM then
		if distance < 5 then return true end;
	elseif weapon == WEAPON_PLASMA then
		if distance < 8 then return true end;
	elseif weapon == WEAPON_CLAWS then
		if distance < 1 then return true end;
	end
	
	return false;
end

function calcWeaponDamage(weapon, range, moved, evade)
	local damage = 0;
	local accuracy = 0;
	if weapon == WEAPON_NONE then
		accuracy = 0;
		damage = 0;
	elseif weapon == WEAPON_PISTOL then
		accuracy = 2;
		damage = 1;
	elseif weapon == WEAPON_SHOTGUN then
		accuracy = 4;
		damage = 4;
	elseif weapon == WEAPON_AUTOMATIC then
		accuracy = 4;
		damage = 3;
	elseif weapon == WEAPON_ROCKET then
		accuracy = 1;
		damage = 6;
	elseif weapon == WEAPON_SWORD then
		accuracy = 6;
		damage = 4;
	elseif weapon == WEAPON_SPIT then
		accuracy = 2;
		damage = 1;
	elseif weapon == WEAPON_ACID_SPLASH then
		accuracy = 4;
		damage = 4;
	elseif weapon == WEAPON_ACID_STREAM then
		accuracy = 4;
		damage = 3;
	elseif weapon == WEAPON_PLASMA then
		accuracy = 1;
		damage = 6;
	elseif weapon == WEAPON_CLAWS then
		accuracy = 6;
		damage = 4;
	end
	local requiredScore = ( accuracy / ( range + moved + evade ) ) * 10;
	local dieRoll = math.random() * 20;

	if dieRoll < requiredScore then
		return damage;
	else
		return 0; -- MISSED!
	end
end
