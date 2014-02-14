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
	--�������ӱ����𴥷���
	trigerid = MapLib.AddMapTrigger("SquadAnnihilated","unitdead");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("unitdeadtriger",trigerid);
	--�����غϽ���������
	trigerid = MapLib.AddMapTrigger("TurnEnd","turnend");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("turnendtriger",trigerid);
	--�����غϿ�ʼ������
	trigerid = MapLib.AddMapTrigger("TurnStart","turnstart");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("turnstarttriger",trigerid);
	--�����������򴥷���
	trigerid = MapLib.AddMapTrigger("GetOutArea","outarea");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("outareatriger",trigerid);
	--�����뿪���򴥷���
	trigerid = MapLib.AddMapTrigger("GetInArea","inarea");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("inareatriger",trigerid);
	
	--����AI����(team,squadid,groupname)
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_3", "DuxRaider");
	BattleLib.AssignAIGroup(2, "Team2Squad_4", "DuxRaider");
	--����AI����(team,missionname,missiontype,missiontargetarea)
	BattleLib.CreateAIMission(2, "DefendCamp", 0, "CampArea");
	--ָ��AI��������(team,groupname,missionname)
	BattleLib.AssignAIMission(2, "DuxRaider", "DefendCamp");
	
	--��������(missionname,missionstate)
	local mainmission = BattleLib.AddPlayerMission("map1mission1",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	local mission1 = BattleLib.AddPlayerMission("map1mission2",0);
	ScriptCommonLib.SetInt("mission1", mission1);
	ScriptCommonLib.SetInt("mission1state", 0);
	
	ScriptCommonLib.SetInt("addedgold", 0);
	ScriptCommonLib.SetInt("battlestory", 0);
	ScriptCommonLib.SetInt("Squad7",0);
end

--���ӱ����𴥷���
function unitdead()
	local squad = ScriptCommonLib.GetTempString("squadid");
	
	if BattleLib.TeamSquadLeft(1) == 0 then
		--ʧ��(storyscript,gold,exp)
		BattleLib.Lost("GameOver.lua","0");
	end
	local faction = SquadLib.GetFaction(squad);
	if faction == 1 then
		BattleLib.AddGold(100);
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 100;
		ScriptCommonLib.SetInt("addedgold", addedgold);
		if BattleLib.TeamSquadLeft(2) == 0 then
			BattleLib.AddGold(2000);
			BattleLib.DumpSquadData();
			addedgold = ScriptCommonLib.GetInt("addedgold");
			addedgold = addedgold + 2000;
			ScriptCommonLib.SetInt("addedgold", addedgold);
			--ʤ��(storyscript,gold,exp)
			BattleLib.Win("cp2.lua", addedgold);
		end
	end
end

function turnstart()
	local turn = ScriptCommonLib.GetTempInt("turn");
	local team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and turn == 1 then
	    BattleLib.Story("cp1_1.lua");
	end
	if team == 1 and turn == 2 then
	    BattleLib.Story("cp1_3.lua");
	end
	if team == 1 and turn == 3 then
	    BattleLib.Story("cp1_4.lua");
	end
end	
		
--�غϽ���������
function turnend()
	local turn = ScriptCommonLib.GetTempInt("turn");
	local team = ScriptCommonLib.GetTempInt("team");
	
	if team == 1 and BattleLib.TeamSquadLeft(2) == 0 then
		BattleLib.DumpSquadData();
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		--ʤ��(storyscript,gold,exp)
		BattleLib.Win("cp2.lua", addedgold);
	end
end

--�뿪���򴥷���
function outarea()
	local squad = ScriptCommonLib.GetTempString("squadid");
	local area = ScriptCommonLib.GetTempString("areaid");
	
	if area == "DeployArea" then
		local faction = SquadLib.GetFaction(squad);
		if faction == 0 then
			local bs = ScriptCommonLib.GetInt("battlestory");
			if bs == 0 then
				--ս������
				BattleLib.Story("cp1_2.lua");
				ScriptCommonLib.SetInt("battlestory", 1);
			end
		end
	elseif area == "BigCamp" then
		ScriptCommonLib.Log("MAPLOG "..squad.." outBigCamp");
	end
end

--�������򴥷���
function inarea()
	local squad = ScriptCommonLib.GetTempString("squadid");
	local area = ScriptCommonLib.GetTempString("areaid");
	
	if area == "BigCamp" then
		ScriptCommonLib.Log("MAPLOG "..squad.." inBigCamp");
		local faction = SquadLib.GetFaction(squad);
		if faction == 0 then
			local mission1state = ScriptCommonLib.GetInt("mission1state");
			if mission1state == 0 then
				local mission1 = ScriptCommonLib.GetInt("mission1");
				--�������(missionindex, missionstate)
				BattleLib.SetPlayerMission(mission1, 1);
				ScriptCommonLib.SetInt("mission1state", 1);
				
				BattleLib.AddGold(1000);
				addedgold = ScriptCommonLib.GetInt("addedgold");
				addedgold = addedgold + 1000;
				ScriptCommonLib.SetInt("addedgold", addedgold);
			end
		end
	end
end