function onaffect()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetTempString("effectid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");
	local tid2 = ScriptCommonLib.GetString("triggerid2");
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
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");
	local tid2 = ScriptCommonLib.GetString("triggerid2");
	if tid1 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid1);
	end
	if tid2 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid2);
	end
end

function onmeleeattack()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tsid  = ScriptCommonLib.GetTempString("targetsquadid");
	local eid = ScriptCommonLib.GetString("effectid");
	local lv = SquadLib.GetEffectLevel(sid, eid);
	local house = SquadLib.GetEquip(tsid, 1);
	if house == "none" then
		local mid = SquadLib.ApplyModifier(sid, 0, lv + 1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		ScriptCommonLib.SetString("modifierid", mid);
	end
end

function aftermeleeattack()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local mid = ScriptCommonLib.GetString("modifierid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end