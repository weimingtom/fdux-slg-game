function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local squad2num = SquadLib.GetUnitNum(target);
	local re = SkillLib.MeleeCombat(caster,target);
	if re>0 then
		local ep = 50;
		local casterlv = SquadLib.GetSquadLevel(caster);
		local targetlv = SquadLib.GetSquadLevel(target);
		if targetlv > casterlv then
			ep = ep + (targetlv - casterlv) * 5;
		end
		local squad2lost = squad2num - SquadLib.GetUnitNum(target);
		local point = squad2lost + ScriptCommonLib.GetRand(0, 20);
		if point > 10 then
			SquadLib.ApplyEffect(target, "Chaos");
			ep = ep + 20;
		end
		SquadLib.AddExp(caster, ep);
		ScriptCommonLib.SetTempInt("castsuccess", 1);
	end
end

function validtarget()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local casterfaction = SquadLib.GetFaction(caster);
	local targetfaction = SquadLib.GetFaction(target);
	if casterfaction ~= targetfaction then
		ScriptCommonLib.SetTempInt("validtarget", 1);
	end
end

function onaffect()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetTempString("effectid");
	local tid = ScriptCommonLib.GetString("triggerid");
	local mid = ScriptCommonLib.GetString("modifierid");
	
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	local lv = SquadLib.GetEffectLevel(sid, eid);
	mid = SquadLib.ApplyModifier(sid, 1, -lv, -lv, -lv, 0.0, 0.0, -2.0 - lv, 0.0, 0.0, 0.0, -1.0 - lv);
	ScriptCommonLib.SetString("modifierid", mid);
	
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnEnd", "onturnend");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	
	ScriptCommonLib.SetString("effectid", eid);
	ScriptCommonLib.SetInt("turn", 0);
	
	eid = SquadLib.ApplyEffect(sid, "Waver");
end

function onremove()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local mid = ScriptCommonLib.GetString("modifierid");
	local tid = ScriptCommonLib.GetString("triggerid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
end

function onturnend()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local turn = ScriptCommonLib.GetInt("turn");
	if turn == 1 then
		local eid = ScriptCommonLib.GetString("effectid");
		SquadLib.RemoveEffect(sid, eid);
	else
		ScriptCommonLib.SetInt("turn", turn + 1);
	end
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end