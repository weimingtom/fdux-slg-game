function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	squadnum = SquadLib.GetUnitNum(caster);
	form = SquadLib.GetSquadAttr(caster, 3, 0);
	if form < 0 then
		form = 0.0;
	end
	atk = form * squadnum / 50.0;
	mid = SquadLib.ApplyModifier(caster, 0, 0.0, atk, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
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
			ep = 50;
			if targetlv > casterlv then
				ep = ep + (targetlv - casterlv) * 5;
			end	
			SquadLib.AddExp(caster, ep);
			ScriptCommonLib.SetTempInt("castsuccess", 1);
		end
	end
	SquadLib.RemoveModifier(caster, mid);
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