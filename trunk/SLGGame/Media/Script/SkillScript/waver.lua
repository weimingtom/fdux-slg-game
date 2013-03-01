function onaffect()
	local mid = ScriptCommonLib.GetString("modifierid");
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetTempString("effectid");
	local tid = ScriptCommonLib.GetString("triggerid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	local lv = SquadLib.GetEffectLevel(sid, eid);
	local apdown = 0;
	if lv > 4 then
		apdown = -lv + 4;
	end
	mid = SquadLib.ApplyModifier(sid, 1, -lv * 0.5, -lv * 0.5, -lv * 0.5, 0.0, 0.0, apdown, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnStart", "onturnstart");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	ScriptCommonLib.SetString("effectid", eid);
	--curlv = ScriptCommonLib.GetInt("curlevel");
	--if lv > curlv then
	--	SquadLib.ShowValue(sid, "Skills_Waver", 1.0, 0.0, 0.0);
	--end
	-- ScriptCommonLib.SetInt("curlevel", lv);
	
	--´«²¥¶¯Ò¡
	ScriptCommonLib.SetInt("spread", 1);
	if lv > 4 then
		local sf = SquadLib.GetFaction(sid);
		local croodx, croody = SquadLib.GetSquadCoord(sid);
		local croodlist = {
			{croodx - 1, croody},
			{croodx, croody - 1},
			{croodx, croody + 1},
			{croodx + 1, croody},
		};
		for i = 1, 4 do
			local tgtsid = BattleLib.GetSquadAt(croodlist[i][1], croodlist[i][2], 1, sf);
			if tgtsid ~= "" then
				local tgtf = SquadLib.GetFaction(tgtsid);
				if tgtf == sf then
					SquadLib.ApplyEffect(tgtsid, "Waver");
				end
			end
		end
	end
	ScriptCommonLib.SetInt("spread", 0);
end

function onremove()
	local mid = ScriptCommonLib.GetString("modifierid");
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tid = ScriptCommonLib.GetString("triggerid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
end

function onturnstart()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local eid = ScriptCommonLib.GetString("effectid");
	SquadLib.RemoveEffect(sid, eid);
end

function canaffect()
	local squadid = ScriptCommonLib.GetTempString("squadid");
	local spread = ScriptCommonLib.GetInt("spread");
	local unshakable, eid = SquadLib.GetEffectLevelByName(squadid, "Unshakable");
	if unshakable > 0 or spread == 1 then
		ScriptCommonLib.SetTempInt("affect", 0);
	else
		ScriptCommonLib.SetTempInt("affect", 1);
	end
end