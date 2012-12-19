function onequip()
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = SquadLib.ApplyEffect(sid, "AntiCav");
	ScriptCommonLib.SetString("effectid", eid);
end

function onunload()
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetString("effectid");
	if eid ~= "" then
		SquadLib.RemoveEffect(sid, eid);
	end
end