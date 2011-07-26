function useskill()
	attacker  = ScriptCommonLib.GetString("skillcaster");
	defender  = ScriptCommonLib.GetString("skilltarget");
	defenderpath = ScriptCommonLib.GetString("skilltargetpath");
	apleft = SkillLib.GetSquadApLeft(defender);
	apleft = apleft + 4;
	SkillLib.SetSquadApLeft(defender,apleft);
	SkillLib.ApplyEffect(defenderpath,"Zeal");
	SkillLib.Action(attacker,1,"mp_seal_02","Skill","magicSkill1.mp3");
	SkillLib.SquadParticle(defender,3,"mp_diabolique","none",3000);
	ScriptCommonLib.SetInt("skillcast",1);
end

function onaffect()
	squadpath = ScriptCommonLib.GetString("affectsquadpath");
	id = SkillLib.ApplyModifier(squadpath,1,0.0,0.0,0.0,0.0,0.0,2.0,0.0,0.0,0.0,0.0);
	ScriptCommonLib.SetString("Modifierid",id);
	ScriptCommonLib.SetInt("LastTurn",0);
	trigerid = TriggerLib.AddSquadTrigger(squadpath,"TurnEnd","onturnend");
	TriggerLib.ActiveSquadTrigger(squadpath,trigerid);
	ScriptCommonLib.SetString("TurnEndTrigger",trigerid);
end

function onremove()
	squadpath = ScriptCommonLib.GetString("affectsquadpath");
	id = ScriptCommonLib.GetString("Modifierid");
	SkillLib.RemoveModifier(squadpath,id);
	id = ScriptCommonLib.GetString("TurnEndTrigger");
	TriggerLib.RemoveSquadTrigger(squadpath,id);
end

function onturnend()
	turn = ScriptCommonLib.GetInt("LastTurn");
	turn = turn + 1;
	ScriptCommonLib.SetInt("LastTurn",turn);
	if turn == 2 then
		squadpath = ScriptCommonLib.GetString("affectsquadpath");
		id = ScriptCommonLib.GetString("effectid");
		SkillLib.RemoveEffect(squadpath, id);
	end
end