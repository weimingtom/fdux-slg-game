function onaffect()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetTempString("effectid");
	local tid = ScriptCommonLib.GetString("triggerid");
	local mid = ScriptCommonLib.GetString("modifierid");
	local eid1 = ScriptCommonLib.GetString("effectid1");
	
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	
	if eid1 ~= "" then
		SquadLib.RemoveEffect(sid, eid1);
	end

	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "MoveTo", "moveto");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	ScriptCommonLib.SetString("effectid", eid);
end

function onremove()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid = ScriptCommonLib.GetString("triggerid");
	local mid = ScriptCommonLib.GetString("modifierid");
	local eid1 = ScriptCommonLib.GetString("effectid1");
	
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

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end

function moveto()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local croodx = ScriptCommonLib.GetTempInt("tgtx");
	local croody = ScriptCommonLib.GetTempInt("tgty");
	local eid = ScriptCommonLib.GetString("effectid");
	local mid = ScriptCommonLib.GetString("modifierid");
	local eid1 = ScriptCommonLib.GetString("effectid1");
	
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	
	if eid1 ~= "" then
		SquadLib.RemoveEffect(sid, eid1);
	end

	local cov = MapLib.GetGroundAttr(croodx, croody, 1);
	
	if cov > 0 then
		local lv = SquadLib.GetEffectLevel(sid, eid);
		if cov > 1 + lv then
			cov = 1 + lv;
		end
		
		mid = SquadLib.ApplyModifier(sid, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, cov, 0.0, 0.0);
		SquadLib.SetString("modifierid", mid);
		
		eid1 = SquadLib.ApplyEffect(sid, "HideInMark");
		ScriptCommonLib.SetString("effectid1", eid1);
	end
end