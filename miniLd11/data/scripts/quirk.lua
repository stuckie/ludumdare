local QuirkNum = 0;

QuirkClass = {}
QuirkClass.__index = QuirkClass

function QuirkClass.create( colR, colG, colB, posX, posY, posZ )
	local quirk = {};
	setmetatable(quirk,QuirkClass);
   
	QuirkNum = QuirkNum + 1;
	local CurrentEntity = "Quirk." .. QuirkNum;

	EntityMan:add2DEntity(CurrentEntity);
	EntityMan:createAnimation(CurrentEntity, "idle");
	EntityMan:loadFrame(CurrentEntity, "idle", "Sprites", "Sprites", 250, 0, 0, 255, 0, 255);
	
	EntityMan:createAnimation(CurrentEntity, "fall");
	EntityMan:loadFrame(CurrentEntity, "fall", "Sprites", "Sprites", 250, 192, 0, 255, 0, 255);
	
	EntityMan:createAnimation(CurrentEntity, "splat");
	EntityMan:loadFrame(CurrentEntity, "splat", "Sprites", "Sprites", 250, 208, 0, 255, 0, 255);
	EntityMan:loadFrame(CurrentEntity, "splat", "Sprites", "Sprites", 250, 224, 0, 255, 0, 255);
	
	EntityMan:createAnimation(CurrentEntity, "walk.Left");
	EntityMan:loadFrame(CurrentEntity, "walk.Left", "Sprites", "Sprites", 250, 0, 0, 255, 0, 255);
	EntityMan:loadFrame(CurrentEntity, "walk.Left", "Sprites", "Sprites", 250, 16, 0, 255, 0, 255);
	
	EntityMan:createAnimation(CurrentEntity, "walk.UpLeft");
	EntityMan:loadFrame(CurrentEntity, "walk.UpLeft", "Sprites", "Sprites", 250, 0, 0, 255, 0, 255);
	EntityMan:loadFrame(CurrentEntity, "walk.UpLeft", "Sprites", "Sprites", 250, 16, 0, 255, 0, 255);
	
	EntityMan:createAnimation(CurrentEntity, "walk.Right");
	EntityMan:loadFrame(CurrentEntity, "walk.Right", "Sprites", "Sprites", 250, 32, 0, 255, 0, 255);
	EntityMan:loadFrame(CurrentEntity, "walk.Right", "Sprites", "Sprites", 250, 48, 0, 255, 0, 255);
	
	EntityMan:createAnimation(CurrentEntity, "walk.UpRight");
	EntityMan:loadFrame(CurrentEntity, "walk.UpRight", "Sprites", "Sprites", 250, 32, 0, 255, 0, 255);
	EntityMan:loadFrame(CurrentEntity, "walk.UpRight", "Sprites", "Sprites", 250, 48, 0, 255, 0, 255);
	
	EntityMan:createAnimation(CurrentEntity, "walk.RightUp");
	EntityMan:loadFrame(CurrentEntity, "walk.RightUp", "Sprites", "Sprites", 250, 64, 0, 255, 0, 255);
	EntityMan:loadFrame(CurrentEntity, "walk.RightUp", "Sprites", "Sprites", 250, 80, 0, 255, 0, 255);
	
	EntityMan:createAnimation(CurrentEntity, "walk.RightDown");
	EntityMan:loadFrame(CurrentEntity, "walk.RightDown", "Sprites", "Sprites", 250, 96, 0, 255, 0, 255);
	EntityMan:loadFrame(CurrentEntity, "walk.RightDown", "Sprites", "Sprites", 250, 112, 0, 255, 0, 255);
	
	EntityMan:createAnimation(CurrentEntity, "walk.LeftDown");
	EntityMan:loadFrame(CurrentEntity, "walk.LeftDown", "Sprites", "Sprites", 250, 0, 16, 255, 0, 255);
	EntityMan:loadFrame(CurrentEntity, "walk.LeftDown", "Sprites", "Sprites", 250, 16, 16, 255, 0, 255);
	
	EntityMan:createAnimation(CurrentEntity, "walk.LeftUp");
	EntityMan:loadFrame(CurrentEntity, "walk.LeftUp", "Sprites", "Sprites", 250, 32, 16, 255, 0, 255);
	EntityMan:loadFrame(CurrentEntity, "walk.LeftUp", "Sprites", "Sprites", 250, 48, 16, 255, 0, 255);
	
	EntityMan:createAnimation(CurrentEntity, "walk.DownRight");
	EntityMan:loadFrame(CurrentEntity, "walk.DownRight", "Sprites", "Sprites", 250, 128, 0, 255, 0, 255);
	EntityMan:loadFrame(CurrentEntity, "walk.DownRight", "Sprites", "Sprites", 250, 144, 0, 255, 0, 255);
	
	EntityMan:createAnimation(CurrentEntity, "walk.DownLeft");
	EntityMan:loadFrame(CurrentEntity, "walk.DownLeft", "Sprites", "Sprites", 250, 160, 0, 255, 0, 255);
	EntityMan:loadFrame(CurrentEntity, "walk.DownLeft", "Sprites", "Sprites", 250, 176, 0, 255, 0, 255);
	
	EntityMan:setAnimation(CurrentEntity, "walk.Left");
	EntityMan:changeColour( CurrentEntity, 0, 0, 255, colR, colG, colB );
	EntityMan:setDimensions(CurrentEntity, 16, 16, 0);
	EntityMan:moveTo(CurrentEntity, posX, posY, posZ);
	
	quirk.name = CurrentEntity;
	quirk.direction = "Left";
	quirk.orientation = "Up";
	quirk.state = "walk";
	quirk.position = { x = posX, y = posY, z = posZ };
	quirk.speed = 0.1;
	quirk.fallCount = 0;
   
	return quirk;
