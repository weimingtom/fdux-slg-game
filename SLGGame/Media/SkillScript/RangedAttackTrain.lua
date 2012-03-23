function onaffect()
	mid = ScriptCommonLib.GetString("modifierid");
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetTempString("effectid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	lv = SquadLib.GetEffectLevel(sid, eid);
	mid = SquadLib.ApplyModifier(sid, 0, 0.0, lv, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
end

function onremove()
	mid = ScriptCommonLib.GetString("modifierid");
	sid = ScriptCommonLib.GetTempString("squadid");
		if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
end