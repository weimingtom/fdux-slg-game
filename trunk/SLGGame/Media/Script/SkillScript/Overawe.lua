function useskill()
	local sid = ScriptCommonLib.GetTempString("squadid");
	local ep = 0;
	local tgtx = ScriptCommonLib.GetTempInt("targetx");
	local tgty = ScriptCommonLib.GetTempInt("targety");
	local sf = SquadLib.GetFaction(sid);
	local croodlist = {
		{tgtx - 1, tgty},
		{tgtx, tgty - 1},
		{tgtx + 1, tgty},
		{tgtx, tgty + 1},
	};
	for i = 1, 4 do
		local tgtsid = BattleLib.GetSquadAt(croodlist[i][1], croodlist[i][2], 1, sf);
		if tgtsid ~= "" then
			local tgtf = SquadLib.GetFaction(tgtsid);
			if tgtf ~= sf then
				SquadLib.ApplyEffect(tgtsid, "Waver");
				SquadLib.ApplyEffect(tgtsid, "Waver");
				local sklv = SquadLib.GetSkillLevel(caster, "Overawe");
				if sklv > 1 then
					SquadLib.ApplyEffect(tgtsid, "Waver");
				end
				ep = ep + 30;
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
		if tgtf ~= sf then
			ScriptCommonLib.SetTempInt("validaffectarea", 1);
		end
	end
end