end

function QuirkClass:render()
	EntityMan:moveTo(self.name, self.position.x, self.position.y, self.position.z);
end

function QuirkClass:update()
	if self.state == "walk" then
		if self.direction == "Left" then
			self.position.x = self.position.x - self.speed;
		elseif self.direction == "Right" then
			self.position.x = self.position.x + self.speed;
		elseif self.direction == "RightUp" or self.direction == "LeftUp" then
			self.position.y = self.position.y - self.speed;
		elseif self.direction == "RightDown" or self.direction == "LeftDown" then
			self.position.y = self.position.y + self.speed;
		elseif self.direction == "UpLeft" then
			self.position.y = self.position.y - self.speed / 2;
			self.position.x = self.position.x - self.speed / 2;
		elseif self.direction == "UpRight" then
			self.position.y = self.position.y - self.speed / 2;
			self.position.x = self.position.x + self.speed / 2;
		elseif self.direction == "DownLeft" then
			self.position.y = self.position.y + self.speed / 2;
			self.position.x = self.position.x - self.speed / 2;
		elseif self.direction == "DownRight" then
			self.position.y = self.position.y + self.speed / 2;
			self.position.x = self.position.x + self.speed / 2;
		end
	elseif self.state == "fall" then
		self.position.y = self.position.y + 0.98;
		self.fallCount = self.fallCount + 1;
		self.orientation = "Up";
	end
	
	self:checkTile();
	
	self:render();
end

function QuirkClass:swapDirection()
	if self.direction == "Left" then
		self.direction = "Right";
		self:changeState("walk");
	elseif self.direction == "Right" then
		self.direction = "Left";
		self:changeState("walk");
	elseif self.direction == "RightUp" then
		self.direction = "RightDown";
		self:changeState("walk");
	elseif self.direction == "RightDown" then
		self.direction = "RightUp";
		self:changeState("walk");
	elseif self.direction == "LeftUp" then
		self.direction = "LeftDown";
		self:changeState("walk");
	elseif self.direction == "LeftDown" then
		self.direction = "LeftUp";
		self:changeState("walk");
	elseif self.direction == "UpLeft" then
		self.direction = "DownRight";
		self:changeState("walk");
	elseif self.direction == "UpRight" then
		self.direction = "DownLeft";
		self:changeState("walk");
	elseif self.direction == "DownLeft" then
		self.direction = "UpRight";
		self:changeState("walk");
	elseif self.direction == "DownRight" then
		self.direction = "UpLeft";
		self:changeState("walk");
	end
end

function QuirkClass:setDirection( newDirection )
	local oldDirection = self.direction;
	
	self.direction = newDirection;
	self:changeState( "walk" );

end

