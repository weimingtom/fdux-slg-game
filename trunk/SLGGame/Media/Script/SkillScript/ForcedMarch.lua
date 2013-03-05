function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	
	SquadLib.Animation(caster, 1, "Skill", "none", "none", 0, 1);
		
	SquadLib.ApplyEffect(caster, "ForcedMarch");
	SquadLib.AddExp(caster, 50);
	SquadLib.ShowValue(caster, "Skills_ForceMarch", 1.0, 1.0, 1.0);
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
	if eid1 ~= "" then
		SquadLib.RemoveEffect(sid, eid1);
	end
	eid1 = SquadLib.ApplyEffect(sid, "MoveThroughCover");
	ScriptCommonLib.SetString("effectid1", eid1);
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnEnd", "onturnend");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	ScriptCommonLib.SetString("effectid", eid);
end

function onremove()
	local eid1 = ScriptCommonLib.GetString("effectid1");
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid = ScriptCommonLib.GetString("triggerid");
	if eid1 ~= "" then
		SquadLib.RemoveEffect(sid, eid1);
	end
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
end

function onturnend()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetString("effectid");
	SquadLib.RemoveEffect(sid, eid);
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end