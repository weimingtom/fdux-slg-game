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
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "Unknow");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "Unknow");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "Unknow");
	BattleLib.AssignAIGroup(2, "Team2Squad_3", "Unknow");
	BattleLib.AssignAIGroup(2, "Team2Squad_4", "Unknow");
	BattleLib.AssignAIGroup(2, "Team2Squad_5", "Unknow");
	--创建AI任务(team,missionname,missiontype,missiontargetarea)
	BattleLib.CreateAIMission(2, "Defend", 0, "KeyArea");
	--指派AI分组任务(team,groupname,missionname)
	BattleLib.AssignAIMission(2, "Unknow", "Defend");
	
	--创建任务(missionname,missionstate)
	mainmission = BattleLib.AddPlayerMission("map4mission1",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	mission1 = BattleLib.AddPlayerMission("map4mission2",0);
	mission2 = BattleLib.AddPlayerMission("map4mission3",0);
	ScriptCommonLib.SetInt("mission1", mission1);
	ScriptCommonLib.SetInt("mission2", mission2);
	ScriptCommonLib.SetInt("mission1state", 1);
	ScriptCommonLib.SetInt("mission2state", 1);
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
		BattleLib.AddGold(120);
		addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 120;
		ScriptCommonLib.SetInt("addedgold", addedgold);
		if BattleLib.TeamSquadLeft(2) == 0 then
			BattleLib.AddGold(1850);
			BattleLib.DumpSquadData();
			addedgold = ScriptCommonLib.GetInt("addedgold");
			addedgold = addedgold + 1850;
			mission1state = ScriptCommonLib.GetInt("mission1state");
			mission2state = ScriptCommonLib.GetInt("mission2state");
			if mission1state == 1then
				BattleLib.AddGold(800);
				addedgold = addedgold + 800;
			end
			if mission2state == 1then
				BattleLib.AddGold(800);
				addedgold = addedgold + 800;
			end
			ScriptCommonLib.SetInt("addedgold", addedgold);
			--胜利(storyscript,gold,exp)
			BattleLib.Win("cp9.lua", "0", "0");
		end
	end
	if faction == 0 then
        ScriptCommonLib.SetInt("mission1state", 0);
		mission1 = ScriptCommonLib.GetInt("mission1");
		BattleLib.SetPlayerMission(mission1, 2);
	end
end

function turnstart()
	turn = ScriptCommonLib.GetTempInt("turn");
	team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and turn == 2 then
	    BattleLib.Story("cp8_1.lua");
	end
end	
		
--回合结束触发器
function turnend()
	turn = ScriptCommonLib.GetTempInt("turn");
	team = ScriptCommonLib.GetTempInt("team");
	
	if team == 1 and BattleLib.TeamSquadLeft(2) == 0 then
		BattleLib.AddGold(1850);
		BattleLib.DumpSquadData();
		addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 1850;
		mission1state = ScriptCommonLib.GetInt("mission1state");
		mission2state = ScriptCommonLib.GetInt("mission2state");
		if mission1state == 1then
			BattleLib.AddGold(800);
			addedgold = addedgold + 800;
		end
		if mission2state == 1then
			BattleLib.AddGold(800);
			addedgold = addedgold + 800;
		end
		ScriptCommonLib.SetInt("addedgold", addedgold);
		--胜利(storyscript,gold,exp)
		BattleLib.Win("cp9.lua", "0", "0");
	end
	if team == 1 and turn > 10 then
	    mission2 = ScriptCommonLib.GetInt("mission2");
		BattleLib.SetPlayerMission(mission2, 2);
	    ScriptCommonLib.SetInt("mission2state", 0);
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