function onaffect()
	sid = ScriptCommonLib.GetTempString("squadid");
	SquadLib.AddSkill(sid, "Pray");
end

function onremove()
	sid = ScriptCommonLib.GetTempString("squadid");
	SquadLib.RemoveSkill(sid, "Pray");
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end