function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local squad1num = SquadLib.GetUnitNum(caster);
	local squad2num = SquadLib.GetUnitNum(target);
	local re = SkillLib.MeleeCombat(caster,target);
	if re > 0 then
		local ep = 50;
		local casterlv = SquadLib.GetSquadLevel(caster);
		local targetlv = SquadLib.GetSquadLevel(target);
		if targetlv > casterlv then
			ep = ep + (targetlv - casterlv) * 5;
		end
		
		if SquadLib.GetUnitNum(target) > 0 then
			local squad1lost = squad1num - SquadLib.GetUnitNum(caster);
			local squad2lost = squad2num - SquadLib.GetUnitNum(target);
			local point = squad2lost - squad1lost + ScriptCommonLib.GetRand(0, 20);
			if point > 15 then
				local casterx, castery = SquadLib.GetSquadCoord(caster);
				local targetx, targety = SquadLib.GetSquadCoord(target);
				
				dir = MapLib.GetDirection(casterx, castery, targetx, targety);
				local dx = 0;
				local dy = 0;
				if dir == 1 then
					dy = 1;
				elseif dir == 2 then
					dx = -1;
				elseif dir == 3 then
					dx = 1;
				else
					dy = -1;
				end
				re = SquadLib.MoveSquad(target, targetx + dx, targety + dy);
				if re == 1 then
					ep = ep + 30;
					SquadLib.MoveSquad(caster, casterx + dx, castery + dy);
				end
				
			end
		end	
		
		SquadLib.AddExp(caster, ep);
		ScriptCommonLib.SetTempInt("castsuccess", 1);
	end
end

function validtarget()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local casterfaction = SquadLib.GetFaction(caster);
	local targetfaction = SquadLib.GetFaction(target);
	if casterfaction ~= targetfaction then
		ScriptCommonLib.SetTempInt("validtarget", 1);
	end
end