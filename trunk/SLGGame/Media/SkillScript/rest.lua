function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	ap = SquadLib.GetActionPoint(caster);
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end