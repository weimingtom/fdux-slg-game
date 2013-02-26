function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	ap = SquadLib.GetActionPoint(caster);
	maxnum = SquadLib.GetUnitMaxNum(caster);
	SquadLib.Animation(caster, 1, "Skill", "none", "mp_seal_08", 0, 1);
	num = SquadLib.GetUnitNum(caster);
	sklv = SquadLib.GetSkillLevel(caster, "Pray");
	camp, eid = SquadLib.GetEffectLevelByName(squadid, "Camp");
	if ap > 2 + sklv * 2 + camp then
	 ap = 2 + sklv * 2 + camp;
	end
	num = num + ap;
	if num > maxnum then
		num = maxnum;
	end
	SquadLib.SetUnitNum(caster, num);
	ep = 8 * num;
	SquadLib.AddExp(caster, ep);	
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	ScriptCommonLib.SetTempInt("validtarget", 1);
end