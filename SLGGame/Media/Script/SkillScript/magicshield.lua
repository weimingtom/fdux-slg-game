function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	eid = SquadLib.ApplyEffect(caster, "MagicShield");
    --SquadLib.AddParticle(caster, "mp_seal_02", 1);
    SquadLib.AddParticle(caster, "mp_hit_12", 3);
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function onaffect()

end

function onremove()

end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	caster  = ScriptCommonLib.GetTempString("squadid");
	target  = ScriptCommonLib.GetTempString("targetsquadid");
	casterfaction = SquadLib.GetFaction(caster);
	targetfaction = SquadLib.GetFaction(target);
	if casterfaction == targetfaction then
		ScriptCommonLib.SetTempInt("validtarget", 1);
    else
        ScriptCommonLib.SetTempInt("validtarget", 0);
	end
end