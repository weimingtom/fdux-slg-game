function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	re = SkillLib.MeleeCombat(caster,target);
	if re>0 then
		casterlv = SquadLib.GetSquadLevel(caster);
		targetlv = SquadLib.GetSquadLevel(target);
		ep = 50;
		if targetlv > casterlv then
			ep = ep + (targetlv - casterlv) * 5;
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