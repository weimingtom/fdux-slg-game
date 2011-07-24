function useskill()
	attacker  = ScriptCommonLib.GetString("skillcaster");
	defender  = ScriptCommonLib.GetString("skilltarget");
	x ,y = ScriptCommonLib.GetSquadCoord(defender);
	SkillLib.Missile(attacker,x,y,1,"mp_seal_03","Skill","Skill.mp3",1,"none","mp_hit_02","se03.wav");
	woundnum = SkillLib.GetWoundNum(defender);
	unitnum = SkillLib.GetUnitNum(defender);
	woundnum = woundnum + 15;
	if woundnum > unitnum then
		woundnum = unitnum;
	end
	SkillLib.SetWoundNum(defender, woundnum);
	ScriptCommonLib.SetInt("skillcast",1);
end