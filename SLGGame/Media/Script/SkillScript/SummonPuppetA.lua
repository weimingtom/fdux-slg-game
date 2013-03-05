function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local maxnum = SquadLib.GetUnitMaxNum(caster);
	SquadLib.Animation(caster, 1, "Skill", "none", "mp_seal_04", 0, 1);
	local num = SquadLib.GetUnitNum(caster);
	local sklv = SquadLib.GetSkillLevel(caster, "SummonPuppetA");
	num = num + 4 + sklv * 2;
	if num > maxnum then
		num = maxnum;
	end
	SquadLib.SetUnitNum(caster, num);
	local ep = 8 * num;
	SquadLib.AddExp(caster, ep);
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	ScriptCommonLib.SetTempInt("validtarget", 1);
end