function QuirkClass:changeState( state )
	local previousState = self.state;
	
	if state == "idle" then
		self.state = "idle";
		EntityMan:setAnimation(self.name, "idle." .. self.direction);
	elseif state == "walk" then
		self.state = "walk";
		if self.orientation == "Up" then
			if self.direction == "DownLeft" then
				EntityMan:setAnimation(self.name, "walk.Left");
			elseif self.direction == "DownRight" then
				EntityMan:setAnimation(self.name, "walk.Right");
			else
				EntityMan:setAnimation(self.name, "walk." .. self.direction);
			end
		elseif self.orientation == "Down" then
			if self.direction == "UpRight" or self.direction == "Right" or self.direction == "DownRight" then
				EntityMan:setAnimation(self.name, "walk.DownRight");
			elseif self.direction == "UpLeft" or self.direction == "Left" or self.direction == "DownLeft" then
				EntityMan:setAnimation(self.name, "walk.DownLeft");
			elseif self.direction == "RightDown" then
				EntityMan:setAnimation(self.name, "walk.RightDown");
			elseif self.direction == "RightUp" then
				EntityMan:setAnimation(self.name, "walk.RightUp");
			elseif self.direction == "LeftDown" then
				EntityMan:setAnimation(self.name, "walk.LeftDown");
			elseif self.direction == "LeftUp" then
				EntityMan:setAnimation(self.name, "walk.LeftUp");
			end
		end
	elseif state == "fall" then
		self.state = "fall";
		EntityMan:setAnimation(self.name, "fall");
	end
end

