function useskill()
	attacker  = ScriptCommonLib.GetString("skillcaster");
	defender  = ScriptCommonLib.GetString("skilltarget");
	defenderpath = ScriptCommonLib.GetString("skilltargetpath");
	id = SkillLib.ApplyEffect(defenderpath,"MagicShield");
	ScriptCommonLib.SetString("Effectid",id);
	SkillLib.Action(attacker,1,"mp_flare_06","Skill","none");
	ScriptCommonLib.SetInt("skillcast",1);
end

function onaffect()
	squadpath = ScriptCommonLib.GetString("affectsquadpath");
	id = SkillLib.ApplyParticle(squadpath,3,"mp_flare_06");
	ScriptCommonLib.SetString("Particleid",id);
	id = SkillLib.ApplyModifier(squadpath,1,0.0,0.0,5.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
	ScriptCommonLib.SetString("Modifierid",id);
	ScriptCommonLib.SetInt("LastTurn",0);
	trigerid = TriggerLib.AddSquadTrigger(squadpath,"TurnEnd","onturnend");
	TriggerLib.ActiveSquadTrigger(squadpath,trigerid);
	ScriptCommonLib.SetString("TurnEndTrigger",trigerid);
end

function onremove()
	squadpath = ScriptCommonLib.GetString("affectsquadpath");
	id = ScriptCommonLib.GetString("Particleid");
	SkillLib.RemoveParticle(squadpath,id);
	id = ScriptCommonLib.GetString("Modifierid");
	SkillLib.RemoveModifier(squadpath,id);
	id = ScriptCommonLib.GetString("TurnEndTrigger");
	TriggerLib.RemoveSquadTrigger(squadpath,id);
end

function onturnend()
	turn = ScriptCommonLib.GetInt("LastTurn");
	turn = turn + 1;
	ScriptCommonLib.SetInt("LastTurn",turn);
	if turn == 4 then
		squadpath = ScriptCommonLib.GetString("affectsquadpath");
		id = ScriptCommonLib.GetString("effectid");
		SkillLib.RemoveEffect(squadpath, id);
	end
end