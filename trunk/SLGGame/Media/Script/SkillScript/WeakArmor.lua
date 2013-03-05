function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
		
	SquadLib.Animation(caster, 1, "Skill", "none", "mp_seal_04", 0, 1);
	local improvelv, improve = SquadLib.GetEffectLevelByName(caster, "WeakImprove");
	if improvelv > 0 then
		SquadLib.ApplyEffect(target, "ImprovedWeakArmor");
	else
		SquadLib.ApplyEffect(target, "WeakArmor");
	end
	SquadLib.PlayParticle(target, 3, "mp_woosh_06", "none", 2500);
	
	local casterlv = SquadLib.GetSquadLevel(caster);
	local targetlv = SquadLib.GetSquadLevel(target);
	local ep = 50;
	if targetlv > casterlv then
		ep = ep + (targetlv - casterlv) * 5;
	end	
	SquadLib.AddExp(caster, ep);
	ScriptCommonLib.SetTempInt("castsuccess", 1);
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
		local squadtype = SquadLib.GetType(target);
		if squadtype == 0 then
			ScriptCommonLib.SetTempInt("validtarget", 1);
		else
			ScriptCommonLib.SetTempInt("validtarget", 0);
		end
    else
        ScriptCommonLib.SetTempInt("validtarget", 0);
	end
end

function onaffect()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetTempString("effectid");
	local mid = ScriptCommonLib.GetString("modifierid");
	local tid = ScriptCommonLib.GetString("triggerid");

	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	
	local def = 0;
	local armor = SquadLib.GetEquip(sid, 2);
	if armor ~= "none" then
		local attr = SquadLib.GetEquipAttr(2, armor, 2);
		local def = 0;
		if attr > 2 then
			def = (attr - 2) / 2;
		end
		if def > 2 then
			def = 2;
		end
	end
	
	mid = SquadLib.ApplyModifier(sid, 2, 0.0, 0.0, -def, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnEnd", "onturnend");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	ScriptCommonLib.SetString("effectid", eid);

	ScriptCommonLib.SetInt("turn", 0);
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