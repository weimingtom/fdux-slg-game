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
	--创建进入区域触发器
	trigerid = MapLib.AddMapTrigger("GetOutArea","outarea");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("outareatriger",trigerid);
	--创建离开区域触发器
	trigerid = MapLib.AddMapTrigger("GetInArea","inarea");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("inareatriger",trigerid);
	
	--创建AI分组(team,squadid,groupname)
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_3", "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_4", "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_5", "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_6", "DuxRaider");
	--创建AI任务(team,missionname,missiontype,missiontargetarea)
	BattleLib.CreateAIMission(2, "DefendCamp", 0, "CameArea");
	--指派AI分组任务(team,groupname,missionname)
	BattleLib.AssignAIMission(2, "DuxRaider", "DefendCamp");
	
	--创建任务(missionname,missionstate)
	mainmission = BattleLib.AddPlayerMission("（主要）消灭所有敌军",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	mission1 = BattleLib.AddPlayerMission("（次要）占领中央的营地（500金币）",0);
	ScriptCommonLib.SetInt("mission1", mission1);
	ScriptCommonLib.SetInt("mission1state", 0);
	
	ScriptCommonLib.SetInt("addedgold", 0);
	ScriptCommonLib.SetInt("battlestory", 0);
end

--部队被歼灭触发器
function unitdead()
	squad = ScriptCommonLib.GetTempString("squadid");
	
	if squad == "Cheetah" or squad == "Dandelion" then
		--失败(storyscript,gold,exp)
		BattleLib.Lost("GameOver.lua","0","0");
	end
	faction = SquadLib.GetFaction(squad);
	if faction == 1 then
		BattleLib.AddGold(200);
		addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 200;
		ScriptCommonLib.SetInt("addedgold", addedgold);
	end
end

--回合结束触发器
function turnend()
	turn = ScriptCommonLib.GetTempInt("turn");
	team = ScriptCommonLib.GetTempInt("team");
	
	if team == 1 and BattleLib.TeamSquadLeft(2) == 0 then
		BattleLib.AddGold(2500);
		BattleLib.DumpSquadData();
		addedgold = ScriptCommonLib.GetInt("addedgold");
		--胜利(storyscript,gold,exp)
		BattleLib.Win("Chapter2.lua", "0", "0");
	end
	if team == 1 and turn > 1 then
		squad7 = ScriptCommonLib.GetInt("Squad7");
		if squad7 == 0 then
			--创建部队(templetid,squadid,x,y,team,num)
			--同时创建玩家AVG部分部队AddStorySquad参数相同
			re = BattleLib.AddBattleSquad("DuxHeavySpear", "Team2Squad_7", -1, 5, 2, 50);
			if re == 1 then
				BattleLib.AssignAIGroup(2, "Team2Squad_7", "DuxRaider");
				ScriptCommonLib.SetInt("Squad7", 1);
			end
		end
	end
end

--离开区域触发器
function outarea()
	squad = ScriptCommonLib.GetTempString("squadid");
	area = ScriptCommonLib.GetTempString("areaid");
	
	if area == "DeployArea" then
		faction = SquadLib.GetFaction(squadid);
		if faction == 0 then
			bs = ScriptCommonLib.GetInt("battlestory");
			if bs == 0 then
				--战斗剧情
				BattleLib.Story("cp12_5.lua");
				ScriptCommonLib.SetInt("battlestory", 1);
			end
		end
	end
end

--进入区域触发器
function inarea()
	squad = ScriptCommonLib.GetTempString("squadid");
	area = ScriptCommonLib.GetTempString("areaid");
	
	if area == "BigCamp" then
		faction = SquadLib.GetFaction(squadid);
		if faction == 0 then
			mission1state = ScriptCommonLib.GetInt("mission1state");
			if mission1state == 0 then
				mission1 = ScriptCommonLib.GetInt("mission1");
				--完成任务(missionindex, missionstate)
				BattleLib.SetPlayerMission(mission1, 1);
				ScriptCommonLib.SetInt("mission1state", 1);
				
				BattleLib.AddGold(500);
				addedgold = ScriptCommonLib.GetInt("addedgold");
				addedgold = addedgold + 500;
				ScriptCommonLib.SetInt("addedgold", addedgold);
			end
		end
	end
end