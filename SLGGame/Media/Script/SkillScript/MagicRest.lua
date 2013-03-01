function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local ap = SquadLib.GetActionPoint(caster);
	local sklv = SquadLib.GetSkillLevel(caster, "MagicRest");
	local camp, eidcamp = SquadLib.GetEffectLevelByName(caster, "Camp");
	local tired, eidtired = SquadLib.GetEffectLevelByName(caster, "Tired");
	
	if ap > 3 + 2 * camp then
		ap = 3 + 2 * camp;
	end
	local restnum = ap + sklv * 2;
	if restnum > tired then
		restnum = tired;
	end
	for i = 1, restnum do
		SquadLib.RemoveEffect(caster, eidtired);
	end
	
	local ep = 8 * restnum;
	SquadLib.AddExp(caster, ep);	
	
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	ScriptCommonLib.SetTempInt("validtarget", 1);
end