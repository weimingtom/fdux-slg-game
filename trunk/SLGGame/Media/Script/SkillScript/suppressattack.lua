function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local x, y = SquadLib.GetSquadCoord(target);
	if x >  -1 then
		local squadnum = SquadLib.GetUnitNum(target);
		local re = SkillLib.RangedAttack(caster,target);
		if re > 0 then
			local effectlv, eid = SquadLib.GetEffectLevelByName(caster, "DoubleShoot");
			if effectlv > 0 then
				if SquadLib.GetUnitNum(target) > 0 then
					SkillLib.RangedAttack(caster,target);
				end
			end
			local squadlost = squadnum - SquadLib.GetUnitNum(target);
			local casterlv = SquadLib.GetSquadLevel(caster);
			local targetlv = SquadLib.GetSquadLevel(target);
			local ep = 40;
			if targetlv > casterlv then
				ep = ep + (targetlv - casterlv) * 4;
			end	
			local point = squadlost + ScriptCommonLib.GetRand(0, 20);
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
	local eid = ScriptCommonLib.GetString("effectid");
	SquadLib.RemoveEffect(sid, eid);
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end