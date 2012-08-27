function useskill()
	sid = ScriptCommonLib.GetTempString("squadid");
	tgtx = ScriptCommonLib.GetTempString("targetx");
	tgty = ScriptCommonLib.GetTempString("targety");
	
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validaffectarea()
	ScriptCommonLib.SetTempInt("validaffectarea", 1);
end