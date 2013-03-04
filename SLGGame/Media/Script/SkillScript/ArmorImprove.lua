function onaffect()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetTempString("effectid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");
	local tid2 = ScriptCommonLib.GetString("triggerid2");
	local mid = ScriptCommonLib.GetString("modifierid");
	
	if tid1 == "" then
		tid1 = SquadLib.AddSquadTrigger(sid, "OnEquip", "onequip");
		SquadLib.ActiveSquadTrigger(sid, tid1);
		ScriptCommonLib.SetString("triggerid1", tid1);
	end
	if tid2 == "" then
		tid2 = SquadLib.AddSquadTrigger(sid, "RemoveEquip", "removeequip");
		SquadLib.ActiveSquadTrigger(sid, tid2);
		ScriptCommonLib.SetString("triggerid2", tid2);
	end
	
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	
	local armor = SquadLib.GetEquip(sid, 2);
	if armor ~= "none" then
		local lv = SquadLib.GetEffectLevel(sid, eid);
		local attr = SquadLib.GetEquipAttr(2, armor, 5);
		if attr < 0 then
			mid = SquadLib.ApplyModifier(sid, 0, 0.0, 0.0, 0.0, 0.0, 0.0, -attr, 0.0, 0.0, 0.0, 0.0);
		end
			mid = SquadLib.ApplyModifier(sid, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		else		
		ScriptCommonLib.SetString("modifierid", mid);
	end
	
	ScriptCommonLib.SetString("effectid", eid);
end

function onremove()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid1 = ScriptCommonLib.GetString("triggerid1");
	local tid2 = ScriptCommonLib.GetString("triggerid2");
	local mid = ScriptCommonLib.GetString("modifierid");
	if tid1 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid1);
	end
	if tid2 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid2);
	end
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end

function onequip()
	local eid = ScriptCommonLib.GetString("effectid");
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eqtype = ScriptCommonLib.GetTempInt("equiptype");
	local eqid = ScriptCommonLib.GetTempString("equipid");
	local mid = ScriptCommonLib.GetString("modifierid");
	if eqtype == 2 then
		if mid ~= "" then
			SquadLib.RemoveModifier(sid, mid);
		end
		
		if eqid ~= "none" then
			local lv = SquadLib.GetEffectLevel(sid, eid);
			local attr = SquadLib.GetEquipAttr(2, eqid, 5);
			if attr < 0 then
				mid = SquadLib.ApplyModifier(sid, 0, 0.0, 0.0, 0.0, 0.0, 0.0, -attr, 0.0, 0.0, 0.0, 0.0);
			end
				mid = SquadLib.ApplyModifier(sid, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			else		
			ScriptCommonLib.SetString("modifierid", mid);
		end
	end
end

function removeequip()
	local eid = ScriptCommonLib.GetString("effectid");
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eqtype = ScriptCommonLib.GetTempInt("equiptype");
	local eqid = ScriptCommonLib.GetTempString("equipid");
	local mid = ScriptCommonLib.GetString("modifierid");
	if eqtype == 2 then
		if mid ~= "" then
			SquadLib.RemoveModifier(sid, mid);
			ScriptCommonLib.SetString("modifierid", "");
		end
	end
end