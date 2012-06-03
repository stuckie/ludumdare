-- Chronos - Moon of Time ( or lack therof )
--------------------------------------------

moonWidth = 4;
moonHeight = 4;
roomWidth = 20;
roomHeight = 12;
moonLevels = 5;
moonGravity = 0.01;
totalResearchers = 0;

local enemyBases = {};
local researchBases = {};

function setupMoon01()
	moonGravity = 0.08;
	totalResearchers = 5;
	enemyBases = {};
	researchBases = {};
	
	for y=0,moonHeight do
		researchBases[y] = {};
		for x=0,moonWidth do
			researchBases[y][x] = nil;
		end
	end
	
	for y=0,moonHeight do
		enemyBases[y] = {};
		for x=0,moonWidth do
			enemyBases[y][x] = List:new();
		end
	end

	enemyBases[0][0]:append({ 	basePosition = { y = 9*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 100,
					baseRespawn = 25,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					width = 32, height = 32,
					offsetX = 0, offsetY = -16,
					baseEnemy = { path = "DropUpLeft", u = 32, v = 16, speed = 0.2, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[0][1]:append({ 	basePosition = { y = 9*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 50,
					baseRespawn = 17,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					width = 32, height = 32,
					offsetX = 0, offsetY = -16,
					baseEnemy = { path = "SinLeft", u = 16, v = 16, speed = 0.2, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[1][0]:append({ 	basePosition = { y = 9*16, x = 2*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					width = 32, height = 32,
					offsetX = 0, offsetY = -16,
 					baseEnemy = { path = "SinRight", u = 16, v = 16, speed = 0.25, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[1][0]:append({ 	basePosition = { y = 9*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					width = 32, height = 32,
					offsetX = 0, offsetY = -16,
 					baseEnemy = { path = "SinLeft", u = 0, v = 16, speed = 0.25, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][2]:append({ 	basePosition = { y = 6*16, x = 8*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 25,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					width = 32, height = 32,
					offsetX = 0, offsetY = -16,
 					baseEnemy = { path = "DropUpRight", u = 80, v = 16, speed = 0.05, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[2][3]:append({ 	basePosition = { y = 1*16, x = 14*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					width = 32, height = 32,
					offsetX = 0, offsetY = 16,
 					baseEnemy = { path = "DropDownLeft", u = 64, v = 16, speed = 0.5, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[0][2]:append({ 	basePosition = { y = 9*16, x = 2*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					width = 32, height = 32,
					offsetX = 32, offsetY = 8,
 					baseEnemy = { path = "SinRight", u = 16, v = 16, speed = 0.5, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[0][2]:append({ 	basePosition = { y = 1*16, x = 14*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					width = 32, height = 32,
					offsetX = 0, offsetY = 16,
 					baseEnemy = { path = "DropDownLeft", u = 64, v = 16, speed = 0.75, health = 1.0, score = 10, time = os.clock() }
	});

	researchBases[0][1] = {	room = { y = 0, x = 1 },
				position = { y=10*16, x = 2*16 },
				researchers = 2,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[2][0] = {	room = { y = 2, x = 0 },
				position = { y=10*16, x = 5*16 },
				researchers = 2,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[0][2] = {	room = { y = 0, x = 2 },
				position = { y=10*16, x = 18*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

end

function setupMoon02()
	moonGravity = 0.06;
	totalResearchers = 5;
	enemyBases = {};
	researchBases = {};
	
	for y=0,moonHeight do
		researchBases[y] = {};
		for x=0,moonWidth do
			researchBases[y][x] = nil;
		end
	end
	
	for y=0,moonHeight do
		enemyBases[y] = {};
		for x=0,moonWidth do
			enemyBases[y][x] = List:new();
		end
	end

	enemyBases[2][1]:append({ 	basePosition = { y = 7*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 100,
					baseRespawn = 25,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
					baseEnemy = { path = "Left", u = 32, v = 16, speed = 0.5, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][0]:append({ 	basePosition = { y = 1*16, x = 3*16 },
					baseHealth = 50,
					baseCounter = 50,
					baseRespawn = 17,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					offsetX = 0, offsetY = 16,
					width = 32, height = 32,
					baseEnemy = { path = "DropDownRight", u = 16, v = 16, speed = 0.2, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[1][0]:append({ 	basePosition = { y = 9*16, x = 2*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
 					baseEnemy = { path = "SinRight", u = 16, v = 16, speed = 0.25, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[1][0]:append({ 	basePosition = { y = 9*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
 					baseEnemy = { path = "SinLeft", u = 0, v = 16, speed = 0.25, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][2]:append({ 	basePosition = { y = 7*16, x = 11*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 25,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
 					baseEnemy = { path = "DropUpLeft", u = 64, v = 16, speed = 0.05, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[1][3]:append({ 	basePosition = { y = 1*16, x = 14*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					offsetX = 0, offsetY = 16,
					width = 32, height = 32,
 					baseEnemy = { path = "DropDownLeft", u = 64, v = 16, speed = 0.5, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[0][2]:append({ 	basePosition = { y = 9*16, x = 2*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 32, offsetY = 8,
					width = 32, height = 32,
 					baseEnemy = { path = "Right", u = 16, v = 16, speed = 0.5, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[0][2]:append({ 	basePosition = { y = 1*16, x = 2*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					offsetX = 0, offsetY = 16,
					width = 32, height = 32,
 					baseEnemy = { path = "DropDownRight", u = 80, v = 16, speed = 1.0, health = 1.0, score = 10, time = os.clock() }
	});

	researchBases[2][0] = {	room = { y = 2, x = 0 },
				position = { y=10*16, x = 5*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[0][2] = {	room = { y = 0, x = 2 },
				position = { y=10*16, x = 18*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[3][3] = {	room = { y = 3, x = 3 },
				position = { y=10*16, x = 15*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[3][0] = {	room = { y = 3, x = 0 },
				position = { y=10*16, x = 2*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[2][2] = {	room = { y = 2, x = 2 },
				position = { y=10*16, x = 2*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};
end

function setupMoon03()
	moonGravity = 0.05;
	totalResearchers = 5;
	enemyBases = {};
	researchBases = {};
	
	for y=0,moonHeight do
		researchBases[y] = {};
		for x=0,moonWidth do
			researchBases[y][x] = nil;
		end
	end
	
	for y=0,moonHeight do
		enemyBases[y] = {};
		for x=0,moonWidth do
			enemyBases[y][x] = List:new();
		end
	end

	enemyBases[2][1]:append({ 	basePosition = { y = 7*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 100,
					baseRespawn = 25,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
					baseEnemy = { path = "SinLeft", u = 32, v = 16, speed = 0.5, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][0]:append({ 	basePosition = { y = 1*16, x = 3*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					offsetX = 0, offsetY = 16,
					width = 32, height = 32,
					baseEnemy = { path = "DropDownRight", u = 16, v = 16, speed = 0.2, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][0]:append({ 	basePosition = { y = 9*16, x = 2*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
 					baseEnemy = { path = "SinRight", u = 16, v = 16, speed = 0.25, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][0]:append({ 	basePosition = { y = 9*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
 					baseEnemy = { path = "SinLeft", u = 0, v = 16, speed = 0.25, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][2]:append({ 	basePosition = { y = 7*16, x = 11*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 10,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
 					baseEnemy = { path = "DropUpLeft", u = 64, v = 16, speed = 0.05, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[1][3]:append({ 	basePosition = { y = 1*16, x = 14*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					offsetX = 0, offsetY = 16,
					width = 32, height = 32,
 					baseEnemy = { path = "DropDownLeft", u = 64, v = 16, speed = 0.5, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[0][3]:append({ 	basePosition = { y = 9*16, x = 2*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 32, offsetY = 8,
					width = 32, height = 32,
 					baseEnemy = { path = "Right", u = 16, v = 16, speed = 0.5, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[0][3]:append({ 	basePosition = { y = 1*16, x = 2*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					offsetX = 0, offsetY = 16,
					width = 32, height = 32,
 					baseEnemy = { path = "DropDownRight", u = 80, v = 16, speed = 1.0, health = 1.0, score = 10, time = os.clock() }
	});

	researchBases[2][0] = {	room = { y = 2, x = 0 },
				position = { y=10*16, x = 5*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[0][3] = {	room = { y = 0, x = 3 },
				position = { y=10*16, x = 18*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[3][3] = {	room = { y = 3, x = 3 },
				position = { y=10*16, x = 15*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[3][0] = {	room = { y = 3, x = 0 },
				position = { y=10*16, x = 8*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[2][3] = {	room = { y = 2, x = 3 },
				position = { y=10*16, x = 2*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};
end

function setupMoon04()
	moonGravity = 0.06;
	totalResearchers = 5;
	enemyBases = {};
	researchBases = {};
	
	for y=0,moonHeight do
		researchBases[y] = {};
		for x=0,moonWidth do
			researchBases[y][x] = nil;
		end
	end
	
	for y=0,moonHeight do
		enemyBases[y] = {};
		for x=0,moonWidth do
			enemyBases[y][x] = List:new();
		end
	end

	enemyBases[2][1]:append({ 	basePosition = { y = 9*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 40,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
					baseEnemy = { path = "SinLeft", u = 32, v = 16, speed = 0.3, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][0]:append({ 	basePosition = { y = 1*16, x = 3*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					offsetX = 0, offsetY = 16,
					width = 32, height = 32,
					baseEnemy = { path = "DropDownRight", u = 16, v = 16, speed = 0.2, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][0]:append({ 	basePosition = { y = 9*16, x = 2*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
 					baseEnemy = { path = "SinRight", u = 16, v = 16, speed = 0.25, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][0]:append({ 	basePosition = { y = 9*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
 					baseEnemy = { path = "SinLeft", u = 0, v = 16, speed = 0.25, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][2]:append({ 	basePosition = { y = 7*16, x = 15*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 10,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = -4, offsetY = 0,
					width = 32, height = 32,
 					baseEnemy = { path = "SinLeft", u = 64, v = 16, speed = 0.75, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[1][3]:append({ 	basePosition = { y = 1*16, x = 14*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					offsetX = 0, offsetY = 16,
					width = 32, height = 32,
 					baseEnemy = { path = "DropDownLeft", u = 64, v = 16, speed = 0.5, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[0][3]:append({ 	basePosition = { y = 9*16, x = 2*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 32, offsetY = 8,
					width = 32, height = 32,
 					baseEnemy = { path = "Right", u = 16, v = 16, speed = 0.5, health = 1.0, score = 10, time = os.clock() }
	});

	researchBases[2][1] = {	room = { y = 2, x = 1 },
				position = { y=10*16, x = 5*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[3][3] = {	room = { y = 3, x = 3 },
				position = { y=10*16, x = 15*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[3][0] = {	room = { y = 3, x = 0 },
				position = { y=10*16, x = 8*16 },
				researchers = 2,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[2][3] = {	room = { y = 2, x = 3 },
				position = { y=10*16, x = 2*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};
end

function setupMoon05()
	moonGravity = 0.07;
	totalResearchers = 5;
	enemyBases = {};
	researchBases = {};
	
	for y=0,moonHeight do
		researchBases[y] = {};
		for x=0,moonWidth do
			researchBases[y][x] = nil;
		end
	end
	
	for y=0,moonHeight do
		enemyBases[y] = {};
		for x=0,moonWidth do
			enemyBases[y][x] = List:new();
		end
	end

	enemyBases[3][1]:append({ 	basePosition = { y = 9*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 100,
					baseRespawn = 25,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
					baseEnemy = { path = "SinLeft", u = 32, v = 16, speed = 0.5, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][0]:append({ 	basePosition = { y = 1*16, x = 3*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					offsetX = 0, offsetY = 20,
					width = 32, height = 32,
					baseEnemy = { path = "DropDownRight", u = 16, v = 16, speed = 1.5, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][0]:append({ 	basePosition = { y = 9*16, x = 2*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
 					baseEnemy = { path = "SinRight", u = 16, v = 16, speed = 2.0, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[2][0]:append({ 	basePosition = { y = 9*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
 					baseEnemy = { path = "SinLeft", u = 0, v = 16, speed = 2.0, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][2]:append({ 	basePosition = { y = 9*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 10,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 0, offsetY = -16,
					width = 32, height = 32,
 					baseEnemy = { path = "SinLeft", u = 64, v = 16, speed = 2.1, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[3][3]:append({ 	basePosition = { y = 1*16, x = 14*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					offsetX = 0, offsetY = 16,
					width = 32, height = 32,
 					baseEnemy = { path = "DropDownLeft", u = 64, v = 16, speed = 0.25, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[0][3]:append({ 	basePosition = { y = 9*16, x = 2*16 },
					baseHealth = 50,
					baseCounter = 25,
					baseRespawn = 15,
					aliveU = 0, deadU = 32,
					aliveV = 224, deadV = 224,
					offsetX = 32, offsetY = 8,
					width = 32, height = 32,
 					baseEnemy = { path = "Right", u = 16, v = 16, speed = 0.5, health = 1.0, score = 10, time = os.clock() }
	});

	enemyBases[0][3]:append({ 	basePosition = { y = 1*16, x = 17*16 },
					baseHealth = 50,
					baseCounter = 20,
					baseRespawn = 10,
					aliveU = 0, deadU = 32,
					aliveV = 192, deadV = 192,
					offsetX = 0, offsetY = 16,
					width = 32, height = 32,
 					baseEnemy = { path = "DropDownLeft", u = 64, v = 16, speed = 3.0, health = 1.0, score = 10, time = os.clock() }
	});

	researchBases[2][0] = {	room = { y = 2, x = 0 },
				position = { y=10*16, x = 5*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[0][3] = {	room = { y = 0, x = 3 },
				position = { y=10*16, x = 18*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[3][3] = {	room = { y = 3, x = 3 },
				position = { y=10*16, x = 15*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[3][0] = {	room = { y = 3, x = 0 },
				position = { y=10*16, x = 8*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};

	researchBases[3][2] = {	room = { y = 3, x = 2 },
				position = { y=10*16, x = 2*16 },
				researchers = 1,
				activeU = 240,
				activeV = 112,
				inactiveU = 240,
				inactiveV = 128
	};
end

function moon01()
	updateEnemyBases(enemyBases[Player.moonPosition.y][Player.moonPosition.x]);
	updateResearchBases(researchBases[Player.moonPosition.y][Player.moonPosition.x]);
end

function moon02()
	updateEnemyBases(enemyBases[Player.moonPosition.y][Player.moonPosition.x]);
	updateResearchBases(researchBases[Player.moonPosition.y][Player.moonPosition.x]);
end

function moon03()
	updateEnemyBases(enemyBases[Player.moonPosition.y][Player.moonPosition.x]);
	updateResearchBases(researchBases[Player.moonPosition.y][Player.moonPosition.x]);
end

function moon04()
	updateEnemyBases(enemyBases[Player.moonPosition.y][Player.moonPosition.x]);
	updateResearchBases(researchBases[Player.moonPosition.y][Player.moonPosition.x]);
end

function moon05()
	updateEnemyBases(enemyBases[Player.moonPosition.y][Player.moonPosition.x]);
	updateResearchBases(researchBases[Player.moonPosition.y][Player.moonPosition.x]);
end

function getResearchBase ( x, y )
	return researchBases[y][x];
end
