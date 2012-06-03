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
	player.maxThrust = 5.0;
	player.speed = 0.1;
	player.buttonDown = false;
	player.health = 100;
	player.lives = 3;
	player.score = 0;
	player.researchersSaved = 0;
	player.cargo = 0;
	player.landed = false;
	player.lastBaseRoom = { x = 0, y = 0 };
	player.lastBasePosition = { x = 3*16, y = 8*16 };

	return player;
end

function PlayerClass:render()
	EntityMan:moveTo(self.name, self.position.x, self.position.y, self.position.z);
	self.velocity.y = self.velocity.y + moonGravity;
	
	if self.velocity.x > self.maxThrust then
		self.velocity.x = self.maxThrust;
	elseif self.velocity.x < -self.maxThrust then
		self.velocity.x = -self.maxThrust;
	end

	if self.velocity.x > 0 then
		self.velocity.x = self.velocity.x - 0.01;
	elseif self.velocity.x < 0 then
		self.velocity.x = self.velocity.x + 0.01;
	end

	if self.velocity.y > self.maxThrust then
		self.velocity.y = self.maxThrust;
	elseif self.velocity.y < -self.maxThrust then
		self.velocity.y = -self.maxThrust;
	end

	self.position.x = self.position.x + self.velocity.x;
	self.position.y = self.position.y + self.velocity.y;
	self:displayLives();
end

function PlayerClass:displayLives()
	for life=1,Player.lives, 1 do 
		TextureMan:blitTexture("LevelData", (life * 16) + ( 300 - (self.lives * 16)), (240-16), 0, 0, 0, 16, 16);
	end
end

function PlayerClass:update()
	if self.lives > 0 then
		self:checkInput();
		self:render();
		self:checkTile();
		if self.health < 0 then
			self.lives = self.lives - 1;
			if self.lives > 0 then
				self.health = 100;
				self.moonPosition.x = self.lastBaseRoom.x;
				self.moonPosition.y = self.lastBaseRoom.y;
				self.position.x = self.lastBasePosition.x;
				self.position.y = self.lastBasePosition.y;
				self.velocity.y = 0;
				self.velocity.x = 0;
				self.cargo = 0;
				renderRoom(self.lastBaseRoom.x, self.lastBaseRoom.y);
			else 
				self.position.x = -16;
				self.position.y = -16;
				EntityMan:moveTo(self.name, self.position.x, self.position.y, self.position.z);
			end
		end
	else
		self.health = 0;
		displayText(120, 80, "GAME OVER");
	end
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
	end
	if ControlMan:getUp() == true then
		self.velocity.y = self.velocity.y - self.speed;
	elseif ControlMan:getDown() == true then
		self.velocity.y = self.velocity.y + self.speed;
	end

	if ControlMan:getZ() == true and self.buttonDown == false then
		if self.direction == "Left" then
			addBullet( self.position.x - 20, self.position.y, "Left", "Player" );
		elseif self.direction == "Right" then
			addBullet( self.position.x + 20, self.position.y, "Right", "Player" );
		end
		AudioMan:playSFX("Fire");
		self.buttonDown = true;
	elseif ControlMan:getX() == true and self.buttonDown == false and self.landed == true then
		if self.cargo > 0 then
			transferResearchers(self.cargo, "Base");
			self.saved = self.cargo;
			self.cargo = 0;
		else
			transferResearchers(1, "Player");
		end
		self.buttonDown = true;
	elseif ControlMan:getReturn() == true and self.buttonDown == false then
		if gamePaused == true then
			gamePaused = false;
		else
			gamePaused = true;
		end
		self.buttonDown = true;	
	elseif ControlMan:getZ() == false and ControlMan:getX() == false and ControlMan:getReturn() == false then
		self.buttonDown = false;
	end

end

