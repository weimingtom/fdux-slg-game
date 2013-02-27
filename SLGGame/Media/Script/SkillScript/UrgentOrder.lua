function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	
	SquadLib.Animation(caster, 1, "Skill", "none", "none", 0, 1);

	ep = 0;
	lv = SquadLib.GetSkillLevel(caster, "UrgentOrder");
	ap = SquadLib.GetActionPoint(target);
	apmax = 1 + 2 * lv;
	if ap <  apmax then
		SquadLib.ShowValue1(target, "Skills_Prepare", apmax - ap, 1.0, 1.0, 1.0);
		ep = ep + 10 * (apmax - ap);
		ap = apmax;
	end
	
	SquadLib.SetActionPoint(target, ap);
	
	SquadLib.AddExp(caster, ep);
	
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	casterfaction = SquadLib.GetFaction(caster);
	targetfaction = SquadLib.GetFaction(target);
	if casterfaction == targetfaction then
		ScriptCommonLib.SetTempInt("validtarget", 1);
	else
		ScriptCommonLib.SetTempInt("validtarget", 0);
	end
end