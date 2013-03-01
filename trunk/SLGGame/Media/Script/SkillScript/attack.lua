function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local re = SkillLib.MeleeCombat(caster,target);
	if re>0 then
		local casterlv = SquadLib.GetSquadLevel(caster);
		local targetlv = SquadLib.GetSquadLevel(target);
		local ep = 50;
		if targetlv > casterlv then
			ep = ep + (targetlv - casterlv) * 5;
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