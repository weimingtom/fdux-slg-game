function useskill()
	local caster  = ScriptCommonLib.GetTempString("squadid");
	local target  = ScriptCommonLib.GetTempString("targetsquadid");
	local atk = 0;
	local wlv, wid = SquadLib.GetEffectLevelByName(target, "Waver");
	local clv, cid = SquadLib.GetEffectLevelByName(target, "Chaos");
	local sklv = SquadLib.GetSkillLevel(caster, "Assault");
	atk = wlv + clv;
	if atk >  2 + 2 * sklv then
		atk = 2 + 2 * sklv;
	end
	local mid = SquadLib.ApplyModifier(caster, 0, atk, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
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