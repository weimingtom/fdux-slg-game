function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	x, y = SquadLib.GetSquadCoord(target);
	if x >  -1 then
		squadnum = SquadLib.GetUnitNum(target);
		re = SkillLib.RangedAttack(caster,target);
		squadlost = squadnum - SquadLib.GetUnitNum(target);
		point = squadlost - ScriptCommonLib.GetRand(0, 20);
		if point > 20 then
			eid = SquadLib.ApplyEffect(target, "Suppressed");
		end
		ScriptCommonLib.SetTempInt("castsuccess", 1);
	end
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	casterfaction = SquadLib.GetFaction(caster);
	targetfaction = SquadLib.GetFaction(target);
	if casterfaction ~= targetfaction then
		ScriptCommonLib.SetTempInt("validtarget", 1);
	end
end

function onaffect()
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetTempString("effectid");
	lv = SquadLib.GetEffectLevel(sid, eid);
	mid = SquadLib.ApplyModifier(sid, 1, 0.0, 0.0, 0.0, 0.0, 0.0, -2.0 - lv, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
	
	tid = SquadLib.AddSquadTrigger(sid, "TurnEnd", "onturnend");
	SquadLib.ActiveSquadTrigger(sid, tid);
	ScriptCommonLib.SetString("triggerid", tid);
	
	ScriptCommonLib.SetString("effectid", eid);
end

function onremove()
	sid = ScriptCommonLib.GetTempString("squadid");
	mid = ScriptCommonLib.GetString("modifierid");
	tid = ScriptCommonLib.GetString("triggerid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
end

function onturnend()
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetString("effectid");
	SquadLib.RemoveEffect(sid, eid);
end

