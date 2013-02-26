function onaffect()
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetTempString("effectid");
	tid = ScriptCommonLib.GetString("triggerid");
	tid1 = ScriptCommonLib.GetString("triggerid1");

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
	sid = ScriptCommonLib.GetTempString("squadid");
	tid = ScriptCommonLib.GetString("triggerid");
	tid1 = ScriptCommonLib.GetString("triggerid1");
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
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetString("effectid");
	lv = SquadLib.GetEffectLevel(sid, eid);
	apcost = ScriptCommonLib.GetTempFloat("apcost");
	apcost = apcost - lv; 
	if apcost < 2 then
		apcost = 2;
	end
	ScriptCommonLib.SetTempFloat("apcost", apcost);
end

function moveto()
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetString("effectid");
	lv = SquadLib.GetEffectLevel(sid, eid);
	apcost = ScriptCommonLib.GetTempFloat("apcost");
	apcost = apcost - lv; 
	if apcost < 2 then
		apcost = 2;
	end
	ScriptCommonLib.SetTempFloat("apcost", apcost);	
end