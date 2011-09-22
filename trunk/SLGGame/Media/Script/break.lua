function useskill()
	attacker  = ScriptCommonLib.GetString("skillcaster");
	defender  = ScriptCommonLib.GetString("skilltarget");
	attackerpath = ScriptCommonLib.GetString("skillcasterpath");
	unitnum1 = SkillLib.GetUnitNum(defender);
	id = SkillLib.ApplyModifier(attackerpath,2,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
	re = SkillLib.MeleeCombat(attacker,defender);
	SkillLib.RemoveModifier(attackerpath,id);
	if re>0 then
		unitnum2 = SkillLib.GetUnitNum(defender);
		roll = unitnum1 - unitnum2 + ScriptCommonLib.GetRand(0,19);
		if roll > 20 then
			SkillLib.ChangeFormation(defender,2);
		end
		ScriptCommonLib.SetInt("skillcast",1);
	end
end