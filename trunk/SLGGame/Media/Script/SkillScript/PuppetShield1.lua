function onaffect()
	local mid = ScriptCommonLib.GetString("modifierid");
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetTempString("effectid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");
	local tid2 = ScriptCommonLib.GetString("triggerid2");
	local tid3 = ScriptCommonLib.GetString("triggerid3");
	local pid = ScriptCommonLib.GetString("particleid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	mid = SquadLib.ApplyModifier(sid, 2, 0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
	if tid1 == "" then
		tid1 = SquadLib.AddSquadTrigger(sid, "OnUnderRangedAttack", "onunderrangedattack");
		SquadLib.ActiveSquadTrigger(sid, tid1);
		ScriptCommonLib.SetString("triggerid1", tid1);
	end
	if tid2 == "" then
		tid2 = SquadLib.AddSquadTrigger(sid, "OnUnderMagicAttack", "onundermagicattack");
		SquadLib.ActiveSquadTrigger(sid, tid2);
		ScriptCommonLib.SetString("triggerid2", tid2);
	end
	if tid3 == "" then
		tid3 = SquadLib.AddSquadTrigger(sid, "OnMeleeAttack", "onmeleeattack");
		SquadLib.ActiveSquadTrigger(sid, tid3);
		ScriptCommonLib.SetString("triggerid3", tid3);
	end
	
	if pid == "" then
		pid = SquadLib.AddParticle(sid, "mp_spell_effect_06", 2);
	end
	ScriptCommonLib.SetString("particleid", pid);
	
	ScriptCommonLib.SetString("effectid", eid);
end

function onremove()
	local mid = ScriptCommonLib.GetString("modifierid");
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");
	local tid2 = ScriptCommonLib.GetString("triggerid2");
	local tid3 = ScriptCommonLib.GetString("triggerid3");
	local pid = ScriptCommonLib.GetString("particleid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	if tid1 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid1);
	end
	if tid2 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid2);
	end
	if tid3 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid3);
	end
	if pid ~= "" then
		SquadLib.DelParticle(sid, pid);
	end
end

function onunderrangedattack()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetString("effectid");
	SquadLib.RemoveEffect(sid, eid);
end

function onundermagicattack()
	local sid = ScriptCommonLib.GetTempString("squadid");	
	local eid = ScriptCommonLib.GetString("effectid");
	SquadLib.RemoveEffect(sid, eid);
end

function onmeleeattack()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetString("effectid");
	SquadLib.RemoveEffect(sid, eid);
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end