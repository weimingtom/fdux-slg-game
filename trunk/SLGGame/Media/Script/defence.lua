function useskill()
	skillcaster  = ScriptCommonLib.GetString("skillcaster");
	skillcasterpath = ScriptCommonLib.GetString("skillcasterpath");
	id = SkillLib.ApplyEffect(skillcasterpath,"Defence");
	ScriptCommonLib.SetString("Effectid",id);
	ScriptCommonLib.SetInt("skillcast",1);
end

function onaffect()
	squadpath = ScriptCommonLib.GetString("affectsquadpath");
	squad = ScriptCommonLib.GetSquadIdFromPath(squadpath);
	apleft = SkillLib.GetSquadApLeft(squad);
	if apleft > 6 then
		apleft = 6;
	end
	apleft = apleft / 2;
	id = SkillLib.ApplyModifier(squadpath,2,0.0,0.0,apleft,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
	ScriptCommonLib.SetString("Modifierid",id);
	ScriptCommonLib.SetInt("LastTurn",0);
	trigerid = TriggerLib.AddSquadTrigger(squadpath,"TurnStart","onturnstart");
	TriggerLib.ActiveSquadTrigger(squadpath,trigerid);
	ScriptCommonLib.SetString("TurnStartTrigger",trigerid);
end

function onremove()
	squadpath = ScriptCommonLib.GetString("affectsquadpath");
	id = ScriptCommonLib.GetString("Modifierid");
	SkillLib.RemoveModifier(squadpath,id);
	id = ScriptCommonLib.GetString("TurnStartTrigger");
	TriggerLib.RemoveSquadTrigger(squadpath,id);
end

function onturnstart()
	turn = ScriptCommonLib.GetInt("LastTurn");
	turn = turn + 1;
	ScriptCommonLib.SetInt("LastTurn",turn);
	if turn == 1 then
		squadpath = ScriptCommonLib.GetString("affectsquadpath");
		id = ScriptCommonLib.GetString("effectid");
		SkillLib.RemoveEffect(squadpath, id);
	end
end

