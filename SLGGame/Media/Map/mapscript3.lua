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
	BattleLib.CreateAIMission(2, "AttackCamp", 0, "AttackArea");
	BattleLib.CreateAIMission(2, "Run", 2, "Run");
	--指派AI分组任务(team,groupname,missionname)
	BattleLib.AssignAIMission(2, "Ulva", "AttackCamp");
	BattleLib.AssignAIMission(2, "Pirate", "AttackCamp");
	
	--创建任务(missionname,missionstate)
	local mainmission = BattleLib.AddPlayerMission("map3mission1",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	local mission1 = BattleLib.AddPlayerMission("map3mission2",0);
	ScriptCommonLib.SetInt("mission1", mission1);
	ScriptCommonLib.SetInt("mission1state", 0);
	
	ScriptCommonLib.SetInt("addedgold", 0);
	ScriptCommonLib.SetInt("battlestory", 0);
end

--部队被歼灭触发器
function unitdead()
	local squad = ScriptCommonLib.GetTempString("squadid");
	
	if BattleLib.TeamSquadLeft(1) == 0 then
		--失败(storyscript,gold,exp)
		BattleLib.Lost("GameOver.lua", "0");
	end
	local faction = SquadLib.GetFaction(squad);
	if faction == 1 then
		BattleLib.AddGold(120);
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 120;
		ScriptCommonLib.SetInt("addedgold", addedgold);
		if  BattleLib.TeamSquadLeft(2) == 0 then
			BattleLib.AddGold(2000);
			BattleLib.DumpSquadData();
			addedgold = ScriptCommonLib.GetInt("addedgold");
			addedgold = addedgold + 2000;
			local mission1state = ScriptCommonLib.GetInt("mission1state");
			if mission1state <= 3 then
				BattleLib.AddGold(1000);
				addedgold = addedgold + 1000;
			end
			ScriptCommonLib.SetInt("addedgold", addedgold);
			--胜利(storyscript,gold,exp)
			BattleLib.Win("cp7.lua", addedgold);
		end
	end
end

function turnstart()
	local turn = ScriptCommonLib.GetTempInt("turn");
	local team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and turn == 1 then
		BattleLib.Story("cp6_4.lua");
	end
	if team == 1 and turn == 3 then
	    MapLib.MoveCameraTo( 17, 17);
		BattleLib.AddStorySquad("Fay", "Fay", 17, 17, 0);
		BattleLib.Story("cp6_1.lua");
	end
	if team == 1 and turn == 4 then
		if BattleLib.AddStorySquad("Elementalist", "Elementalist", 10, 12, 0) == 0 then
            BattleLib.AddStorySquad("Elementalist", "Elementalist", 9, 11, 0)
            MapLib.MoveCameraTo( 9, 11);
        else
            MapLib.MoveCameraTo( 10, 12);
        end
	    BattleLib.Story("cp6_2.lua");
		BattleLib.AssignAIMission(2, "Pirate", "Run");
	end
end	
		
--回合结束触发器
function turnend()
	local turn = ScriptCommonLib.GetTempInt("turn");
	local team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and BattleLib.TeamSquadLeft(2) == 0 then
		BattleLib.AddGold(2000);
		BattleLib.DumpSquadData();
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 2000;
		local mission1state = ScriptCommonLib.GetInt("mission1state");
		if mission1state <= 3 then
			BattleLib.AddGold(1000);
			addedgold = addedgold + 1000;
		end
		ScriptCommonLib.SetInt("addedgold", addedgold);
		--胜利(storyscript,gold,exp)
		BattleLib.Win("cp7.lua", addedgold);
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
	
	if area == "Run" then
		local faction = SquadLib.GetFaction(squad);
		if faction == 1 then
			local mission1state = ScriptCommonLib.GetInt("mission1state");
		    mission1state = mission1state + 1;
			ScriptCommonLib.SetInt("mission1state", mission1state);
			BattleLib.RemoveBattleSquad(squad);
            if BattleLib.TeamSquadLeft(2) ~= 0 then
                BattleLib.Story("cp6_3.lua");
            end
			if mission1state > 3 then
				local mission1 = ScriptCommonLib.GetInt("mission1");
				--任务成功(missionindex, missionstate)
				BattleLib.SetPlayerMission(mission1, 2);
			end
		end
	end
end