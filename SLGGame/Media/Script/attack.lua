function useskill()
	attacker  = ScriptCommonLib.GetString("skillcaster");
	defender  = ScriptCommonLib.GetString("skilltarget");
	re ,  atkdie, atkwond,  defdie, defwond = SkillLib.MeleeCombat(attacker,defender);
	if re>0 then
		ScriptCommonLib.SetInt("skillcast",1);
	end
end