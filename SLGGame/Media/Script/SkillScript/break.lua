function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	squad1num = SquadLib.GetUnitNum(caster);
	squad2num = SquadLib.GetUnitNum(target);
	re = SkillLib.MeleeCombat(caster,target);
	if re>0 then
		ep = 60;
		if targetlv > casterlv then
			ep = ep + (targetlv - casterlv) * 6;
		end
		squad1lost = squad1num - SquadLib.GetUnitNum(caster);
		squad2lost = squad2num - SquadLib.GetUnitNum(target);
		point = squad2lost - squad1lost + ScriptCommonLib.GetRand(0, 20);
		if point > 15 then
			SquadLib.ChangeFormation(target, 2);
			ep = ep + 20;
		end
		SquadLib.AddExp(caster, ep);
		ScriptCommonLib.SetTempInt("castsuccess", 1);
	end
end

function validtarget()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	casterfaction = SquadLib.GetFaction(caster);
	targetfaction = SquadLib.GetFaction(target);
	if casterfaction ~= targetfaction then
		ScriptCommonLib.SetTempInt("validtarget", 1);
	end
end