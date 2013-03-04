function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local re = SkillLib.MeleeCombat(caster,target);
	if re>0 then
		local casterlv = SquadLib.GetSquadLevel(caster);
		local targetlv = SquadLib.GetSquadLevel(target);
		local ep = 40;
		if targetlv > casterlv then
			ep = ep + (targetlv - casterlv) * 4;
		end
		
		local squadtype = SquadLib.GetType(target);
		if squadtype == 0 then
			local maxnum = SquadLib.GetUnitMaxNum(target);
			local num = SquadLib.GetUnitNum(target);
			if maxnum - num > 10 then
				maxnum = maxnum - 10;
				ep = ep + 20;
			else
				maxnum = num;
				ep = ep + (maxnum - num) * 2;
			end
			SquadLib.SetUnitMaxNum(target, maxnum);
		end
		SquadLib.AddExp(caster, ep);
		ScriptCommonLib.SetTempInt("castsuccess", 1);
	end
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