function QuirkClass:checkTile()
	if self.state == "walk" then
		if self.direction == "Left" then
			local tileType = LevelMan:getTileType( ( self.position.x + 8 ) / 16, self.position.y / 16, 0 );
			local belowTileType = LevelMan:getTileType( (self.position.x + 16 )/ 16, (self.position.y + 16) / 16, 0 );
			if tileType == "Solid" or tileType == "DownRight" or tileType == "UpRight" then
				self:swapDirection();
			elseif tileType == "UpLeft" then
				self:setDirection("UpLeft");
			elseif tileType == "DownLeft" then
				self:setDirection("DownLeft");
			elseif belowTileType == "UpRight" then
				self:setDirection("DownLeft");
			end
			if self.orientation == "Up" then
				if LevelMan:getTileType( ( self.position.x + 8 ) / 16, ( self.position.y + 16 ) / 16 , 0) == "none" then
					self:changeState("fall");
				end
			elseif self.orientation == "Down" then
				if LevelMan:getTileType( ( self.position.x + 8 ) / 16, ( self.position.y - 8 ) / 16, 0 ) == "none" then
					self:changeState("fall");
				end
			end
		elseif self.direction == "UpLeft" then
			local aboveTileType = LevelMan:getTileType( self.position.x / 16, (self.position.y - 1) / 16, 0 );
			local leftTileType = LevelMan:getTileType( (self.position.x - 1) / 16, self.position.y / 16, 0 );
			local belowTileType = LevelMan:getTileType( self.position.x/ 16, (self.position.y + 15) / 16, 0 );
			if leftTileType == "Solid" then
				self:setDirection("RightUp");
			elseif aboveTileType == "UpRight" then
				self:swapDirection();
			elseif aboveTileType == "Solid" then
				self:setDirection("Left");
			elseif self.orientation == "Up" and belowTileType == "none" then
				self:setDirection("Left");
			end
		elseif self.direction == "RightUp" then
			local tileType = LevelMan:getTileType( self.position.x / 16, self.position.y / 16, 0 );
			if tileType == "Solid" then
				self:swapDirection();
			elseif tileType == "DownLeft" then
				self.orientation = "Down";
				self:setDirection("UpRight");
			elseif tileType == "UpLeft" then
				self.orientation = "Down";
				self:setDirection("DownRight");
			end
		elseif self.direction == "UpRight" then
			if self.orientation == "Down" then
				local aboveTileType = LevelMan:getTileType( self.position.x / 16, (self.position.y - 1) / 16, 0 );
				local rightTileType = LevelMan:getTileType( (self.position.x + 1) / 16, self.position.y / 16, 0 );
				if rightTileType == "Solid" then
					self:swapDirection();
				elseif aboveTileType == "Solid" then
					self:setDirection("Right");
				end
			elseif self.orientation == "Up" then
				local rightTileType = LevelMan:getTileType( (self.position.x + 16) / 16, self.position.y / 16, 0 );
				local belowTileType = LevelMan:getTileType( (self.position.x + 16 )/ 16, (self.position.y + 15) / 16, 0 );
				if rightTileType == "Solid" then
					self:setDirection("LeftUp");
				elseif belowTileType == "none" then
					self:setDirection("Right");
				end
			end
		elseif self.direction == "Right" then
			local rightTileType = LevelMan:getTileType( (self.position.x + 8 ) / 16, (self.position.y + 8 ) / 16, 0);
			local belowTileType = LevelMan:getTileType( (self.position.x + 16 ) / 16, (self.position.y + 16 ) / 16, 0);
			if rightTileType == "Solid" or rightTileType == "UpLeft" then
				self:swapDirection();
			elseif rightTileType == "DownRight" or belowTileType == "UpLeft" then
				self:setDirection("DownRight");
			elseif rightTileType == "UpRight" then
				self:setDirection("UpRight");
			end
			if self.orientation == "Up" then
				if LevelMan:getTileType( ( self.position.x + 8 ) / 16, ( self.position.y + 16 ) / 16 , 0) == "none" then
					self:changeState("fall");
				end
			elseif self.orientation == "Down" then
				if LevelMan:getTileType( ( self.position.x + 8 ) / 16, ( self.position.y - 8 ) / 16, 0 ) == "none" then
					self:changeState("fall");
				end
			end
		elseif self.direction == "LeftDown" then
			local tileType = LevelMan:getTileType( self.position.x / 16, (self.position.y / 16) + 1, 0 );
			if tileType == "Solid" then
				self:swapDirection();
			elseif tileType == "UpRight" then
				self.orientation = "Up";
				self:setDirection("DownLeft");
			end
		elseif self.direction == "RightDown" then
			local tileType = LevelMan:getTileType( (self.position.x + 8 ) / 16, (self.position.y + 8) / 16, 0 );
			if tileType == "Solid" then
				self:swapDirection();
			elseif tileType == "UpLeft" then
				self.orientation = "Up";
				self:setDirection("DownRight");
			end
		elseif self.direction == "LeftUp" then
			local tileType = LevelMan:getTileType( (self.position.x + 8 )/ 16, ( self.position.y ) / 16, 0 );
			if tileType == "Solid" then
				self:swapDirection();
			elseif tileType == "DownLeft" then
				self.orientation = "Down";
				self:setDirection("UpRight");
			elseif tileType == "UpLeft" then
				self.orientation = "Down";
				self:setDirection("DownRight");
			elseif tileType == "DownRight" then
				self.orientation = "Down";
				self:setDirection("UpLeft");
			end
		elseif self.direction == "DownRight" then
			local downTileType = LevelMan:getTileType( self.position.x / 16, (self.position.y + 14) / 16, 0 );
			local rightTileType = LevelMan:getTileType( (self.position.x + 16) / 16, self.position.y / 16, 0 );
			if downTileType == "Solid" then
				self:setDirection("Right");
			elseif rightTileType == "Solid" then
				self:setDirection("LeftDown");
			end
			if self.orientation == "Down" then
				if LevelMan:getTileType( (self.position.x + 8 ) / 16, ( self.position.y) / 16, 0 ) == "none" then
					self:changeState("fall");
				end
			end
		elseif self.direction == "DownLeft" then
			local downTileType = LevelMan:getTileType( ( self.position.x + 8 ) / 16, (self.position.y + 16) / 16, 0 );
			local leftTileType = LevelMan:getTileType( ( self.position.x )/ 16, ( self.position.y + 8 )/ 16, 0 );
			if downTileType == "Solid" then
				self:setDirection("Left");
			elseif leftTileType == "Solid" then
				self:setDirection("RightDown");
			end
			if self.orientation == "Down" then
				if LevelMan:getTileType( ( self.position.x ) / 16, ( self.position.y ) / 16, 0 ) == "none" then
					self:changeState("fall");
				end
			end
		end
	elseif self.state == "fall" then
		local fallTile = LevelMan:getTileType( (self.position.x + 8 ) / 16, (self.position.y + 16 )/ 16, 0 )
		if fallTile == "Solid" then
			self:changeState("walk");
		elseif fallTile ~= "none" and fallTile ~= "Solid" then
			self:setDirection(fallTile)
		end
	end
end
