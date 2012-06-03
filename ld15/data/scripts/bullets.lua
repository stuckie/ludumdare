-- We don't want to pollute the engine's entity stack with bullets, so this is cheeky!

local bulletList = List:new();

function addBullet ( pX, pY, pDirection, pType )
	local pU = 0;
	local pV = 0;
	if pType == "Player" then
		pU = 0;
		pV = 32;
	end
	bulletList:append({x = pX, y = pY, direction = pDirection, u = pU, v = pV, w = 16, h = 16 });
end

function updateBullets()
	for i,bullet in ipairs(bulletList) do
		TextureMan:blitTexture("LevelData", bullet.x, bullet.y, 0, bullet.u, bullet.v, bullet.w, bullet.h);
		if bullet.direction == "Left" then
			bullet.x = bullet.x - 1.0;
		elseif bullet.direction == "Right" then
			bullet.x = bullet.x + 1.0;
		end

		if bullet.x < -16 or bullet.x > 336 then
			bulletList:remove(bullet);
		end
	end
end

function checkAgainstBullets( posX, posY )
	for i,bullet in ipairs(bulletList) do
		local left1 = bullet.x;
		local left2 = posX;
		local right1 = bullet.x + 16;
		local right2 = posX + 16;
		local top1 = bullet.y;
		local top2 = posY;
		local bottom1 = bullet.y + 16;
		local bottom2 = posY + 16;

		if bottom1 > top2 and top1 < bottom2 and right1 > left2 and left1 < right2 then
			addEntity( bullet.x, bullet.y, "Explosion", 16, 32, 0, 20.0 );
			bulletList:remove(bullet);
			return true;
		end
	end

	return false;
end