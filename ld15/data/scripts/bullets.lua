-- We don't want to pollute the engine's entity stack with bullets, so this is cheeky!

bulletList = List:new();

function addBullet ( pX, pY, pDirection, pType )
	if pType == "Player" then
		pU = 0;
		pV = 32;
	elseif pType == "Enemy" then
		pU = 32;
		pV = 32;
	end

	local pPosition = { x = pX, y = pY };
	bulletList:append({position = pPosition, direction = pDirection, u = pU, v = pV, w = 16, h = 16 });
end

function updateBullets()
	for i,bullet in ipairs(bulletList) do
		TextureMan:blitTexture("LevelData", bullet.position.x, bullet.position.y, 0, bullet.u, bullet.v, bullet.w, bullet.h);
		if bullet.direction == "Left" then
			bullet.position.x = bullet.position.x - 10.0;
		elseif bullet.direction == "Right" then
			bullet.position.x = bullet.position.x + 10.0;
		end

		if bullet.position.x < -16 or bullet.position.x > 336 or checkBulletAgainstTile(bullet.position) == true then
			bulletList:remove(bullet);
			return;
		end
	end
end

function checkAgainstBullets( posX, posY, width, height )
	for i,bullet in ipairs(bulletList) do
		local left1 = bullet.position.x;
		local left2 = posX;
		local right1 = bullet.position.x + width;
		local right2 = posX + width;
		local top1 = bullet.position.y;
		local top2 = posY;
		local bottom1 = bullet.position.y + height;
		local bottom2 = posY + height;

		if bottom1 > top2 and top1 < bottom2 and right1 > left2 and left1 < right2 then
			addEntity( bullet.position.x, bullet.position.y, "Explosion", 16, 32, 0, 1.0, 0, 1.0 );
			AudioMan:playSFX("Explosion");
			bulletList:remove(bullet);
			return true;
		end
	end

	return false;
end

function checkBulletAgainstTile( position )
	local leftTile = LevelMan:getTileType( position.x / 16, position.y / 16, 1 );
	local rightTile = LevelMan:getTileType( (position.x / 16) + 1, position.y / 16, 1 );
	
	if rightTile == "Solid" or rightTile == "ResearchLand" or rightTile == "ResearchLeft" or rightTile == "ResearchMid"  or rightTile == "ResearchRight" then
		addEntity( position.x, position.y, "Explosion", 16, 32, 0, 1.0, 0, 1.0 );
		return true;
	end
	if leftTile == "Solid" or leftTile == "ResearchLand" or leftTile == "ResearchLeft" or leftTile == "ResearchMid"  or leftTile == "ResearchRight" then
		addEntity( position.x, position.y, "Explosion", 16, 32, 0, 1.0, 0, 1.0 );
		return true;
	end

	return false;
end
