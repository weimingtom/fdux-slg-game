function useskill()
	skillcaster  = ScriptCommonLib.GetString("skillcaster");
	apleft = SkillLib.GetSquadApLeft(skillcaster);
	woundnum = SkillLib.GetWoundNum(skillcaster);
	woundrev = apleft * 3;
	if woundrev > 15 then
		woundrev = 15;
	end
	if woundrev > woundnum then
		woundrev = woundnum;
	end
	SkillLib.SetWoundNum(skillcaster, woundnum - woundrev);
	ScriptCommonLib.SetInt("skillcast",1);
end