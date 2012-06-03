-- derelict_ camera

CameraClass = {};
CameraClass.__index = CameraClass;

function CameraClass.create( derelictFloor, bottomX, bottomY, topX, topY )
	local camera = {};
	setmetatable(camera, CameraClass);

	camera.z = derelictFloor;
	camera.bottomX = bottomX;
	camera.bottomY = bottomY;
	camera.topX = topX;
	camera.topY = topY;
	camera.y = 25;
	camera.x = 0;
	camera.speed = 1;

	return camera;
end

function CameraClass:render()
	local player = getPlayer("Player"..ACTIVE_PLAYER);

	-- draw ship tiles in this area
	if self.y > 15 then self.y = 15 end; -- hack...
	if self.y < 0 then self.y = 0 end;
	if self.x < 0 then self.x = 0 end;
	if self.x > derelictRoomWidth * (derelictFloorWidth - 1) then self.x = derelictRoomWidth * (derelictFloorWidth - 1) end;
	for y=self.bottomY + self.y,self.topY + self.y do
		for x=self.bottomX + self.x,self.topX + self.x do
			if player.lineOfSight[self.z][y][x] == nil then
				print("bugger: " .. self.z .. ", " .. y .. ", " .. x);
				break;
			end
			if player.lineOfSight[self.z][y][x] ~= LOS_UNEXPLORED then
			
				local tile = derelictShipTiles[self.z][y][x];
				if tile ~= nil then
					displayTile( tile.tileCode, tile.textureSheet, tile.tileX*32-self.x*32, tile.tileY*32-self.y*32 );
					
					if player.lineOfSight[self.z][y][x] == LOS_EXPLORED then
						displayTile( "fade", "tileData", tile.tileX*32-self.x*32, tile.tileY*32-self.y*32 );
					end
				end
			end
		end
	end

	-- draw door tiles in this area
	for y=self.bottomY + self.y,self.topY + self.y do
		for x=self.bottomX + self.x,self.topX + self.x do
			if player.lineOfSight[self.z][y][x] ~= LOS_UNEXPLORED then
				local tile = derelictDoorTiles[self.z][y][x];
				if tile ~= nil then
					displayTile( tile.tileType, "tileData", x*32-self.x*32, y*32-self.y*32 );

					if player.lineOfSight[self.z][y][x] == LOS_EXPLORED then
						displayTile( "fade", "tileData", x*32-self.x*32, y*32-self.y*32 );
					end
				end
			end
		end
	end

	-- draw entities in this area
	for y=self.bottomY + self.y,self.topY + self.y do
		for x=self.bottomX + self.x,self.topX + self.x do
			if player.lineOfSight[self.z][y][x] ~= LOS_UNEXPLORED then
				local entity = derelictEntities[self.z][y][x];
				if entity ~= nil then
					if player.lineOfSight[self.z][y][x] == LOS_EXPLORED then
						displayTile( "blip", "tileData", x*32-self.x*32, y*32-self.y*32 );
					elseif player.lineOfSight[self.z][y][x] == LOS_VISIBLE then
						crewSelectShowUnitPic(entity.class, x * 32 - self.x*32, y * 32 - self.y*32);
						
					end
				end
			end
		end
	end

	-- draw blips
	for y=self.bottomY + self.y,self.topY + self.y do
		for x=self.bottomX + self.x,self.topX + self.x do
			if player.lineOfSight[self.z][y][x] ~= LOS_UNEXPLORED then
				local entity = derelictEntities[self.z][y][x];
				if entity ~= nil then
					if player.lineOfSight[self.z][y][x] == LOS_EXPLORED then
						displayTile( "blip", "tileData", x*32-self.x*32, y*32-self.y*32 );
					elseif player.lineOfSight[self.z][y][x] == LOS_VISIBLE then
						crewSelectShowUnitPic(entity.class, x * 32 - self.x*32, y * 32 - self.y*32);
						
					end
				end
			end
		end
	end

	-- draw Player's units
	for unitNum=1,player:getUnitAmount() do
		local unit = player:getUnit(unitNum);
		if unit.z == self.z then
			crewSelectShowUnitPic(unit.class, unit.x * 32 - self.x*32, unit.y * 32 - self.y*32);
		end
	end

	-- draw HUD elements if need be
	player:renderAction();
	renderHudElements();
end

function CameraClass:panLeft()
	if self.x > 0 then
		self.x = self.x - self.speed;
	end
end

function CameraClass:panRight()
	if self.x < (derelictRoomWidth) * (derelictFloorWidth - 1) then
		self.x = self.x + self.speed;
	end
end

function CameraClass:panUp()
	if self.y > 0 then
		self.y = self.y - self.speed;
	end
end

function CameraClass:panDown()
	if self.y < (derelictRoomHeight) * (derelictFloorHeight - 1) then
		self.y = self.y + self.speed;
	end
end
