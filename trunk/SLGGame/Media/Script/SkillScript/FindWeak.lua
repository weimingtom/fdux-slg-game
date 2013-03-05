function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	
	local ep = 0;
	local atk = 0;
	local form = SquadLib.GetFormation(target);
	if form == 0 then 
		local casterx, castery = SquadLib.GetSquadCoord(caster);
		local targetx, targety = SquadLib.GetSquadCoord(target);
		dir = MapLib.GetDirection(casterx, castery, targetx, targety);
		dir2 = SquadLib.GetDirection(caster);
		if dir == dir2 then
			atk = atk + 5;
			ep = ep + 30;
		end
	elseif form == 2 then
		atk = atk + 5;
		ep = ep + 30;
	end
	
	local mid = SquadLib.ApplyModifier(caster, 0, atk, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

	local re = SkillLib.MeleeCombat(caster,target);
	if re > 0 then
		ep = ep + 50;
		local casterlv = SquadLib.GetSquadLevel(caster);
		local targetlv = SquadLib.GetSquadLevel(target);
		if targetlv > casterlv then
			ep = ep + (targetlv - casterlv) * 5;
		end
		
		SquadLib.AddExp(caster, ep);
		ScriptCommonLib.SetTempInt("castsuccess", 1);
	end
	SquadLib.RemoveModifier(caster, mid);
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