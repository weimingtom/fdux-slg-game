function initmap()
	trigerid = TriggerLib.AddTrigger("FinishDeploy","finishdeploy");
	TriggerLib.ActiveTrigger(trigerid);
	ScriptCommonLib.SetString("finishdeploytriger",trigerid);
	ScriptCommonLib.PlayMusic("battle1.mp3");
	ScriptCommonLib.SetCamera(0,4);
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
	if squad == "Cheetah" or squad == "Dandelion" or squad == "Olivia" then
		TriggerLib.ChangeState(1,"GameOver.lua");
	elseif ScriptCommonLib.GetTeamSquadLeft(2) == 0 then
		TriggerLib.ChangeState(1,"Chapter3.lua");
	end
end

function turnend()
	turn = ScriptCommonLib.GetInt("trun");
	team = ScriptCommonLib.GetInt("team");
	--if team == 1 then
	--	ScriptCommonLib.PlayMusic("battle4.mp3");
	--elseif team == 2 then
	--	ScriptCommonLib.PlayMusic("battle1.mp3");
	--end
end