function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	SquadLib.ApplyEffect(caster, "FuryPuppet");
	SquadLib.ApplyEffect(caster, "Tired");
	SquadLib.PlayParticle(caster, 2, "mp_diabolique", "none", 2500);
	SquadLib.AddExp(caster, 50);
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	ScriptCommonLib.SetTempInt("validtarget", 1);
end

function onaffect()
	local eid1 = ScriptCommonLib.GetString("effectid1");
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetTempString("effectid");
	local tid = ScriptCommonLib.GetString("triggerid");
	local mid = ScriptCommonLib.GetString("modifierid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	local lv = SquadLib.GetSkillLevel(sid, "FuryPuppet");
	mid = SquadLib.ApplyModifier(sid, 0, lv + 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);	
	if eid1 ~= "" then
		SquadLib.RemoveEffect(sid, eid1);
	end
	eid1 = SquadLib.ApplyEffect(sid, "Trample");
	ScriptCommonLib.SetString("effectid1", eid1);
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnEnd", "onturnend");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	ScriptCommonLib.SetString("effectid", eid);
	ScriptCommonLib.SetInt("turn", 0);
end

function onremove()
	local eid1 = ScriptCommonLib.GetString("effectid1");
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid = ScriptCommonLib.GetString("triggerid");
	local mid = ScriptCommonLib.GetString("modifierid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	if eid1 ~= "" then
		SquadLib.RemoveEffect(sid, eid1);
	end
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
end

function onturnend()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local turn = ScriptCommonLib.GetInt("turn");
	if turn == 3 then
		local eid = ScriptCommonLib.GetString("effectid");
		SquadLib.RemoveEffect(sid, eid);
	else
		ScriptCommonLib.SetInt("turn", turn + 1);
	end
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end