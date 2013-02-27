function onaffect()
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetTempString("effectid");
	tid = ScriptCommonLib.GetString("triggerid");
	mid = ScriptCommonLib.GetString("modifierid");
	
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	lv = SquadLib.GetEffectLevel(sid, eid);
	mid = SquadLib.ApplyModifier(sid, 1, -lv, -lv, -lv, 0.0, 0.0, -2.0 - lv, 0.0, 0.0, 0.0, -1.0 - lv);
	ScriptCommonLib.SetString("modifierid", mid);
	
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnEnd", "onturnend");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	
	ScriptCommonLib.SetString("effectid", eid);
	ScriptCommonLib.SetInt("turn", 0);
	
	eid = SquadLib.ApplyEffect(sid, "Waver");
end

function onremove()
	sid = ScriptCommonLib.GetTempString("squadid");
	mid = ScriptCommonLib.GetString("modifierid");
	tid = ScriptCommonLib.GetString("triggerid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
end

function onturnend()
	sid = ScriptCommonLib.GetTempString("squadid");
	turn = ScriptCommonLib.GetInt("turn");
	if turn == 1 then
		eid = ScriptCommonLib.GetString("effectid");
		SquadLib.RemoveEffect(sid, eid);
	else
		ScriptCommonLib.SetInt("turn", turn + 1);
	end
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end