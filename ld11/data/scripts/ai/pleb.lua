-- GEvOlve Pleb AI

function AddSquare()
	Unit.Squares = Unit.Squares + 1;
	Unit.Total = Unit.Total + 1;
	local CurrentSquare = "Square." .. Unit.Squares;
	EntityMan:Add2DEntity(CurrentSquare);
	EntityMan:CreateAnimation(CurrentSquare, "idle");
	EntityMan:LoadFrame(CurrentSquare, "idle", "square", "squaremask", 0, 0, 0, 0, 0, 0);
	EntityMan:SetAnimation(CurrentSquare, "idle");
	EntityMan:MoveTo(CurrentSquare, 5, 5, -64);
	EntityMan:Scale(CurrentSquare, 1);
	EntityMan:NewVar(CurrentSquare, "Health");
	EntityMan:ChangeVar(CurrentSquare, "Health", 100);
	EntityMan:NewVar(CurrentSquare, "Task");
	EntityMan:ChangeVar(CurrentSquare, "Task", "Female");
	EntityMan:Colour(CurrentSquare, 1, 0, 1 );
	if math.random(2) == 1 then 
		EntityMan:ChangeVar(CurrentSquare, "Task", "Male"); 
		EntityMan:Colour(CurrentSquare, 0, 0, 1 );
	end
	return CurrentSquare;
end

function AddCircle()
	Unit.Circles = Unit.Circles + 1;
	Unit.Total = Unit.Total + 1;
	local CurrentCircle = "Circle." .. Unit.Circles;
	EntityMan:Add2DEntity(CurrentCircle);
	EntityMan:CreateAnimation(CurrentCircle, "idle");
	EntityMan:LoadFrame(CurrentCircle, "idle", "circle", "circlemask", 0, 0, 0, 0, 0, 0);
	EntityMan:SetAnimation(CurrentCircle, "idle");
	EntityMan:MoveTo(CurrentCircle, -5, -5, -64);
	EntityMan:Scale(CurrentCircle, 1);
	EntityMan:NewVar(CurrentCircle, "Health");
	EntityMan:ChangeVar(CurrentCircle, "Health", 100);
	EntityMan:NewVar(CurrentCircle, "Task");
	EntityMan:ChangeVar(CurrentCircle, "Task", "Female");
	EntityMan:Colour(CurrentCircle, 1, 0, 1 );
	if math.random(2) == 1 then 
		EntityMan:ChangeVar(CurrentCircle, "Task", "Male"); 
		EntityMan:Colour(CurrentCircle, 0, 0, 1 );
	end
	return CurrentCircle;
end

function MalePleb(MyId)
	-- Male Entities seek out Female Entities!
	CurrentRace = EntityMan:CheckVar(MyId, "Race");
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
				if EntityMan:CheckVar(list.id, "Race") == CurrentRace and EntityMan:CheckVar(list.id, "Task") == "Female" and EntityMan:CheckVar(list.id, "Status") == "Idle" then
					EntityMan:ChangeVar(MyId, "Status", "Hunting");
					EntityMan:ChangeVar(MyId, "Hunting", list.id);
					EntityMan:ChangeVar(list.id, "Status", "Hunting");
					EntityMan:ChangeVar(list.id, "Hunting", MyId);
					EntityMan:SetSpeed(MyId, 0.005);
					EntityMan:SetSpeed(list.id, 0.005);
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
				EntityMan:ChangeVar(MyId, "Status", "Mating");
				EntityMan:ChangeVar(HuntingID, "Status", "Mating");
			end
		end
	end

	if CurrentStatus == "Mating" and Cooldown == 0 then
		EntityMan:ChangeVar(MyId, "Cooldown", 100);
		EntityMan:ChangeVar(MyId, "Status", "Rest");
		EntityMan:SetSpeed(MyId, 0);
		Energy = Energy - 10;
		EntityMan:ChangeVar(MyId, "Health", Energy);
	end

	EntityMan:Colour(MyId, 0, 0, Energy/100);

	if CurrentStatus == "Rest" then
		if Cooldown == 0 then EntityMan:ChangeVar(MyId, "Status", "Idle"); end
		EntityMan:LookTo(MyId, math.random(64)-32, math.random(64)-32, -64);
		EntityMan:SetSpeed(MyId, 0.005);
	end

	if Energy <= 0 then 
		Unit.Total = Unit.Total - 1;
		EntityMan:DelEntity(MyId);
	end
end

function FemalePleb(MyId)
	-- Female Entities seek out Male Entities!
	CurrentRace = EntityMan:CheckVar(MyId, "Race");
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
				if EntityMan:CheckVar(list.id, "Race") == CurrentRace and EntityMan:CheckVar(list.id, "Task") == "Male" and EntityMan:CheckVar(list.id, "Status") == "Idle" then
					EntityMan:ChangeVar(MyId, "Status", "Hunting");
					EntityMan:ChangeVar(MyId, "Hunting", list.id);
					EntityMan:ChangeVar(list.id, "Status", "Hunting");
					EntityMan:ChangeVar(list.id, "Hunting", MyId);
					EntityMan:SetSpeed(MyId, 0.005);
					EntityMan:SetSpeed(list.id, 0.005);
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
				EntityMan:ChangeVar(MyId, "Status", "Mating");
				EntityMan:ChangeVar(HuntingID, "Status", "Mating");
			end
		end
	end

	if CurrentStatus == "Mating" and Cooldown == 0 then
		if Unit.Total < MaxEntities then
			if CurrentRace == "Circle" then Baby = AddCircle(); end
			if CurrentRace == "Square" then Baby = AddSquare(); end
			EntityMan:MoveTo(Baby, myX, myY, myZ);
			EntityMan:NewVar(Baby, "Race");
			EntityMan:ChangeVar(Baby, "Race", CurrentRace);
			EntityMan:NewVar(Baby, "Status");
			EntityMan:ChangeVar(Baby, "Status", "Idle");
			EntityMan:NewVar(Baby, "Cooldown");
			EntityMan:ChangeVar(Baby, "Cooldown", 10);
			EntityMan:NewVar(Baby, "Hunting");
			Entities = { next = Entities, id = Baby };
		end
		EntityMan:ChangeVar(MyId, "Cooldown", 100);
		EntityMan:ChangeVar(MyId, "Status", "Rest");
		Energy = Energy - 10;
		EntityMan:ChangeVar(MyId, "Health", Energy);
	end

	EntityMan:Colour(MyId, Energy/100, 0, Energy/100);

	if CurrentStatus == "Rest" then
		if Cooldown == 0 then EntityMan:ChangeVar(MyId, "Status", "Idle"); end
		EntityMan:LookTo(MyId, math.random(64)-32, math.random(64)-32, -64);
		EntityMan:SetSpeed(MyId, 0.005);
	end

	if Energy <= 0 then 
		EntityMan:DelEntity(MyId);
		Unit.Total = Unit.Total - 1;
	end

end
