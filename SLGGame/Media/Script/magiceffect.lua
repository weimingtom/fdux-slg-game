function onlearn()
	squadpath = ScriptCommonLib.GetString("skillcasterpath");
	id = SkillLib.ApplyEffect(squadpath,"TestEffect");
	ScriptCommonLib.SetString("Effectid",id);
end

function onaffect()
	squadpath = ScriptCommonLib.GetString("affectsquadpath");
	id = SkillLib.ApplyParticle(squadpath,1,"mp_flare_06");
	ScriptCommonLib.SetString("Effectid",id);
	id = SkillLib.ApplyModifier(squadpath);
	ScriptCommonLib.SetString("Modifierid",id);
end

function onremove()
	squadpath = ScriptCommonLib.GetString("affectsquadpath");
	id = ScriptCommonLib.GetString(squadpath,"Effectid");
	SkillLib.RemoveParticle(id);
	id = ScriptCommonLib.GetString(squadpath,"Modifierid");
	SkillLib.RemoveModifier(id);
end