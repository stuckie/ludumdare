-- GEvOlve Attacker AI

function AddCircleAttacker()
	if Unit.Total < MaxEntities then
		Current = AddCircle();
		EntityMan:MoveTo(Current, math.random(64)-32, math.random(64)-32, -64);
		EntityMan:NewVar(Current, "Task");
		EntityMan:ChangeVar(Current, "Task", "Attacker");
		EntityMan:NewVar(Current, "Race");
		EntityMan:ChangeVar(Current, "Race", "Circle");
		EntityMan:NewVar(Current, "Status");
		EntityMan:ChangeVar(Current, "Status", "Idle");
		EntityMan:NewVar(Current, "Cooldown");
		EntityMan:ChangeVar(Current, "Cooldown", "10");
		EntityMan:NewVar(Current, "Hunting");
		EntityMan:Colour(Current, 1, 0, 0);
		Entities = { next = Entities, id = Current };
	end
end

function AddSquareAttacker()
	if Unit.Total < MaxEntities then
		Current = AddSquare();
		EntityMan:MoveTo(Current, math.random(64)-32, math.random(64)-32, -64);
		EntityMan:NewVar(Current, "Task");
		EntityMan:ChangeVar(Current, "Task", "Attacker");
		EntityMan:NewVar(Current, "Race");
		EntityMan:ChangeVar(Current, "Race", "Square");
		EntityMan:NewVar(Current, "Status");
		EntityMan:ChangeVar(Current, "Status", "Idle");
		EntityMan:NewVar(Current, "Cooldown");
		EntityMan:ChangeVar(Current, "Cooldown", "10");
		EntityMan:NewVar(Current, "Hunting");
		EntityMan:Colour(Current, 1, 0, 0);
		Entities = { next = Entities, id = Current };
	end
end

function Attacker(MyId)
	-- Find and Attack Opposing Plebs!
	CurrentRace = EntityMan:CheckVar(MyId, "Race");
	if CurrentRace == "Circle" then EnemyRace = "Square"; end
	if CurrentRace == "Square" then EnemyRace = "Circle"; end
	CurrentStatus = EntityMan:CheckVar(MyId, "Status");
	Energy = 0;
	Energy = Energy + EntityMan:CheckVar(MyId, "Health");
	Cooldown = 0;
	Cooldown = Cooldown + EntityMan:CheckVar(MyId, "Cooldown");
	myX = EntityMan:GetX(MyId);
	myY = EntityMan:GetY(MyId);
	myZ = EntityMan:GetZ(MyId);
	if Cooldown > 0 then 
		Cooldown = Cooldown - 1; 
		EntityMan:ChangeVar(MyId, "Cooldown", Cooldown);
	end

	if CurrentStatus == "Idle" then
		local list = Entities;
		while list do
			if EntityMan:CheckExist(list.id) == true then
				if EntityMan:CheckVar(list.id, "Race") == EnemyRace then
					EntityMan:ChangeVar(MyId, "Status", "Hunting");
					EntityMan:ChangeVar(MyId, "Hunting", list.id);
					EntityMan:SetSpeed(MyId, 0.005);
				end
			end
		list = list.next;
		end
	end

	if CurrentStatus == "Hunting" then
		HuntingID = EntityMan:CheckVar(MyId, "Hunting");
		Available = EntityMan:CheckExist(HuntingID);
		if Available == false then 
			EntityMan:ChangeVar(MyId, "Cooldown", 1000);
			EntityMan:ChangeVar(MyId, "Status", "Rest");
		end
		if Available == true then
			EntityMan:LookTo(MyId, EntityMan:GetX(HuntingID), EntityMan:GetY(HuntingID), EntityMan:GetZ(HuntingID));
			if myX >= EntityMan:GetX(HuntingID) - 1 and myX <= EntityMan:GetX(HuntingID) + 1  and myY >= EntityMan:GetY(HuntingID) - 1 and myY <= EntityMan:GetY(HuntingID) + 1 and myZ == EntityMan:GetZ(HuntingID) then
				EntityMan:ChangeVar(MyId, "Cooldown", 1000);
				EntityMan:ChangeVar(HuntingID, "Cooldown", 1000);
				EntityMan:ChangeVar(MyId, "Status", "Rest");
				EnemyEnergy = 0;
				EnemyEnergy = EnemyEnergy + EntityMan:CheckVar(HuntingID, "Health");
				EnemyEnergy = EnemyEnergy - 25;
				EntityMan:ChangeVar(HuntingID, "Health", EnemyEnergy);
				EntityMan:ChangeVar(HuntingID, "Status", "Rest");
			end
		end
	end

	EntityMan:Colour(MyId, Energy/100, 0, 0);

	if CurrentStatus == "Rest" then
		if Cooldown == 0 then EntityMan:ChangeVar(MyId, "Status", "Idle"); end
		EntityMan:LookTo(MyId, math.random(128)-64, math.random(128)-64, -64);
		EntityMan:SetSpeed(MyId, 0.005);
	end

	if Energy <= 0 then 
		Unit.Total = Unit.Total - 1;
		EntityMan:DelEntity(MyId);
	end
end
