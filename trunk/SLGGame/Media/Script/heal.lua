function useskill()
	attacker  = ScriptCommonLib.GetString("skillcaster");
	defender  = ScriptCommonLib.GetString("skilltarget");
	SkillLib.Action(attacker,1,"mp_seal_02","Skill","magicSkill1.mp3");
	SkillLib.SquadParticle(defender,3,"mp_streak_01","none",3000);
	woundnum = SkillLib.GetWoundNum(defender);
	woundrev = 15;
	if woundrev > woundnum then
		woundrev = woundnum;
	end
	SkillLib.SetWoundNum(defender, woundnum - woundrev);
	ScriptCommonLib.SetInt("skillcast",1);
end