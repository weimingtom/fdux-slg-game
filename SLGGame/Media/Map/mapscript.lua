function initmap()
	trigerid = MapLib.AddMapTrigger("FinishDeploy","finishdeploy");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("finishdeploytriger",trigerid);
	
	ScriptCommonLib.PlayMusic("battle1.mp3");
	MapLib.SetCamera(0,4);
end

function finishdeploy()
	trigerid = ScriptCommonLib.GetString("finishdeploytriger");
	MapLib.RemoveMapTrigger(trigerid);
	
	trigerid = MapLib.AddMapTrigger("SquadAnnihilated","unitdead");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("unitdeadtriger",trigerid);
	trigerid = MapLib.AddMapTrigger("TurnEnd","turnend");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("turnendtriger",trigerid);
	
	--BattleLib.CreateAIGroup(2, "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "DuxRaider");
	BattleLib.CreateAIMission(2, "EliminateTeam1", 1, 1);
	BattleLib.AssignAIMission(2, "DuxRaider", "EliminateTeam1");
end

function unitdead()
	squad = ScriptCommonLib.GetTempString("squadid");
	if squad == "Cheetah" or squad == "Dandelion" then
		BattleLib.ChangeState(2,"GameOver.lua");
	end
end

function turnend()
	turn = ScriptCommonLib.GetTempInt("trun");
	team = ScriptCommonLib.GetTempInt("team");
	
	if team == 1 and turn == 2 then
		BattleLib.Story("battlestory1.lua");
	end
	
	if team == 1 then
		if BattleLib.TeamSquadLeft(2) == 2 then
			if turn < 6 then
				BattleLib.AddGold(500);
			end
			BattleLib.AddGold(2000);
			BattleLib.DumpSquadData();
			BattleLib.ChangeState(2,"Chapter2.lua");
		elseif BattleLib.TeamSquadLeft(2) == 0 then
			if turn < 6 then
				BattleLib.AddGold(500);
			end
			BattleLib.AddGold(2500);
			BattleLib.DumpSquadData();
			BattleLib.ChangeState(2,"Chapter2.lua");
		end
	end
end