function onaffect()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid = ScriptCommonLib.GetString("triggerid");
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnStart", "turnstart");
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

function turnstart()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local lv, eid = SquadLib.GetEffectLevelByName(sid, "PuppetShield1");
	local sklv = SquadLib.GetSkillLevel(sid, "PuppetShield");
	for i = lv, sklv + 1 do
		SquadLib.ApplyEffect(sid, "PuppetShield1");
	end
end