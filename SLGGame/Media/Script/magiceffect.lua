function onlearn()
	squadpath = ScriptCommonLib.GetString("skillcasterpath");
	id = SkillLib.ApplyEffect(squadpath,"TestEffect");
	ScriptCommonLib.SetString("Effectid",id);
end

function onaffect()
	squadpath = ScriptCommonLib.GetString("affectsquadpath");
	id = SkillLib.ApplyParticle(squadpath,2,"mp_flare_06");
	ScriptCommonLib.SetString("Particleid",id);
	id = SkillLib.ApplyModifier(squadpath,3,5.0,0.0,5.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
	ScriptCommonLib.SetString("Modifierid",id);
end

function onremove()
	squadpath = ScriptCommonLib.GetString("affectsquadpath");
	id = ScriptCommonLib.GetString("Particleid");
	SkillLib.RemoveParticle(squadpath,id);
	id = ScriptCommonLib.GetString("Modifierid");
	SkillLib.RemoveModifier(squadpath,id);
end