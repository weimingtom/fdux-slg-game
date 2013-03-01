function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local ap = SquadLib.GetActionPoint(caster);
	local maxnum = SquadLib.GetUnitMaxNum(caster);
	local num = SquadLib.GetUnitNum(caster);
	local sklv = SquadLib.GetSkillLevel(caster, "Rest");
	local camp, eid = SquadLib.GetEffectLevelByName(caster, "Camp");
	if ap > 3 + camp then
	 ap = 3 + camp;
	end
	num = num + ap * (1 + sklv);
	if num > maxnum then
		num = maxnum;
	end
	SquadLib.SetUnitNum(caster, num);
	local ep = 5 * num;
	SquadLib.AddExp(caster, ep);	
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	ScriptCommonLib.SetTempInt("validtarget", 1);
end