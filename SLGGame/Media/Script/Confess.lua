function useskill()
	attacker  = ScriptCommonLib.GetString("skillcaster");
	unitnum = SkillLib.GetUnitNum(attacker);
	if unitnum > 3 then
		unitnum = unitnum - 2;
		SkillLib.SetUnitNum(attacker, unitnum);
		defender  = ScriptCommonLib.GetString("skilltarget");
		x ,y = ScriptCommonLib.GetSquadCoord(defender);
		SkillLib.Missile(attacker,x,y,1,"mp_seal_03","Skill","Skill.mp3",1,"none","mp_hit_02","se03.wav");
		SkillLib.SetMorale(defender, -15, 1);
		ScriptCommonLib.SetInt("skillcast",1);
	end
end