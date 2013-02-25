function onaffect()
	tid = ScriptCommonLib.GetString("triggerid");
	tid1 = ScriptCommonLib.GetString("triggerid1");
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetTempString("effectid");
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "OnCharge", "oncharge");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid)
	end
	if tid1 == "" then
		tid1 = SquadLib.AddSquadTrigger(sid, "AfterCharge", "aftercharge");
		SquadLib.ActiveSquadTrigger(sid, tid1);
		ScriptCommonLib.SetString("triggerid1", tid1)
	end
	ScriptCommonLib.SetString("effectid", eid);
end

function onremove()
	sid = ScriptCommonLib.GetTempString("squadid");
	tid = ScriptCommonLib.GetString("triggerid");
	tid1 = ScriptCommonLib.GetString("triggerid1");
	mid = ScriptCommonLib.GetString("modifierid");
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
	if tid1 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid1);
	end
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end

function oncharge()
	mid = ScriptCommonLib.GetString("modifierid");
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetString("effectid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	lv = SquadLib.GetEffectLevel(sid, eid);
	mid = SquadLib.ApplyModifier(sid, 0, lv, 0.0, 0.0, lv, lv, 0.0, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
end

function aftercharge()
	mid = ScriptCommonLib.GetString("modifierid");
	sid = ScriptCommonLib.GetTempString("squadid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
		ScriptCommonLib.SetString("modifierid", "");
	end
end