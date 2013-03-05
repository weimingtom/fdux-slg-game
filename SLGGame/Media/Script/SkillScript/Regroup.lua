function useskill()
	local sid = ScriptCommonLib.GetTempString("squadid");
	
	SquadLib.Animation(sid, 1, "Skill", "none", "none", 0, 1);
	
	local ep = 0;
	local tgtx = ScriptCommonLib.GetTempInt("targetx");
	local tgty = ScriptCommonLib.GetTempInt("targety");
	local sf = SquadLib.GetFaction(sid);
	local croodlist = {
		{tgtx, tgty},
		{tgtx - 1, tgty},
		{tgtx, tgty - 1},
		{tgtx + 1, tgty},
		{tgtx, tgty + 1},
	};
	local lv = SquadLib.GetSkillLevel(sid, "Inspire");
	for i = 1, 5 do
		local tgtsid = BattleLib.GetSquadAt(croodlist[i][1], croodlist[i][2], 1, sf);
		if tgtsid ~= "" then
			local tgtf = SquadLib.GetFaction(tgtsid);
			if tgtf == sf then
				local elv, eid = SquadLib.GetEffectLevelByName(tgtsid, "Waver");
				if elv > 2 and lv > 1 then
					SquadLib.RemoveEffect(tgtsid, eid);
				end
				if elv > 1 then
					SquadLib.RemoveEffect(tgtsid, eid);
					ep = ep + 10;
				end
				if elv > 0 then
					SquadLib.RemoveEffect(tgtsid, eid);
					ep = ep + 10;
				end
			end
		end
	end	
	SquadLib.AddExp(sid, ep);
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validaffectarea()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local tgtx = ScriptCommonLib.GetTempInt("targetx");
	local tgty = ScriptCommonLib.GetTempInt("targety");
	local sf = SquadLib.GetFaction(sid);
	local tgtsid = BattleLib.GetSquadAt(tgtx, tgty, 1, sf);
	if tgtsid ~= "" then
		local tgtf = SquadLib.GetFaction(tgtsid);
		if tgtf == sf then
			ScriptCommonLib.SetTempInt("validaffectarea", 1);
		else
			ScriptCommonLib.SetTempInt("validaffectarea", 0);
		end
	else
		ScriptCommonLib.SetTempInt("validaffectarea", 1);
	end
end