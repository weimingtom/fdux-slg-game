function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local unitnum = SquadLib.GetUnitNum(caster);
	if unitnum > 3 then
		SquadLib.Animation(caster, 1, "Skill", "none", "mp_seal_08", 0, 1);
		unitnum = unitnum - 2;
		SquadLib.SetUnitNum(caster, unitnum);
		SquadLib.PlayParticle(target, 3, "mp_streak_01", "none", 2500);
		local maxnum = SquadLib.GetUnitMaxNum(target);
		local num = SquadLib.GetUnitNum(target);
		num = num + 12;
		if num > maxnum then
			num = maxnum;
		end
		SquadLib.SetUnitNum(target, num);
		local ep = 50;
		if casterlv > targetlv then
			ep = ep + (targetlv - casterlv) * 5;
		end		
		SquadLib.AddExp(caster, ep);	
		ScriptCommonLib.SetTempInt("castsuccess", 1);
	else
		SquadLib.ShowValue(sid, "Skills_NotEnoughGuard", 1.0, 1.0, 1.0);
		ScriptCommonLib.SetTempInt("castsuccess", 0);
	end
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local casterfaction = SquadLib.GetFaction(caster);
	local targetfaction = SquadLib.GetFaction(target);
	if casterfaction == targetfaction then
		local squadtype = SquadLib.GetType(target);
		if squadtype == 0 then
			ScriptCommonLib.SetTempInt("validtarget", 1);
		else
			ScriptCommonLib.SetTempInt("validtarget", 0);
		end
	else
		ScriptCommonLib.SetTempInt("validtarget", 0);
	end
end