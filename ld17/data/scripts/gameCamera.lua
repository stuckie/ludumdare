CameraClass = {};
CameraClass.__index = CameraClass;

function CameraClass.create( layer, bottomX, bottomY, topX, topY )
	local camera = {};
	setmetatable(camera, CameraClass);

	camera.z = layer;
	camera.bottomX = bottomX;
	camera.bottomY = bottomY;
	camera.topX = topX;
	camera.topY = topY;
	camera.tileX = 0;
	camera.tileY = 0;
	camera.y = 0;
	camera.x = 0;
	camera.speed = 5;

	return camera;
end

function CameraClass:render()
	if self.y > 95 then self.y = 95 end;
	if self.y < 0 then self.y = 0 end;
	if self.x < 0 then self.x = 0 end;
	if self.x > 100 then self.x = 100 end;

	-- Layer 0
	for y=0, 100 do
		for x=0, 100 do
			local tile = layer0Map[y][x];
			if tile ~= nil then
				if (calcDistanceX((tile.tileX*64) + 64, self.x*64) < WindowWidth + 64
				and calcDistanceY((tile.tileY*64) + 64, self.y*64) < WindowHeight + 64) then
					displayLayer0( tile.tileCode, tile.tileX*64-self.x*64, tile.tileY*64-self.y*64 );
				end
			end
		end
	end

	-- Layer 1
	for y=0, 100 do
		for x=0, 100 do
			local tile = layer1Map[y][x];
			if tile ~= nil then
				if (calcDistanceX((tile.tileX*64) + 64, self.x*64) < WindowWidth + 64
				and calcDistanceY((tile.tileY*64) + 64, self.y*64) < WindowHeight + 64) then
					displayLayer1( tile.tileCode, tile.tileX*64-self.x*64, tile.tileY*64-self.y*64 );
				end
			end
		end
	end
end

function CameraClass:panLeft()
	if self.x > 0 then
		local movement = self.speed * DeltaTime;
		self.x = self.x - movement;
	end
end

function CameraClass:panRight()
	if self.x < 95 then
		local movement = self.speed * DeltaTime;
		self.x = self.x + movement;
	end
end

function CameraClass:panUp()
	if self.y > 0 then
		local movement = self.speed * DeltaTime;
		self.y = self.y - movement;
	end
end

function CameraClass:panDown()
	if self.y < 100 then
		local movement = self.speed * DeltaTime;
		self.y = self.y + movement;
	end
end