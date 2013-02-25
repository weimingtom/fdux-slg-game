function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	ap = SquadLib.GetActionPoint(caster);
	maxnum = SquadLib.GetUnitMaxNum(caster);
	SquadLib.Animation(caster, 1, "Skill", "none", "mp_seal_08", 0, 1);
	num = SquadLib.GetUnitNum(caster);
	num = num + ap / 2.0;
	if num > maxnum then
		num = maxnum;
	end
	SquadLib.SetUnitNum(caster, num);
	ep = 5 * num;
	SquadLib.AddExp(caster, ep);	
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	ScriptCommonLib.SetTempInt("validtarget", 1);
end