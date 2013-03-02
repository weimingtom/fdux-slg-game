function initmap()
	local trigerid = MapLib.AddMapTrigger("FinishDeploy","finishdeploy");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("finishdeploytriger",trigerid);
	
	ScriptCommonLib.PlayMusic("battle2.ogg");
	MapLib.SetCamera(0,4);
end

function finishdeploy()
	local trigerid = ScriptCommonLib.GetString("finishdeploytriger");
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
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_3", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_4", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_5", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_6", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_7", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_8", "Ulva");
	
	BattleLib.AssignAIGroup(3, "Team3Squad_0", "Kareena");
	BattleLib.AssignAIGroup(3, "Team3Squad_1", "Kareena");
	BattleLib.AssignAIGroup(3, "Team3Squad_2", "Kareena");
	
	--创建AI任务(team,missionname,missiontype,missiontargetarea)
	BattleLib.CreateAIMission(2, "Attack", 0, "DeployArea");
	BattleLib.CreateAIMission(3, "Defend", 0, "KeyArea");
	--指派AI分组任务(team,groupname,missionname)
	BattleLib.AssignAIMission(2,"Ulva", "Attack");
	BattleLib.AssignAIMission(3,"Kareena", "Defend");
	
	--创建任务(missionname,missionstate)
	local mainmission = BattleLib.AddPlayerMission("map8mission1",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	local mission1 = BattleLib.AddPlayerMission("map8mission2",0);
	local mission2 = BattleLib.AddPlayerMission("map8mission3",0);
	ScriptCommonLib.SetInt("mission1", mission1);
	ScriptCommonLib.SetInt("mission2", mission2);
	ScriptCommonLib.SetInt("mission1state", 1);
	ScriptCommonLib.SetInt("mission2state", 1);
	ScriptCommonLib.SetInt("addedgold", 0);
end

--部队被歼灭触发器
function unitdead()
	local squad = ScriptCommonLib.GetTempString("squadid");
	
	if BattleLib.TeamSquadLeft(1) == 0 then
		--失败(storyscript,gold,exp)
		BattleLib.Lost("GameOver.lua", "0"); 
	end
	
	if squad == "Kareena" then
		--失败(storyscript,gold,exp)
       	local mission2 = ScriptCommonLib.GetInt("mission2");
		BattleLib.SetPlayerMission(mission2, 2);
	    ScriptCommonLib.SetInt("mission2state", 0);
	end
	
	local faction = SquadLib.GetFaction(squad);
	if faction == 1 then
		BattleLib.AddGold(130);
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 130;
		ScriptCommonLib.SetInt("addedgold", addedgold);
		if BattleLib.TeamSquadLeft(2) == 0  then
			BattleLib.AddGold(2700);
			BattleLib.DumpSquadData();
			addedgold = ScriptCommonLib.GetInt("addedgold");
			addedgold = addedgold + 2700;
			local mission1state = ScriptCommonLib.GetInt("mission1state");
			local mission2state = ScriptCommonLib.GetInt("mission2state");
			if mission1state == 1 then
				BattleLib.AddGold(1650);
				addedgold = addedgold + 1650;
			end
			if mission2state == 1 then
				BattleLib.AddGold(1300);
				addedgold = addedgold + 1300;
			end
			ScriptCommonLib.SetInt("addedgold", addedgold);
			--胜利(storyscript,gold,exp)
			BattleLib.Win("cp17.lua", addedgold);
		end
	end
end

function turnstart()
	local turn = ScriptCommonLib.GetTempInt("turn");
	local team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and turn == 1 then
	    BattleLib.Story("cp16_1.lua");
	end
	
	if team == 1 and turn == 4 then
		MapLib.MoveCameraTo( 12, 14);
		AVGLib.SetCanSupply("GuardHeavySpear",1);
		AVGLib.SetCanSupply("GuardLightBow",1);
		AVGLib.SetCanSupply("GuardLightSword",1);
		AVGLib.SetCanSupply("Fay",1);
		AVGLib.SetCanSupply("Elementalist",1);
		BattleLib.AddStorySquad ("Fay", "Fay", 12, 14, 1);
		BattleLib.AddStorySquad ("GuardHeavySpear", "GuardHeavySpear", 13, 15, 1);
		BattleLib.AddStorySquad ("GuardLightBow", "GuardLightBow", 13, 14, 1);
		BattleLib.AddStorySquad ("GuardLightSword", "GuardLightSword", 12, 15, 1);
		BattleLib.AddStorySquad ("Elementalist", "Elementalist", 14, 15, 1);
		BattleLib.Story("cp16_5.lua");
	end
end	
		
--回合结束触发器
function turnend()
	local turn = ScriptCommonLib.GetTempInt("turn");
	local team = ScriptCommonLib.GetTempInt("team");
	
	if team == 1 and turn >= 10 then
		local mission1 = ScriptCommonLib.GetInt("mission1");
		--完成任务(missionindex, missionstate)
		BattleLib.SetPlayerMission(mission1, 2);
		ScriptCommonLib.SetInt("mission1state", 0);
	end
	
	if team == 2 and turn>=10 then
		BattleLib.Story("cp16_6.lua");
		BattleLib.AddGold(2700);
		BattleLib.DumpSquadData();
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 2700;
		local mission2state = ScriptCommonLib.GetInt("mission2state");
		if mission2state == 1 then
				BattleLib.AddGold(1300);
				addedgold = addedgold + 1300;
		end
		--胜利(storyscript,gold,exp)
		ScriptCommonLib.SetInt("addedgold", addedgold);	
		BattleLib.Win("cp17.lua", addedgold);
	end
end

--离开区域触发器
function outarea()
	local squad = ScriptCommonLib.GetTempString("squadid");
	local area = ScriptCommonLib.GetTempString("areaid");
end

--进入区域触发器
function inarea()
	local squad = ScriptCommonLib.GetTempString("squadid");
	local area = ScriptCommonLib.GetTempString("areaid");
end