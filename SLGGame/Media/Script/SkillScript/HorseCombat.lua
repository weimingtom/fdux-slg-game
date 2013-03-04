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
	
	local house = SquadLib.GetEquip(sid, 1);
	if house ~= "none" then
		local lv = SquadLib.GetEffectLevel(sid, eid);
		local attr = SquadLib.GetEquipAttr(1, eqid, 2);
		local def = 0;
		if attr < 0 then
			def = -attr;
		end
		if def > 1 + lv then
			def = 1 + lv;
		end
		attr = SquadLib.GetEquipAttr(1, eqid, 9);
		local cot = 0;
		if attr < 0 then
			cot = -attr;
		end
		if cot > 2 + lv then
			cot = 2 + lv;
		end
		mid = SquadLib.ApplyModifier(sid, 0, 0.0, 0.0, def, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, cot);
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
	if eqtype == 1 then
		if mid ~= "" then
			SquadLib.RemoveModifier(sid, mid);
		end
		
		if eqid ~= "none" then
			local lv = SquadLib.GetEffectLevel(sid, eid);
			local attr = SquadLib.GetEquipAttr(1, eqid, 2);
			local def = 0;
			if attr < 0 then
				def = -attr;
			end
			if def > 1 + lv then
				def = 1 + lv;
			end
			attr = SquadLib.GetEquipAttr(1, eqid, 9);
			local cot = 0;
			if attr < 0 then
				cot = -attr;
			end
			if cot > 2 + lv then
				cot = 2 + lv;
			end
			mid = SquadLib.ApplyModifier(sid, 0, 0.0, 0.0, def, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, cot);
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
	if eqtype == 1 then
		if mid ~= "" then
			SquadLib.RemoveModifier(sid, mid);
			ScriptCommonLib.SetString("modifierid", "");
		end
	end
end