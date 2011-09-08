function useskill()
	skillcaster  = ScriptCommonLib.GetString("skillcaster");
	apleft = SkillLib.GetSquadApLeft(skillcaster);
	moralerev = apleft * 3;
	if moralerev > 12 then
		moralerev = 12;
	end
	SkillLib.SetMorale(skillcaster, moralerev, 1);
	ScriptCommonLib.SetInt("skillcast",1);
end