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
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_3", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_4", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_5", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_6", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_7", "Ulva");
	BattleLib.AssignAIGroup(2, "Team2Squad_8", "Ulva");
	--创建AI任务(team,missionname,missiontype,missiontargetarea)
	BattleLib.CreateAIMission(2, "Attack", 0, "DeployArea");
	BattleLib.CreateAIMission(3, "AttackUlva", 0, "DeployArea");
	--指派AI分组任务(team,groupname,missionname)
	BattleLib.AssignAIMission(2, "Ulva", "Attack");
	BattleLib.AssignAIMission(3, "Winfred", "AttackUlva");
	
	--创建任务(missionname,missionstate)
	local mainmission = BattleLib.AddPlayerMission("map6mission1",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	local mission1 = BattleLib.AddPlayerMission("map6mission2",0);
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
	if faction == 1 then
		BattleLib.AddGold(130);
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 130;
		ScriptCommonLib.SetInt("addedgold", addedgold);
		if BattleLib.TeamSquadLeft(2) == 0 then
			BattleLib.AddGold(2200);
			BattleLib.DumpSquadData();
			addedgold = ScriptCommonLib.GetInt("addedgold");
			addedgold = addedgold + 2200;
			local mission1state = ScriptCommonLib.GetInt("mission1state");
			if mission1state == 1 then
				BattleLib.AddGold(1350);
				addedgold = addedgold + 1350;
			end
			ScriptCommonLib.SetInt("addedgold", addedgold);
			--胜利(storyscript,gold,exp)
			BattleLib.Win("cp13.lua", addedgold);
		end
	end
	if squad == "Elementalist" then
	    local mission1 = ScriptCommonLib.GetInt("mission1");
		--完成任务(missionindex, missionstate)
		BattleLib.SetPlayerMission(mission1, 2);
		ScriptCommonLib.SetInt("mission1state", 0);
	end
end

function turnstart()
	local turn = ScriptCommonLib.GetTempInt("turn");
	local team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and turn == 1 then
	    BattleLib.Story("cp12_1.lua");
	end
	if team == 1 and turn == 2 then
		MapLib.MoveCameraTo( 17, 18);
		AVGLib.SetCanSupply("Fay",1);
		AVGLib.SetCanSupply("GuardHeavySpear",1);
		BattleLib.AddStorySquad ("Fay", "Fay", 17, 18, 1);
		BattleLib.AddStorySquad ("GuardHeavySpear", "GuardHeavySpear", 16, 18, 1);
		BattleLib.Story("cp12_2.lua");
	end
	if team == 1 and turn == 3 then
		MapLib.MoveCameraTo( 8, 11);
		BattleLib.AddBattleSquad("James", "Team3Squad_0", 8, 11, 3, 50);
		BattleLib.AddBattleSquad("WinfredHeavyHalberd", "Team3Squad_1", 6, 16, 3, 50);
		BattleLib.AddBattleSquad("WinfredHeavyHalberd", "Team3Squad_2", 8, 10, 3, 50);
		BattleLib.AddBattleSquad("WinfredLightHalberd", "Team3Squad_3", 6, 17, 3, 50);
		BattleLib.AddBattleSquad("WinfredLightHalberd", "Team3Squad_4", 5, 17, 3, 50);
		BattleLib.AddBattleSquad("WinfredLightBow", "Team3Squad_5", 5, 16, 3, 50);
		BattleLib.AddBattleSquad("WinfredLightBow", "Team3Squad_6", 7, 11, 3, 50);
		BattleLib.AddBattleSquad("WinfredLightBow", "Team3Squad_7", 7, 10, 3, 50);
		BattleLib.Story("cp12_5.lua");
			
		BattleLib.AssignAIGroup(3, "Team3Squad_0", "Winfred");
		BattleLib.AssignAIGroup(3, "Team3Squad_1", "Winfred");
		BattleLib.AssignAIGroup(3, "Team3Squad_2", "Winfred");
		BattleLib.AssignAIGroup(3, "Team3Squad_3", "Winfred");
		BattleLib.AssignAIGroup(3, "Team3Squad_4", "Winfred");
		BattleLib.AssignAIGroup(3, "Team3Squad_5", "Winfred");
		BattleLib.AssignAIGroup(3, "Team3Squad_6", "Winfred");
		BattleLib.AssignAIGroup(3, "Team3Squad_7", "Winfred");
	end
end	
		
--回合结束触发器
function turnend()
	local turn = ScriptCommonLib.GetTempInt("turn");
	local team = ScriptCommonLib.GetTempInt("team");
	
	if team == 1 and BattleLib.TeamSquadLeft(2) == 0 then
		BattleLib.DumpSquadData();
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		--胜利(storyscript,gold,exp)
		BattleLib.Win("cp13.lua", addedgold);
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