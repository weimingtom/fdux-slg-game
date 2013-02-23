function initmap()
	trigerid = MapLib.AddMapTrigger("FinishDeploy","finishdeploy");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("finishdeploytriger",trigerid);
	
	ScriptCommonLib.PlayMusic("battle2.ogg");
	MapLib.SetCamera(0,4);
end

function finishdeploy()
	trigerid = ScriptCommonLib.GetString("finishdeploytriger");
	MapLib.RemoveMapTrigger(trigerid);
	--创建部队被歼灭触发器
	trigerid = MapLib.AddMapTrigger("SquadAnnihilated","unitdead");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("unitdeadtriger",trigerid);
	--创建回合结束触发器
	trigerid = MapLib.AddMapTrigger("TurnEnd","turnend");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("turnendtriger",trigerid);
	--创建回合开始触发器
	trigerid = MapLib.AddMapTrigger("TurnStart","turnstart");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("turnstarttriger",trigerid);
	--创建进入区域触发器
	trigerid = MapLib.AddMapTrigger("GetOutArea","outarea");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("outareatriger",trigerid);
	--创建离开区域触发器
	trigerid = MapLib.AddMapTrigger("GetInArea","inarea");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("inareatriger",trigerid);
	
	--创建AI分组(team,squadid,groupname)
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "Pirate");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "Pirate");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "Pirate");
	BattleLib.AssignAIGroup(2, "Team2Squad_3", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_4", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_5", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_6", "Pirate");
	BattleLib.AssignAIGroup(2, "Team2Squad_7", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_8", "Pirate");
	BattleLib.AssignAIGroup(2, "Team2Squad_9", "Ulva");
	--创建AI任务(team,missionname,missiontype,missiontargetarea)
	BattleLib.CreateAIMission(2, "AttackCamp", 0, "DeployArea");
	BattleLib.CreateAIMission(2, "Run", 0, "Run");
	--指派AI分组任务(team,groupname,missionname)
	BattleLib.AssignAIMission(2, "Ulva", "AttackCamp");
	BattleLib.AssignAIMission(2, "Pirate", "AttackCamp");
	
	--创建任务(missionname,missionstate)
	mainmission = BattleLib.AddPlayerMission("map3mission1",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	mission1 = BattleLib.AddPlayerMission("map3mission2",0);
	ScriptCommonLib.SetInt("mission1", mission1);
	ScriptCommonLib.SetInt("mission1state", 0);
	
	ScriptCommonLib.SetInt("addedgold", 0);
	ScriptCommonLib.SetInt("battlestory", 0);
end

--部队被歼灭触发器
function unitdead()
	squad = ScriptCommonLib.GetTempString("squadid");
	
	if BattleLib.TeamSquadLeft(1) == 0 then
		--失败(storyscript,gold,exp)
		BattleLib.Lost("GameOver.lua","0","0");
	end
	faction = SquadLib.GetFaction(squad);
	if faction == 1 then
		BattleLib.AddGold(100);
		addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 100;
		ScriptCommonLib.SetInt("addedgold", addedgold);
	end
end

function turnstart()
	turn = ScriptCommonLib.GetTempInt("turn");
	team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and turn == 3 then
	    BattleLib.Story("cp6_1.lua");
		BattleLib.AddBattleSquad("Fay", "Fay", 18, 16, 1, 20);
		BattleLib.AddBattleSquad("Elementalist", "Elementalist", 8, 15, 1, 20);
	end
	if team == 1 and turn == 4 then
	    BattleLib.Story("cp6_2.lua");
		BattleLib.AssignAIMission(2, "Pirate", "Run");
	end
end	
		
--回合结束触发器
function turnend()
	turn = ScriptCommonLib.GetTempInt("turn");
	team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and BattleLib.TeamSquadLeft(2) == 0 then
		BattleLib.AddGold(1500);
		BattleLib.DumpSquadData();
		addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 1500;
		mission1state = ScriptCommonLib.GetInt("mission1state");
		if mission1state <= 3 then
			BattleLib.AddGold(700);
			addedgold = addedgold + 700;
		end
		ScriptCommonLib.SetInt("addedgold", addedgold);
		--胜利(storyscript,gold,exp)
		BattleLib.Win("cp7.lua", "0", "0");
	end
end

--离开区域触发器
function outarea()
	squad = ScriptCommonLib.GetTempString("squadid");
	area = ScriptCommonLib.GetTempString("areaid");
end

--进入区域触发器
function inarea()
	squad = ScriptCommonLib.GetTempString("squadid");
	area = ScriptCommonLib.GetTempString("areaid");
	
	if area == "Run" then
		faction = SquadLib.GetFaction(squad);
		if faction == 1 then
			mission1state = ScriptCommonLib.GetInt("mission1state");
		    mission1state = mission1state + 1;
			ScriptCommonLib.SetInt("mission1state", mission1state);
			if mission1state > 3 then
				mission1 = ScriptCommonLib.GetInt("mission1");
				--任务成功(missionindex, missionstate)
				BattleLib.SetPlayerMission(mission1, 2);
			end
		end
	end
end