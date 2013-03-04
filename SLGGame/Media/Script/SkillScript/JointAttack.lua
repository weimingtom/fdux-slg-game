function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	
	local ep = 30;
	
	local croodx, croody = SquadLib.GetSquadCoord(target);
	local sf = SquadLib.GetFaction(caster);
	local atk = - 2;
	local croodlist = {
		{croodx - 1, croody},
		{croodx, croody - 1},
		{croodx + 1, croody},
		{croodx, croody + 1},
	};
	for i = 1, 4 do
		local tgtsid = BattleLib.GetSquadAt(croodlist[i][1], croodlist[i][2], 1, sf);
		if tgtsid ~= "" then
			local tgtf = SquadLib.GetFaction(tgtsid);
			if tgtf == sf then
				atk = atk + 2;
				ep = ep + 15;
			end
		end
	end	
	
	local mid = SquadLib.ApplyModifier(caster, 0, atk, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	
	local re = SkillLib.MeleeCombat(caster,target);
	if re>0 then
		local casterlv = SquadLib.GetSquadLevel(caster);
		local targetlv = SquadLib.GetSquadLevel(target);

		if targetlv > casterlv then
			ep = ep + (targetlv - casterlv) * 3;
		end
		
		SquadLib.AddExp(caster, ep);
		ScriptCommonLib.SetTempInt("castsuccess", 1);
	end
	SquadLib.RemoveModifier(caster, mid);
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