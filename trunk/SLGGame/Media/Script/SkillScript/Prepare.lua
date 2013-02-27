function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	eid = SquadLib.ApplyEffect(caster, "Prepare");
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	ScriptCommonLib.SetTempInt("validtarget", 1);
end

function onaffect()
	mid = ScriptCommonLib.GetString("modifierid");
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetTempString("effectid");
	tid = ScriptCommonLib.GetString("triggerid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	lv = SquadLib.GetSkillLevel(sid, "Prepare");
	ap = SquadLib.GetActionPoint(sid);
	if ap > 1 + 2 * lv then
		ap = 1 + 2 * lv;
	end
	ep = 15 * ap;
	SquadLib.AddExp(sid, ep);
	mid = SquadLib.ApplyModifier(sid, 0, 0.0, 0.0, 0.0, 0.0, 0.0, ap, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnStart", "onturnstart");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	ScriptCommonLib.SetString("effectid", eid);
	
	SquadLib.ShowValue1(sid, "Skills_Prepare", ap, 1.0, 1.0, 1.0);
end

function onremove()
	mid = ScriptCommonLib.GetString("modifierid");
	sid = ScriptCommonLib.GetTempString("squadid");
	tid = ScriptCommonLib.GetString("triggerid");
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
	SquadLib.RemoveEffect(sid, eid);
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end