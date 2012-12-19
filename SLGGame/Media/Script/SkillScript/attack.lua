function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	re = SkillLib.MeleeCombat(caster,target);
	if re>0 then
		ScriptCommonLib.SetTempInt("castsuccess", 1);
	end
end

function validtarget()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	casterfaction = SquadLib.GetFaction(caster);
	targetfaction = SquadLib.GetFaction(target);
	if casterfaction ~= targetfaction then
		ScriptCommonLib.SetTempInt("validtarget", 1);
	end
end