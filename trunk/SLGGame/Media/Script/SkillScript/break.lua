function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local squad1num = SquadLib.GetUnitNum(caster);
	local squad2num = SquadLib.GetUnitNum(target);
	local re = SkillLib.MeleeCombat(caster,target);
	if re>0 then
		local ep = 60;
		if targetlv > casterlv then
			ep = ep + (targetlv - casterlv) * 6;
		end
		local squad1lost = squad1num - SquadLib.GetUnitNum(caster);
		local squad2lost = squad2num - SquadLib.GetUnitNum(target);
		local point = squad2lost - squad1lost + ScriptCommonLib.GetRand(0, 20);
		if point > 15 then
			SquadLib.ChangeFormation(target, 2);
			ep = ep + 20;
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