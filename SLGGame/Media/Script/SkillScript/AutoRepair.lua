function onaffect()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetTempString("effectid");
	local tid = ScriptCommonLib.GetString("triggerid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");

	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnStart", "onturnstart");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	if tid1 == "" then
		tid1 = SquadLib.AddSquadTrigger(sid, "TurnEnd", "onturnend");
		SquadLib.ActiveSquadTrigger(sid, tid1);
		ScriptCommonLib.SetString("triggerid1", tid);
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

function onturnstart()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetString("effectid");
	local lv = SquadLib.GetEffectLevel(sid, eid);
	local num = SquadLib.GetUnitNum(sid);
	local maxnum = SquadLib.GetUnitMaxNum(sid);
	if num < maxnum then
		num = num + lv;
		if num > maxnum then
			num = maxnum;
		end
		SquadLib.PlayParticle(sid, 2, "mp_spell_effect_01", "none", 2500);
		SquadLib.SetUnitNum(sid, num);
	end
end

function onturnend()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetString("effectid");
	local lv = SquadLib.GetEffectLevel(sid, eid);
	local num = SquadLib.GetUnitNum(sid);
	local maxnum = SquadLib.GetUnitMaxNum(sid);
	if num < maxnum then
		num = num + lv + 1;
		if num > maxnum then
			num = maxnum;
		end
		SquadLib.PlayParticle(sid, 2, "mp_spell_effect_01", "none", 2500);
		SquadLib.SetUnitNum(sid, num);
	end
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end