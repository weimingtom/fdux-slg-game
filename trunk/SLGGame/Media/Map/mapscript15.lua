function initmap()
	trigerid = MapLib.AddMapTrigger("FinishDeploy","finishdeploy");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("finishdeploytriger",trigerid);
	
	ScriptCommonLib.PlayMusic("battle1.ogg");
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
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "Guard");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "Guard");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "Guard");
	BattleLib.AssignAIGroup(2, "Team2Squad_3", "Guard");
	BattleLib.AssignAIGroup(2, "Team2Squad_4", "Guard");
	
	BattleLib.AssignAIGroup(3, "Team3Squad_0", "Winfred");
	BattleLib.AssignAIGroup(3, "Team3Squad_1", "Winfred");
	BattleLib.AssignAIGroup(3, "Team3Squad_2", "Winfred");
	--创建AI任务(team,missionname,missiontype,missiontargetarea)
	BattleLib.CreateAIMission(2, "Attack1", 0, "DeployArea");
	BattleLib.CreateAIMission(3, "Attack2", 0, "DeployArea");
	BattleLib.CreateAIMission(3, "Attack3", 0, "TargetArea");
	--指派AI分组任务(team,groupname,missionname)
	BattleLib.AssignAIMission(2,"Noth", "Attack1");
	BattleLib.AssignAIMission(3,"Winfred", "Attack2");
	BattleLib.AssignAIMission(3,"Winfred2", "Attack3");
	
	--创建任务(missionname,missionstate)
	mainmission = BattleLib.AddPlayerMission("map15mission1",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	mission1 = BattleLib.AddPlayerMission("map15mission2",0);
	ScriptCommonLib.SetInt("mission1", mission1);
	ScriptCommonLib.SetInt("mission1state", 1);
	ScriptCommonLib.SetInt("addedgold", 0);
end

--部队被歼灭触发器
function unitdead()
	squad = ScriptCommonLib.GetTempString("squadid");
	
	if BattleLib.TeamSquadLeft(1) == 0  then
		--失败(storyscript,gold,exp)
		BattleLib.Lost("GameOver.lua","0","0");
	end
	faction = SquadLib.GetFaction(squad);
	if faction == 1 then
		BattleLib.AddGold(100);
		addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 100;
		ScriptCommonLib.SetInt("addedgold", addedgold);
		mission1state = ScriptCommonLib.GetInt("mission1state");
		if BattleLib.TeamSquadLeft(2) == 0 and mission1state == 1 then
			BattleLib.AddGold(1500);
			BattleLib.DumpSquadData();
			addedgold = ScriptCommonLib.GetInt("addedgold");
			addedgold = addedgold + 1500;
			if mission1state == 1 then
				BattleLib.AddGold(1000);
				addedgold = addedgold + 1000;
			end
			ScriptCommonLib.SetInt("addedgold", addedgold);
			--胜利(storyscript,gold,exp)
			BattleLib.Win("cp31.lua", "0", "0");
		end
	end
end

function turnstart()
	turn = ScriptCommonLib.GetTempInt("turn");
	team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and turn == 1 then
	    BattleLib.Story("cp30_1.lua");
	end
	if team == 1 and turn == 3 then
	    BattleLib.Story("cp30_2.lua");
		AVGLib.SetCanSupply("WingsHeavyInf",1);
		AVGLib.SetCanSupply("WingsCrossBow",1);
		AVGLib.SetCanSupply("Fay",1);
		AVGLib.SetCanSupply("Cheetah",1);
		BattleLib.CreateStorySquad ("WingsHeavyInf", "WingsHeavyInf", 1, 3, false);
		BattleLib.CreateStorySquad ("WingsCrossBow", "WingsCrossBow", 0, 2, false);
		BattleLib.CreateStorySquad ("Fay", "Fay", 1, 2, false);
		BattleLib.CreateStorySquad ("Cheetah", "Cheetah", 2, 2, false);
	end
	if team == 1 and turn == 9 then
	    BattleLib.AddBattleSquad("James", "Team3Squad_3", 3, 6, 3, 50);
		BattleLib.AddBattleSquad("WinfredLightCavalry", "Team3Squad_4", 1, 5, 3, 50);
		BattleLib.AddBattleSquad("WinfredLightCavalry", "Team3Squad_5", 1, 7, 3, 50);
		BattleLib.AddBattleSquad("WinfredHeavyCavalry", "Team3Squad_6", 2, 5, 3, 50);
		BattleLib.AddBattleSquad("WinfredHeavyCavalry", "Team3Squad_7", 2, 7, 3, 50);
		BattleLib.AddBattleSquad("WinfredHeavyHalberd", "Team3Squad_8", 0, 5, 3, 50);
		BattleLib.AddBattleSquad("WinfredHeavyHalberd", "Team3Squad_9", 0, 7, 3, 50);
		BattleLib.AddBattleSquad("WinfredLightBow", "Team3Squad_10", 0, 4, 3, 50);
		BattleLib.AddBattleSquad("WinfredLightBow", "Team3Squad_11", 0, 8, 3, 50);
		
		BattleLib.AssignAIGroup(3, "Team3Squad_3", "Winfred2");
		BattleLib.AssignAIGroup(3, "Team3Squad_4", "Winfred2");
		BattleLib.AssignAIGroup(3, "Team3Squad_5", "Winfred2");
		BattleLib.AssignAIGroup(3, "Team3Squad_6", "Winfred2");
		BattleLib.AssignAIGroup(3, "Team3Squad_7", "Winfred2");
		BattleLib.AssignAIGroup(3, "Team3Squad_8", "Winfred2");
		BattleLib.AssignAIGroup(3, "Team3Squad_9", "Winfred2");
		BattleLib.AssignAIGroup(3, "Team3Squad_10", "Winfred2");
		BattleLib.AssignAIGroup(3, "Team3Squad_11", "Winfred2");
		
		BattleLib.Story("cp30_5.lua");
		mission1 = ScriptCommonLib.GetInt("mission1");
		--完成任务(missionindex, missionstate)
		BattleLib.SetPlayerMission(mission1, 2);
		ScriptCommonLib.SetInt("mission1state", 0);
		mainmission = BattleLib.AddPlayerMission("map15mission3",0);
		ScriptCommonLib.SetInt("mainmission", mainmission);
	end

end	
		
--回合结束触发器
function turnend()
	turn = ScriptCommonLib.GetTempInt("turn");
	team = ScriptCommonLib.GetTempInt("team");
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
	faction = SquadLib.GetFaction(squad);
	mission1state = ScriptCommonLib.GetInt("mission1state");
	
	if faction == 0 and area == "TargetArea" and mission1state == 0 then
		BattleLib.AddGold(1500);
		BattleLib.DumpSquadData();
		addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 1500;
		mission1state = ScriptCommonLib.GetInt("mission1state");
		ScriptCommonLib.SetInt("addedgold", addedgold);
		--胜利(storyscript,gold,exp)
		BattleLib.Win("cp31.lua", "0", "0");
	end
end