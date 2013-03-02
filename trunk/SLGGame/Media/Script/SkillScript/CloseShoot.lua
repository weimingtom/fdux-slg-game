function onaffect()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid = ScriptCommonLib.GetString("triggerid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "OnRangedAttack", "onrangedattack");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	if tid1 == "" then
		tid1 = SquadLib.AddSquadTrigger(sid, "AfterRangedAttack", "afterrangedattack");
		SquadLib.ActiveSquadTrigger(sid, tid1);
		ScriptCommonLib.SetString("triggerid1", tid1);
	end
end

function onremove()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local mid = ScriptCommonLib.GetString("modifierid");
	local tid = ScriptCommonLib.GetString("triggerid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");	
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

function onrangedattack()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tsid = ScriptCommonLib.GetTempString("targetsquadid");
	local mid = ScriptCommonLib.GetString("modifierid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	local croodx, croody = SquadLib.GetSquadCoord(sid);
	local tcroodx, tcroody = SquadLib.GetSquadCoord(tsid);
	local range = MapLib.GetDistance(croodx, croody, tcroodx, tcroody);
	if range < 3 then
		range = 3 - range;
	else
		range = 0;
	end
	mid = SquadLib.ApplyModifier(sid, 0, range, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
end

function afterrangedattack()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local mid = ScriptCommonLib.GetString("modifierid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
		ScriptCommonLib.SetString("modifierid", "");
	end	
end
