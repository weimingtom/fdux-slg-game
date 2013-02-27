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
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "Noth1");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "Noth1");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "Noth1");
	BattleLib.AssignAIGroup(2, "Team2Squad_3", "Noth2");
	BattleLib.AssignAIGroup(2, "Team2Squad_4", "Noth1");
	BattleLib.AssignAIGroup(2, "Team2Squad_5", "Noth3");
	BattleLib.AssignAIGroup(2, "Team2Squad_6", "Noth2");
	BattleLib.AssignAIGroup(2, "Team2Squad_7", "Noth1");
	BattleLib.AssignAIGroup(2, "Team2Squad_8", "Noth1");
	BattleLib.AssignAIGroup(2, "Team2Squad_9", "Noth1");
	BattleLib.AssignAIGroup(2, "Team2Squad_10", "Noth3");
	BattleLib.AssignAIGroup(2, "Team2Squad_11", "Noth3");
	BattleLib.AssignAIGroup(2, "Team2Squad_12", "Noth1");
	BattleLib.AssignAIGroup(2, "Team2Squad_13", "Noth2");
	BattleLib.AssignAIGroup(2, "Team2Squad_14", "Noth3");
	--创建AI任务(team,missionname,missiontype,missiontargetarea)
	BattleLib.CreateAIMission(2, "Attack", 0, "KeyArea1");
	BattleLib.CreateAIMission(2, "Defend1", 0, "KeyArea2");
	BattleLib.CreateAIMission(2, "Defend2", 0, "KeyArea3");
	--指派AI分组任务(team,groupname,missionname)
	BattleLib.AssignAIMission(2,"Noth1", "Attack");
	BattleLib.AssignAIMission(2,"Noth2", "Defend2");
	BattleLib.AssignAIMission(2,"Noth3", "Defend1");
	
	--创建任务(missionname,missionstate)
	mainmission = BattleLib.AddPlayerMission("map13mission1",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	mission1 = BattleLib.AddPlayerMission("map13mission2",0);
	ScriptCommonLib.SetInt("mission1", mission1);
	ScriptCommonLib.SetInt("mission1state", 0);
	ScriptCommonLib.SetInt("addedgold", 0);
end

--部队被歼灭触发器
function unitdead()
	squad = ScriptCommonLib.GetTempString("squadid");
	
	if BattleLib.TeamSquadLeft(1) == 0 or squad == "Caster" then
		--失败(storyscript,gold,exp)
		BattleLib.Lost("GameOver.lua","0","0");
	end
	faction = SquadLib.GetFaction(squad);
	if faction == 1 then
		BattleLib.AddGold(240);
		addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 240;
		ScriptCommonLib.SetInt("addedgold", addedgold);
		mission1state = ScriptCommonLib.GetInt("mission1state");
		mission1state = mission1state + 1;
		ScriptCommonLib.SetInt("mission1state", mission1state);
		if mission1state >= 4  then
			mission1 = ScriptCommonLib.GetInt("mission1");
			BattleLib.SetPlayerMission(mission1, 1);
		end
	end
end


function turnstart()
	turn = ScriptCommonLib.GetTempInt("turn");
	team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and turn == 1 then
	    BattleLib.Story("cp26_1.lua");
	end
	if team == 1 and turn == 4 then
		MapLib.MoveCameraTo( 18, 8);
		AVGLib.SetCanSupply("Azaria",1);
		AVGLib.SetCanSupply("Caster",1);
		AVGLib.SetCanSupply("Olivia",1);
		BattleLib.AddStorySquad ("Azaria", "Azaria", 18, 8, 1);
		BattleLib.AddStorySquad ("Caster", "Caster", 17, 7, 1);
		BattleLib.AddStorySquad ("Olivia", "Olivia", 18, 7, 1);
		BattleLib.Story("cp26_2.lua");
	end
	if team == 1 and turn == 5 then
		MapLib.MoveCameraTo( 14, 3);
		AVGLib.SetCanSupply("Fay",1);
		BattleLib.AddStorySquad ("Fay", "Fay", 14, 3, 0);
		BattleLib.Story("cp26_5.lua");
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
	
	if area == TargetArea then
		faction = SquadLib.GetFaction(squad);
		if faction == 0 then
			BattleLib.Story("cp26_6.lua");
			BattleLib.AddGold(4400);
			BattleLib.DumpSquadData();
			addedgold = ScriptCommonLib.GetInt("addedgold");
			addedgold = addedgold + 4400;
			mission1state = ScriptCommonLib.GetInt("mission1state");
			if mission1state >= 4 then
				BattleLib.AddGold(2700);
				addedgold = addedgold + 2700;
			end
			ScriptCommonLib.SetInt("addedgold", addedgold);
			--胜利(storyscript,gold,exp)
			BattleLib.Win("cp27.lua", "0", "0");
		end
	end
end