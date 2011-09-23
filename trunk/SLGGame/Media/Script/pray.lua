function useskill()
	skillcaster  = ScriptCommonLib.GetString("skillcaster");
	unitnum = SkillLib.GetUnitNum(skillcaster);
	apleft = SkillLib.GetSquadApLeft(skillcaster);
	if apleft > 5 then
		unitnum = unitnum + 3;
	elseif apleft > 3 then
		unitnum = unitnum + 2;
	elseif apleft > 1 then
		unitnum = unitnum + 1;
	end
	unitmaxnum = SkillLib.GetUnitMaxNum(skillcaster);
	if unitnum > unitmaxnum then
		unitnum = unitmaxnum;
	end
	SkillLib.SetUnitNum(skillcaster, unitnum);
	ScriptCommonLib.SetInt("skillcast",1);
end