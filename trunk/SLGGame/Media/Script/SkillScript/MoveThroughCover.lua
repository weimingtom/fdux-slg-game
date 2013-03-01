function onaffect()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetTempString("effectid");
	local tid = ScriptCommonLib.GetString("triggerid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");

	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TryMove", "trymove");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	if tid1 == "" then
		tid1 = SquadLib.AddSquadTrigger(sid, "MoveTo", "moveto");
		SquadLib.ActiveSquadTrigger(sid, tid1);
		ScriptCommonLib.SetString("triggerid1", tid1);
	end
	ScriptCommonLib.SetString("effectid", eid);
end

function onremove()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid = ScriptCommonLib.GetString("triggerid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
	if tid1 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid1);
	end
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end

function trymove()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetString("effectid");
	local lv = SquadLib.GetEffectLevel(sid, eid);
	local apcost = ScriptCommonLib.GetTempFloat("apcost");
	apcost = apcost - lv; 
	if apcost < 2 then
		apcost = 2;
	end
	ScriptCommonLib.SetTempFloat("apcost", apcost);
end

function moveto()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetString("effectid");
	local lv = SquadLib.GetEffectLevel(sid, eid);
	local apcost = ScriptCommonLib.GetTempFloat("apcost");
	apcost = apcost - lv; 
	if apcost < 2 then
		apcost = 2;
	end
	ScriptCommonLib.SetTempFloat("apcost", apcost);	
end