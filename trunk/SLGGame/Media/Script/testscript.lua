function initmap()
	trigerid = TriggerLib.AddTrigger("FinishDeploy","finishdeploy");
	TriggerLib.ActiveTrigger(trigerid);
	ScriptCommonLib.SetString("finishdeploytriger",trigerid);
	ScriptCommonLib.PlayMusic("battle1.wav");
end

function finishdeploy()
	trigerid = ScriptCommonLib.GetString("finishdeploytriger");
	TriggerLib.DisableTrigger(trigerid);
	trigerid = TriggerLib.AddTrigger("UnitDead","unitdead");
	TriggerLib.ActiveTrigger(trigerid);
	ScriptCommonLib.SetString("unitdeadtriger",trigerid);
	trigerid = TriggerLib.AddTrigger("TurnEnd","turnend");
	TriggerLib.ActiveTrigger(trigerid);
	ScriptCommonLib.SetString("turnendtriger",trigerid);
end

function unitdead()
	squad = ScriptCommonLib.GetString("squad");
	if squad == Cheetah or squad == Dandelion or squad == Olivia then
		TriggerLib.ChangeState(1,"Chapter1_4.lua");
	elseif ScriptCommonLib.GetTeamSquadLeft(2) == 0 then
		TriggerLib.ChangeState(1,"Chapter1_3.lua");
	end
end

function turnend()
	turn = ScriptCommonLib.GetInt("trun");
	team = ScriptCommonLib.GetInt("team");
end