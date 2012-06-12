function onaffect()
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetTempString("effectid");
	tid1 = ScriptCommonLib.GetString("triggerid1");
	tid2 = ScriptCommonLib.GetString("triggerid2");
	if tid1 == "" then
		tid1 = SquadLib.AddSquadTrigger(sid, "OnMeleeAttack", "onmeleeattack");
		SquadLib.ActiveSquadTrigger(sid, tid1);
		ScriptCommonLib.SetString("triggerid1", tid1);
	end
	if tid2 == "" then
		tid2 = SquadLib.AddSquadTrigger(sid, "AfterMeleeAttack", "aftermeleeattack");
		SquadLib.ActiveSquadTrigger(sid, tid2);
		ScriptCommonLib.SetString("triggerid2", tid2);
	end
	ScriptCommonLib.SetString("effectid", eid);
end

function onremove()
	sid = ScriptCommonLib.GetTempString("squadid");
	tid1 = ScriptCommonLib.GetString("triggerid1");
	tid2 = ScriptCommonLib.GetString("triggerid2");
	if tid1 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid1);
	end
	if tid2 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid2);
	end
end

function onmeleeattack()
	sid = ScriptCommonLib.GetTempString("squadid");
	tsid  = ScriptCommonLib.GetTempString("targetsquadid");
	eid = ScriptCommonLib.GetString("effectid");
	lv = SquadLib.GetEffectLevel(sid, eid);
	mid = SquadLib.ApplyModifier(sid, 0, lv * 5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
end

function aftermeleeattack()
	sid = ScriptCommonLib.GetTempString("squadid");
	mid = ScriptCommonLib.GetString("modifierid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
end