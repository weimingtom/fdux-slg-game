function initmap()
	local trigerid = MapLib.AddMapTrigger("FinishDeploy","finishdeploy");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("finishdeploytriger",trigerid);
	
	ScriptCommonLib.PlayMusic("battle1.ogg");
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
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "Winfred");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "Winfred");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "Winfred");
	BattleLib.AssignAIGroup(2, "Team2Squad_3", "Winfred");
	BattleLib.AssignAIGroup(2, "Team2Squad_4", "Winfred");
	BattleLib.AssignAIGroup(2, "Team2Squad_5", "Winfred");

	BattleLib.AssignAIGroup(3, "Team3Squad_0", "Guard");
	BattleLib.AssignAIGroup(3, "Team3Squad_1", "Guard");
	BattleLib.AssignAIGroup(3, "Team3Squad_2", "Guard");
	BattleLib.AssignAIGroup(3, "Team3Squad_3", "Guard");
	BattleLib.AssignAIGroup(3, "Team3Squad_4", "Guard");
	
	--创建AI任务(team,missionname,missiontype,missiontargetarea)
	BattleLib.CreateAIMission(2, "Attack1", 0, "TargetArea");
	BattleLib.CreateAIMission(3, "Attack2", 0, "TargetArea");
	--指派AI分组任务(team,groupname,missionname)
	BattleLib.AssignAIMission(2,"Winfred", "Attack1");
	BattleLib.AssignAIMission(3,"Guard", "Attack2");
		
	--创建任务(missionname,missionstate)
	local mainmission = BattleLib.AddPlayerMission("map16mission1",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	local mission1 = BattleLib.AddPlayerMission("map16mission2",0);
	ScriptCommonLib.SetInt("mission1", mission1);
	ScriptCommonLib.SetInt("mission1state", 1);
	ScriptCommonLib.SetInt("addedgold", 0);
end

--部队被歼灭触发器
function unitdead()
	local squad = ScriptCommonLib.GetTempString("squadid");
	
	if BattleLib.TeamSquadLeft(1) == 0  then
		--失败(storyscript,gold,exp)
		BattleLib.Lost("GameOver.lua", "0");
	end
	local faction = SquadLib.GetFaction(squad);
	if faction == 1 or faction == 0 then
		BattleLib.AddGold(300);
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 300;
		ScriptCommonLib.SetInt("addedgold", addedgold);
		if BattleLib.TeamSquadLeft(2) == 0 and BattleLib.TeamSquadLeft(3) == 0 then
			BattleLib.AddGold(6800);
			BattleLib.DumpSquadData();
			addedgold = ScriptCommonLib.GetInt("addedgold");
			addedgold = addedgold + 6800;
			local mission1state = ScriptCommonLib.GetInt("mission1state");
			if mission1state == 1 then
				BattleLib.AddGold(3500);
				addedgold = addedgold + 3500;
			end
			ScriptCommonLib.SetInt("addedgold", addedgold);
		--胜利(storyscript,gold,exp)
			BattleLib.Win("cp33.lua", addedgold);
		end
	end
	if faction == 0 then
		local mission1state = ScriptCommonLib.GetInt("mission1state");
		if mission1state == 1 then
			local mission1 = ScriptCommonLib.GetInt("mission1");
			--完成任务(missionindex, missionstate)
			BattleLib.SetPlayerMission(mission1, 2);
			ScriptCommonLib.SetInt("mission1state", 0);
		end
	end
end

function turnstart()
	local turn = ScriptCommonLib.GetTempInt("turn");
	local team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and turn == 1 then
	    BattleLib.Story("cp32_1.lua");
	end
	if team == 1 and turn == 3 then
		MapLib.MoveCameraTo( 18, 2);
		AVGLib.SetCanSupply("WingsHeavyInf",1);
		AVGLib.SetCanSupply("WingsCrossBow",1);
		AVGLib.SetCanSupply("Azaria",1);
		AVGLib.SetCanSupply("Caster",1);
		AVGLib.SetCanSupply("Olivia",1);
		AVGLib.SetCanSupply("Cheetah",1);
		AVGLib.SetCanSupply("WingsLightCavalry",1);
		BattleLib.AddStorySquad ("WingsHeavyInf", "WingsHeavyInf", 18, 3, 1);
		BattleLib.AddStorySquad ("WingsCrossBow", "WingsCrossBow", 19, 1, 1);
		BattleLib.AddStorySquad ("Azaria", "Azaria", 19, 2, 1);
		BattleLib.AddStorySquad ("Caster", "Caster", 17, 2, 1);
		BattleLib.AddStorySquad ("Olivia", "Olivia", 19, 3, 1);
		BattleLib.AddStorySquad ("Cheetah", "Cheetah", 18, 2, 1);
		BattleLib.AddStorySquad ("WingsLightCavalry", "WingsLightCavalry", 17, 1, 1);
		BattleLib.Story("cp32_2.lua");
	end
end	
		
--回合结束触发器
function turnend()
	local turn = ScriptCommonLib.GetTempInt("turn");
	local team = ScriptCommonLib.GetTempInt("team");
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