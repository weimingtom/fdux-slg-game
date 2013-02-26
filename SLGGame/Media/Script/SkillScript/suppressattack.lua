function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	x, y = SquadLib.GetSquadCoord(target);
	if x >  -1 then
		squadnum = SquadLib.GetUnitNum(target);
		re = SkillLib.RangedAttack(caster,target);
		if re > 0 then
			effectlv, eid = SquadLib.GetEffectLevelByName(caster, "DoubleShoot");
			if effectlv > 0 then
				if SquadLib.GetUnitNum(target) > 0 then
					SkillLib.RangedAttack(caster,target);
				end
			end
			squadlost = squadnum - SquadLib.GetUnitNum(target);
			casterlv = SquadLib.GetSquadLevel(caster);
			targetlv = SquadLib.GetSquadLevel(target);
			ep = 40;
			if targetlv > casterlv then
				ep = ep + (targetlv - casterlv) * 4;
			end	
			point = squadlost + ScriptCommonLib.GetRand(0, 20);
			if point > 15 then
				eid = SquadLib.ApplyEffect(target, "Suppressed");
				ep = ep + 20;
			end
			SquadLib.AddExp(caster, ep);
			ScriptCommonLib.SetTempInt("castsuccess", 1);
		end
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
	tid = ScriptCommonLib.GetString("triggerid");
	mid = ScriptCommonLib.GetString("modifierid");
	
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	mid = SquadLib.ApplyModifier(sid, 1, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
	
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnEnd", "onturnend");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	
	SquadLib.ShowValue(sid, "Skills_Suppressed", 1.0, 1.0, 1.0);
	
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

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end