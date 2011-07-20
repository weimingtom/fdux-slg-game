function useskill()
	attacker  = ScriptCommonLib.GetString("skillcaster");
	defender  = ScriptCommonLib.GetString("skilltarget");
	x ,y = ScriptCommonLib.GetSquadCoord(defender);
	SkillLib.Missile(attacker,x,y,1,"mp_flare_06","Skill","Skill.mp3",1,"fireSystem","none","none");
	re = SkillLib.MagicAttack(attacker,defender,15,25.0);
	if re>0 then
		ScriptCommonLib.SetInt("skillcast",1);
	end
end