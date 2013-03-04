function onaffect()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetTempString("effectid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");
	local tid2 = ScriptCommonLib.GetString("triggerid2");
	if tid1 == "" then
		tid1 = SquadLib.AddSquadTrigger(sid, "OnMeleeAttack", "onmeleeattack");
		SquadLib.ActiveSquadTrigger(sid, tid1);
		ScriptCommonLib.SetString("triggerid1", tid1);
	end
	if tid2 == "" then
		tid2 = SquadLib.AddSquadTrigger(sid, "AfterMeleeAttack", "aftermeleeattack");
		SquadLib.ActiveSquadTrigger(sid, tid2);
		ScriptCommonLib.SetString("triggerid2", tid2);
	end
	ScriptCommonLib.SetString("effectid", eid);
end

function onremove()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");
	local tid2 = ScriptCommonLib.GetString("triggerid2");
	if tid1 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid1);
	end
	if tid2 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid2);
	end
end

function onmeleeattack()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tsid  = ScriptCommonLib.GetTempString("targetsquadid");
	local eid = ScriptCommonLib.GetString("effectid");
	
	local armor = SquadLib.GetEquip(tsid, 2);
	if armor ~= "none" then
		local lv = SquadLib.GetEffectLevel(sid, eid);
		local attr = SquadLib.GetEquipAttr(2, armor, 2);
		local atk = 0;
		if attr > 2 then
			atk = (attr - 2) / 2;
		end
		if atk > 2 + lv then
			atk = 2 + lv;
		end
		local mid = SquadLib.ApplyModifier(sid, 0, atk, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		ScriptCommonLib.SetString("modifierid", mid);
	end
end

function aftermeleeattack()
	sid = ScriptCommonLib.GetTempString("squadid");
	mid = ScriptCommonLib.GetString("modifierid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end