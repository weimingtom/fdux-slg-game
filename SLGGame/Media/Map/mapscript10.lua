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
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "Noth");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "Noth");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "Noth");
	BattleLib.AssignAIGroup(2, "Team2Squad_3", "Noth");
	BattleLib.AssignAIGroup(2, "Team2Squad_4", "Noth");
	BattleLib.AssignAIGroup(2, "Team2Squad_5", "Noth");
	BattleLib.AssignAIGroup(2, "Team2Squad_6", "Noth");
	BattleLib.AssignAIGroup(2, "Team2Squad_7", "Noth");
	BattleLib.AssignAIGroup(2, "Team2Squad_8", "Noth");
	BattleLib.AssignAIGroup(2, "Team2Squad_9", "Noth");
	BattleLib.AssignAIGroup(2, "Team2Squad_10", "Noth");
	
	BattleLib.AssignAIGroup(3, "Team3Squad_0", "Winfred");
	BattleLib.AssignAIGroup(3, "Team3Squad_1", "Winfred");
	BattleLib.AssignAIGroup(3, "Team3Squad_2", "Winfred");
	BattleLib.AssignAIGroup(3, "Team3Squad_3", "Winfred");
	BattleLib.AssignAIGroup(3, "Team3Squad_4", "Winfred");
	BattleLib.AssignAIGroup(3, "Team3Squad_5", "Winfred");
	BattleLib.AssignAIGroup(3, "Team3Squad_6", "Winfred");
	BattleLib.AssignAIGroup(3, "Team3Squad_7", "Winfred");

	
	--创建AI任务(team,missionname,missiontype,missiontargetarea)
	BattleLib.CreateAIMission(2, "Attack", 0, "KeyArea");
	BattleLib.CreateAIMission(3, "Defend", 0, "KeyArea");
	--指派AI分组任务(team,groupname,missionname)
	BattleLib.AssignAIMission(2,"Noth", "Attack");
	BattleLib.AssignAIMission(3,"Winfred", "Defend");
	
	--创建任务(missionname,missionstate)
	local mainmission = BattleLib.AddPlayerMission("map10mission1",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	local mission1 = BattleLib.AddPlayerMission("map10mission2",0);
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
		BattleLib.AddGold(150);
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 150;
		ScriptCommonLib.SetInt("addedgold", addedgold);
		if BattleLib.TeamSquadLeft(2) == 0  then
			BattleLib.AddGold(3300);
			BattleLib.DumpSquadData();
			addedgold = ScriptCommonLib.GetInt("addedgold");
			addedgold = addedgold + 3300;
			local mission1state = ScriptCommonLib.GetInt("mission1state");
			if mission1state == 1 then
				BattleLib.AddGold(1900);
				addedgold = addedgold + 1900;
			end
			ScriptCommonLib.SetInt("addedgold", addedgold);
			--胜利(storyscript,gold,exp)
			BattleLib.Win("cp22.lua", addedgold);
		end
	end
	if BattleLib.TeamSquadLeft(3) == 0 then
		BattleLib.Story("cp21_6.lua");
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
		MapLib.MoveCameraTo( 7, 18);
	    BattleLib.Story("cp21_5.lua");
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