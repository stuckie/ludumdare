PlayerClass = {}
PlayerClass.__index = PlayerClass

function PlayerClass.create( posX, posY, posZ )
	local player = {};
	setmetatable(player, PlayerClass);

	local CurrentEntity = "Player";

	EntityMan:add2DEntity(CurrentEntity);
	EntityMan:createAnimation(CurrentEntity, "Right");
	EntityMan:loadFrame(CurrentEntity, "Right", "LevelData", "LevelData", 0, 0, 0, 255, 0, 255);

	EntityMan:createAnimation(CurrentEntity, "Left");
	EntityMan:loadFrame(CurrentEntity, "Left", "LevelData", "LevelData", 0, 16, 0, 255, 0, 255);
	
	EntityMan:setAnimation(CurrentEntity, "Right");

	EntityMan:setDimensions(CurrentEntity, 16, 16, 0);
	EntityMan:moveTo(CurrentEntity, posX, posY, posZ);
	
	player.name = CurrentEntity;
	player.direction = "Right";
	player.position = { x = posX, y = posY, z = posZ };
	player.velocity = { x = 0.0, y = 0.0 };
	player.moonPosition = { x = 0, y = 0 };
	player.maxThrust = 0.5;
	player.speed = 0.005;
	player.buttonDown = false;
	player.health = 100;

	return player;
end

function PlayerClass:setMoonPosition( posX, posY )
	self.moonPosition.x = posX;
	self.moonPosition.y = posY;
end

function PlayerClass:getMoonPosition()
	return self.moonPosition;
end

function PlayerClass:render()
	EntityMan:moveTo(self.name, self.position.x, self.position.y, self.position.z);
end

function PlayerClass:update()
	self:checkInput();
	self:render();
	self:checkTile();
end

function PlayerClass:checkInput()
	if ControlMan:getLeft() == true then
		self.velocity.x = self.velocity.x - self.speed;
		EntityMan:setAnimation(self.name, "Left");
		self.direction = "Left";
	elseif ControlMan:getRight() == true then
		self.velocity.x = self.velocity.x + self.speed;
		EntityMan:setAnimation(self.name, "Right");
		self.direction = "Right";
	elseif ControlMan:getUp() == true then
		self.velocity.y = self.velocity.y - self.speed;
	elseif ControlMan:getDown() == true then
		self.velocity.y = self.velocity.y + self.speed;
	end

	if ControlMan:getZ() == true and self.buttonDown == false then
		addBullet( self.position.x, self.position.y, self.direction, "Player" );
		self.buttonDown = true;
	elseif ControlMan:getZ() == false then
		self.buttonDown = false;
	end


	self.velocity.y = self.velocity.y + moonGravity;
	
	if self.velocity.x > self.maxThrust then
		self.velocity.x = self.maxThrust;
	elseif self.velocity.x < -self.maxThrust then
		self.velocity.x = -self.maxThrust;
	end

	if self.velocity.x > 0 then
		self.velocity.x = self.velocity.x - 0.001;
	elseif self.velocity.x < 0 then
		self.velocity.x = self.velocity.x + 0.001;
	end

	if self.velocity.y > self.maxThrust then
		self.velocity.y = self.maxThrust;
	elseif self.velocity.y < -self.maxThrust then
		self.velocity.y = -self.maxThrust;
	end

	self.position.x = self.position.x + self.velocity.x;
	self.position.y = self.position.y + self.velocity.y;

end

function PlayerClass:checkTile()
	local aboveTile = LevelMan:getTileType( (self.position.x + 8 )/ 16, (self.position.y / 16 ), 1 );
	local belowTile = LevelMan:getTileType( (self.position.x + 8)/ 16, (self.position.y / 16 ) + 1, 1 );
	local leftTile = LevelMan:getTileType( self.position.x / 16, self.position.y / 16, 1 );
	local rightTile = LevelMan:getTileType( (self.position.x / 16) + 1, self.position.y / 16, 1 );
	-- IS IT SOLID? ========================================================================================================
	if belowTile == "Solid" or belowTile == "ResearchLand" or belowTile == "ResearchLeft" or belowTile == "ResearchMid"  or belowTile == "ResearchRight" or belowTile == "LeaveSky" then
		if self.velocity.y > moonGravity then
			self.velocity.y = - self.velocity.y/2 + moonGravity;
			self.health = self.health + self.velocity.y/2;
		else
			self.velocity.y = -moonGravity;
		end
	end
	if aboveTile == "Solid" or aboveTile == "ResearchLand" or aboveTile == "ResearchLeft" or aboveTile == "ResearchMid"  or aboveTile == "ResearchRight" or aboveTile == "LeaveSky" then
		if self.velocity.y < moonGravity then
			self.velocity.y = - self.velocity.y/2 + moonGravity;
			self.health = self.health - self.velocity.y/2;
		else
			self.velocity.y = 0;
		end
	end
	if rightTile == "Solid" or rightTile == "ResearchLand" or rightTile == "ResearchLeft" or rightTile == "ResearchMid"  or rightTile == "ResearchRight" or rightTile == "LeaveSky" then
		if self.velocity.x > moonGravity  then
			self.velocity.x = - self.velocity.x + moonGravity;
			self.health = self.health + self.velocity.x/2;
		else
			self.velocity.x = -moonGravity;
		end
	end
	if leftTile == "Solid" or leftTile == "ResearchLand" or leftTile == "ResearchLeft" or leftTile == "ResearchMid"  or leftTile == "ResearchRight" or leftTile == "LeaveSky" then
		if self.velocity.x > moonGravity or self.velocity.x < moonGravity then
			self.velocity.x = - self.velocity.x/2 + moonGravity;
			self.health = self.health - self.velocity.x/2;
		else
			self.velocity.x = 0;
		end
	end
	-- IS IT A FLIPSCREEN? =================================================================================================
	if belowTile == "LeaveDown" then
		self.position.y = 20;
		self.moonPosition.y = self.moonPosition.y + 1;
		renderRoom( self.moonPosition.x, self.moonPosition.y );
	elseif aboveTile == "LeaveUp" then
		self.position.y = 150;
		self.moonPosition.y = self.moonPosition.y - 1;
		renderRoom( self.moonPosition.x, self.moonPosition.y );
	elseif rightTile == "LeaveRight" then
		self.position.x = 34;
		self.moonPosition.x = self.moonPosition.x + 1;
		renderRoom( self.moonPosition.x, self.moonPosition.y );
	elseif leftTile == "LeaveLeft" then
		self.position.x = 320 - 34;
		self.moonPosition.x = self.moonPosition.x - 1;
		renderRoom( self.moonPosition.x, self.moonPosition.y );
	end
end

