function onaffect()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid = ScriptCommonLib.GetString("triggerid");
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "OnMeleeAttack", "onmeleeattack");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
end

function onremove()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid = ScriptCommonLib.GetString("triggerid");
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end

function onmeleeattack()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tsid = ScriptCommonLib.GetTempString("targetsquadid");
	local asdefender = ScriptCommonLib.GetTempInt("asdefender");
	if asdefender == 1 then
		local ap = SquadLib.GetActionPoint(tsid);
		ap = ap - 2.0;
		SquadLib.SetActionPoint(tsid, ap);
	end
end