function PlayerClass:checkTile()
	local aboveTile = LevelMan:getTileType( (self.position.x + 8 )/ 16, (self.position.y - 1) / 16, 1 );
	local belowTile = LevelMan:getTileType( (self.position.x + 8)/ 16, (self.position.y / 16 ) + 1, 1 );
	local leftTile = LevelMan:getTileType( self.position.x / 16, (self.position.y + 8) / 16, 1 );
	local rightTile = LevelMan:getTileType( (self.position.x / 16) + 1, (self.position.y + 8 ) / 16, 1 );
	-- IS IT SOLID? ========================================================================================================
	if belowTile == "Solid" or belowTile == "ResearchLeft" or belowTile == "ResearchMid"  or belowTile == "ResearchRight" or belowTile == "LeaveSky" or belowTile == "Invis" then
		if self.velocity.y > moonGravity then
			self.velocity.y = - self.velocity.y/2 - (moonGravity + self.speed);
			self.health = self.health + self.velocity.y/2;
		else
			self.velocity.y = -(moonGravity + self.speed*2);
		end
	end
	if belowTile == "ResearchLand" then
		if self.velocity.y > moonGravity then
			self.velocity.y = - self.velocity.y/2 - (moonGravity + self.speed);
			if self.health < 100 then
				AudioMan:playSFX("Health");
				self.health = self.health + 0.5;
			end
		else
			self.velocity.y = -(moonGravity + self.speed);
			if self.health < 100 then
				AudioMan:playSFX("Health");
				self.health = self.health + 0.5;
			end
		end
		self.landed = true;
	else
		self.landed = false;
	end
	if aboveTile == "Solid" or aboveTile == "ResearchLand" or aboveTile == "ResearchLeft" or aboveTile == "ResearchMid"  or aboveTile == "ResearchRight" or aboveTile == "LeaveSky" or aboveTile == "Invis" then
		if self.velocity.y < moonGravity then
			self.velocity.y = - self.velocity.y/2 + (moonGravity + self.speed);
			self.health = self.health - self.velocity.y/2;
		else
			self.velocity.y = (moonGravity + self.speed);
		end
	end
	if (aboveTile == "LeaveSky" or leftTile == "LeaveSky") and totalResearchers == 0 then
		nextLevel();
	end
	if rightTile == "Solid" or rightTile == "ResearchLand" or rightTile == "ResearchLeft" or rightTile == "ResearchMid"  or rightTile == "ResearchRight" or rightTile == "LeaveSky" or rightTile == "Invis" then
		if self.velocity.x > self.speed then
			self.velocity.x = - self.velocity.x/2 + (moonGravity + self.speed)/2;
			self.health = self.health + self.velocity.x/2;
		else
			self.velocity.x = -(moonGravity + self.speed);
		end
	end
	if leftTile == "Solid" or leftTile == "ResearchLand" or leftTile == "ResearchLeft" or leftTile == "ResearchMid"  or leftTile == "ResearchRight" or leftTile == "LeaveSky" or leftTile == "Invis" then
		if self.velocity.x < self.speed then
			self.velocity.x = - self.velocity.x/2 + (moonGravity + self.speed)/2;
			self.health = self.health - self.velocity.x/2;
		else
			self.velocity.x = (moonGravity + self.speed);
		end
	end
	-- IS IT A FLIPSCREEN? =================================================================================================
	if belowTile == "LeaveDown" then
		self.position.y = 25;
		self.moonPosition.y = self.moonPosition.y + 1;
		renderRoom( self.moonPosition.x, self.moonPosition.y );
	elseif aboveTile == "LeaveUp" then
		self.position.y = 150;
		self.moonPosition.y = self.moonPosition.y - 1;
		renderRoom( self.moonPosition.x, self.moonPosition.y );
	elseif rightTile == "LeaveRight" then
		self.position.x = 16;
		self.moonPosition.x = self.moonPosition.x + 1;
		renderRoom( self.moonPosition.x, self.moonPosition.y );
	elseif leftTile == "LeaveLeft" then
		self.position.x = 320 - 34;
		self.moonPosition.x = self.moonPosition.x - 1;
		renderRoom( self.moonPosition.x, self.moonPosition.y );
	end
end

function checkAgainstPlayer( posX, posY, width, height )
	local left1 = Player.position.x;
	local left2 = posX;
	local right1 = Player.position.x + width;
	local right2 = posX + width;
	local top1 = Player.position.y;
	local top2 = posY;
	local bottom1 = Player.position.y + height;
	local bottom2 = posY + height;

	if bottom1 > top2 and top1 < bottom2 and right1 > left2 and left1 < right2 then
		return true;
	end

	return false;
end

