function useskill()
	attacker  = ScriptCommonLib.GetString("skillcaster");
	defender  = ScriptCommonLib.GetString("skilltarget");
	SkillLib.Action(attacker,1,"mp_seal_08","Skill","magicSkill1.mp3");
	woundnum = SkillLib.GetWoundNum(defender);
	woundrev = 15;
	if woundrev > woundnum then
		woundrev = woundnum;
	end
	SkillLib.SetWoundNum(defender, woundnum - woundrev);
	ScriptCommonLib.SetInt("skillcast",1);
end