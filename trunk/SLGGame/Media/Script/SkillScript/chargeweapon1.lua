function onequip()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = SquadLib.ApplyEffect(sid, "Charge");
	ScriptCommonLib.SetString("effectid", eid);
end

function onunload()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetString("effectid");
	if eid ~= "" then
		SquadLib.RemoveEffect(sid, eid);
	end
end