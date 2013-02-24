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
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "WinfredRider");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "WinfredRider");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "WinfredRider");
	BattleLib.AssignAIGroup(2, "Team2Squad_3", "WinfredRider");
	BattleLib.AssignAIGroup(2, "Team2Squad_4", "WinfredRider");
	BattleLib.AssignAIGroup(2, "Team2Squad_5", "WinfredRider");
	BattleLib.AssignAIGroup(2, "Team2Squad_6", "WinfredRider");
	BattleLib.AssignAIGroup(2, "Team2Squad_7", "WinfredRider");
	BattleLib.AssignAIGroup(2, "Team2Squad_8", "Winfred");
	BattleLib.AssignAIGroup(2, "Team2Squad_9", "Winfred");
	BattleLib.AssignAIGroup(2, "Team2Squad_10", "Winfred");
	BattleLib.AssignAIGroup(2, "Team2Squad_11", "Winfred");
	BattleLib.AssignAIGroup(2, "Team2Squad_12", "Winfred");
	BattleLib.AssignAIGroup(2, "Team2Squad_13", "Winfred");
	BattleLib.AssignAIGroup(2, "Team2Squad_14", "Winfred");
	BattleLib.AssignAIGroup(2, "Team2Squad_15", "Winfred");
	

	--创建AI任务(team,missionname,missiontype,missiontargetarea)
	BattleLib.CreateAIMission(2, "Attack1", 0, "DeployArea");
	BattleLib.CreateAIMission(2, "Attack2", 0, "KeyArea1");
	BattleLib.CreateAIMission(2, "Run", 0, "KeyArea2");

	--指派AI分组任务(team,groupname,missionname)
	BattleLib.AssignAIMission(3,"WinfredRider", "Attack1");
	BattleLib.AssignAIMission(3,"Winfred", "Attack2");
	
	--创建任务(missionname,missionstate)
	mainmission = BattleLib.AddPlayerMission("map17mission1",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	mission1 = BattleLib.AddPlayerMission("map17mission2",0);
	ScriptCommonLib.SetInt("mission1", mission1);
	ScriptCommonLib.SetInt("mission1state", 0);
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
		mission1state = mission1state + 1;
		ScriptCommonLib.SetInt("mission1state", mission1state);
		if squad == "Team2Squad_3" then
			BattleLib.Story("cp34_5.lua");
			BattleLib.AddGold(1500);
			BattleLib.DumpSquadData();
			addedgold = ScriptCommonLib.GetInt("addedgold");
			addedgold = addedgold + 1500;
			if mission1state >= 8 then
				BattleLib.AddGold(1000);
				addedgold = addedgold + 1000;
			end
			ScriptCommonLib.SetInt("addedgold", addedgold);
			--胜利(storyscript,gold,exp)
			BattleLib.Win("cp35.lua", "0", "0");
		end
	end
end

function turnstart()
	turn = ScriptCommonLib.GetTempInt("turn");
	team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and turn == 1 then
	    BattleLib.Story("cp34_1.lua");
	end
end	
		
--回合结束触发器
function turnend()
	turn = ScriptCommonLib.GetTempInt("turn");
	team = ScriptCommonLib.GetTempInt("team");

	if team == 1 and turn == 1 then
	    BattleLib.Story("cp34_2.lua");
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
end