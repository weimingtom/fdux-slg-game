function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local x, y = SquadLib.GetSquadCoord(target);
	if x >  -1 then
		local re = SkillLib.RangedAttack(caster,target);
		if re > 0 then
			local effectlv, eid = SquadLib.GetEffectLevelByName(caster, "DoubleShoot");
			if effectlv > 0 then
				if SquadLib.GetUnitNum(target) > 0 then
					SkillLib.RangedAttack(caster,target);
				end
			end
			local casterlv = SquadLib.GetSquadLevel(caster);
			local targetlv = SquadLib.GetSquadLevel(target);
			local ep = 40;
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
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local casterfaction = SquadLib.GetFaction(caster);
	local targetfaction = SquadLib.GetFaction(target);
	if casterfaction ~= targetfaction then
		ScriptCommonLib.SetTempInt("validtarget", 1);
	end
end