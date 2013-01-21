function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	eid = SquadLib.ApplyEffect(caster, "Defence");
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function onaffect()
	mid = ScriptCommonLib.GetString("modifierid");
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetTempString("effectid");
	tid = ScriptCommonLib.GetString("triggerid");
	--pid = ScriptCommonLib.GetString("particleid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	lv = SquadLib.GetEffectLevel(sid, eid);
	ap = SquadLib.GetActionPoint(sid);
	defence = lv + (ap - 2) / 2;
	if defence > 2 + lv then
		defence = 2 + lv;
	end
	mid = SquadLib.ApplyModifier(sid, 0, 0.0, 0.0, defence, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnStart", "onturnstart");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	ScriptCommonLib.SetString("effectid", eid);
	--[[
	if pid == "" then
		pid = SquadLib.AddParticle(sid, "PUMediaPack/Fireplace_01", 3);
	end
	ScriptCommonLib.SetString("particleid", pid);
	]]--
end

function onremove()
	mid = ScriptCommonLib.GetString("modifierid");
	sid = ScriptCommonLib.GetTempString("squadid");
	tid = ScriptCommonLib.GetString("triggerid");
	--pid = ScriptCommonLib.GetString("particleid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
	--[[
	if pid ~= "" then
		SquadLib.DelParticle(sid, pid);
	end
	]]--
end

function onturnstart()
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetString("effectid");
	SquadLib.RemoveEffect(sid, eid);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	ScriptCommonLib.SetTempInt("validtarget", 1);
end