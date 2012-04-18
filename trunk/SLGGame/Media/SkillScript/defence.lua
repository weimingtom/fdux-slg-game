function useskill()
	caster  = ScriptCommonLib.GetTempString("castsquad");
	eid = SquadLib.ApplyEffect(caster, "Defence");
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function onaffect()
	mid = ScriptCommonLib.GetString("modifierid");
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetTempString("effectid");
	tid = ScriptCommonLib.GetTempString("triggerid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	lv = SquadLib.GetEffectLevel(sid, eid);
	ap = SquadLib.GetActionPoint(sid);
	defence = lv + (ap - 2) / 2;
	mid = SquadLib.ApplyModifier(sid, 0, 0.0, 0.0, defence, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
	if tid ~= "" then
		tid = SquadLib.AddSquadTrigger(sid, "turnstart", "onturnstart");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	ScriptCommonLib.SetString("effectid", eid);
end

function onremove()
	mid = ScriptCommonLib.GetString("modifierid");
	sid = ScriptCommonLib.GetTempString("squadid");
	tid = ScriptCommonLib.GetTempString("triggerid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
end

function onturnstart()
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetString("effectid");
	ScriptCommonLib.RemoveEffect(sid, eid);
end