function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local x, y = SquadLib.GetSquadCoord(target);
	if x >  -1 then
		local atk = 0;
		local def = MapLib.GetGroundAttr(x, y, 0);
		if def > 0 then
			atk = atk + def * 1.5;
		end
		local mid = SquadLib.ApplyModifier(caster, 0, 0.0, atk, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		re = SkillLib.RangedAttack(caster,target);
		if re > 0 then
			local effectlv, eid = SquadLib.GetEffectLevelByName(caster, "DoubleShoot");
			if effectlv > 0 then
				if SquadLib.GetUnitNum(target) > 0 then
					SkillLib.RangedAttack(caster,target);
				end
			end
			SquadLib.PlayParticle(target, 1, "mp_explosion_02", "none", 2500);
			local casterlv = SquadLib.GetSquadLevel(caster);
			local targetlv = SquadLib.GetSquadLevel(target);
			local ep = 50;
			if targetlv > casterlv then
				ep = ep + (targetlv - casterlv) * 5;
			end	
			SquadLib.AddExp(caster, ep);
			ScriptCommonLib.SetTempInt("castsuccess", 1);
		end
		SquadLib.RemoveModifier(caster, mid);
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