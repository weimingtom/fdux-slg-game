function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	ap = SquadLib.GetActionPoint(caster);
	maxnum = SquadLib.GetUnitMaxNum(caster);
	num = SquadLib.GetUnitNum(caster);
	sklv = SquadLib.GetSkillLevel(caster, "Rest");
	camp, eid = SquadLib.GetEffectLevelByName(squadid, "Camp");
	if ap > 1 + sklv + camp then
	 ap = 1 + sklv + camp;
	end
	num = num + ap * 2;
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