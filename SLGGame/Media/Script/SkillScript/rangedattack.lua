function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	x, y = SquadLib.GetSquadCoord(target);
	if x >  -1 then
		re = SkillLib.RangedAttack(caster,target);
		if re > 0 then
			effectlv, eid = SquadLib.GetEffectLevelByName(caster, "DoubleShoot");
			if effectlv > 0 then
				if SquadLib.GetUnitNum(target) > 0 then
					SkillLib.RangedAttack(caster,target);
				end
			end
			casterlv = SquadLib.GetSquadLevel(caster);
			targetlv = SquadLib.GetSquadLevel(target);
			ep = 40;
			if targetlv > casterlv then
				ep = ep + (targetlv - casterlv) * 4;
			end
			SquadLib.AddExp(caster, ep);			
			ScriptCommonLib.SetTempInt("castsuccess", 1);
		end
	end
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
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