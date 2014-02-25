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
	BattleLib.AssignAIGroup(2, "Team2Squad_0", "Syrin1");
	BattleLib.AssignAIGroup(2, "Team2Squad_1", "Guard");
	BattleLib.AssignAIGroup(2, "Team2Squad_2", "Guard");
	BattleLib.AssignAIGroup(2, "Team2Squad_3", "Syrin1");
	BattleLib.AssignAIGroup(2, "Team2Squad_4", "Guard");
	BattleLib.AssignAIGroup(2, "Team2Squad_5", "Guard");
	BattleLib.AssignAIGroup(2, "Team2Squad_6", "Guard");
	BattleLib.AssignAIGroup(2, "Team2Squad_7", "Guard");
	
	BattleLib.AssignAIGroup(3, "Team3Squad_0", "DarkKnight");
	BattleLib.AssignAIGroup(3, "Team3Squad_1", "DarkKnight");
	BattleLib.AssignAIGroup(3, "Team3Squad_2", "DarkKnight");
	BattleLib.AssignAIGroup(3, "Team3Squad_3", "Syrin");
	
	--����AI����(team,missionname,missiontype,missiontargetarea)
	BattleLib.CreateAIMission(2, "Attack1", 0, "DeployArea");
	BattleLib.CreateAIMission(3, "Attack2", 0, "DeployArea");
	BattleLib.CreateAIMission(2, "Defend1", 0, "TargetArea");
	BattleLib.CreateAIMission(3, "Defend2", 0, "TargetArea");
	BattleLib.CreateAIMission(2, "Attack3", 0, "KeyArea");
	BattleLib.CreateAIMission(3, "Attack4", 0, "KeyArea");	
	--ָ��AI��������(team,groupname,missionname)
	BattleLib.AssignAIMission(2,"Guard", "Attack1");
	BattleLib.AssignAIMission(3,"DarkKnight", "Attack2");
	BattleLib.AssignAIMission(2,"Syrin1", "Defend1");
	BattleLib.AssignAIMission(3,"Syrin", "Defend2");
	
	--��������(missionname,missionstate)
	local mainmission = BattleLib.AddPlayerMission("map19mission1",0);
	ScriptCommonLib.SetInt("mainmission", mainmission);
	local mission1 = BattleLib.AddPlayerMission("map19mission2",0);
	ScriptCommonLib.SetInt("mission1", mission1);
	ScriptCommonLib.SetInt("mission1state", 0);
	ScriptCommonLib.SetInt("addedgold", 0);
end

--���ӱ����𴥷���
function unitdead()
	local squad = ScriptCommonLib.GetTempString("squadid");
	
	if BattleLib.TeamSquadLeft(1) == 0  then
		--ʧ��(storyscript,gold,exp)
		BattleLib.Lost("GameOver.lua", "0");
	end
	local faction = SquadLib.GetFaction(squad);
	if faction == 1 or faction == 2 then
		BattleLib.AddGold(500);
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 500;
		ScriptCommonLib.SetInt("addedgold", addedgold);
		local mission1state = ScriptCommonLib.GetInt("mission1state");
		if squad == "Team3Squad_1" then
			local mission1 = ScriptCommonLib.GetInt("mission1");
			--�������(missionindex, missionstate)
			BattleLib.SetPlayerMission(mission1, 1);
			ScriptCommonLib.SetInt("mission1state", 1);
		end
	end
end

function turnstart()
	local turn = ScriptCommonLib.GetTempInt("turn");
	local team = ScriptCommonLib.GetTempInt("team");
	if team == 1 and turn == 1 then
		MapLib.MoveCameraTo( 10, 9);
	    BattleLib.Story("cp37_1.lua");
	end
	if team == 1 and turn == 2 then
		MapLib.MoveCameraTo( 11, 6);
	    BattleLib.Story("cp37_2.lua");
	end
	if team == 1 and turn == 4 then
		BattleLib.Story("cp37_3.lua");
	end
	if team == 1 and turn == 6 then		
		BattleLib.Story("cp37_5.lua");
		BattleLib.AssignAIMission(2,"Guard", "Attack3");
		BattleLib.AssignAIMission(3,"DarkKnight", "Attack4");
	end

end	
		
--�غϽ���������
function turnend()
	local turn = ScriptCommonLib.GetTempInt("turn");
	local team = ScriptCommonLib.GetTempInt("team");
	if BattleLib.TeamSquadLeft(2) == 0 then
		BattleLib.AddGold(9000);
		BattleLib.DumpSquadData();
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 9000;
		local mission1state = ScriptCommonLib.GetInt("mission1state");
		if mission1state == 1 then
			BattleLib.AddGold(4800);
			addedgold = addedgold + 4800;
		end
		ScriptCommonLib.SetInt("addedgold", addedgold);
		--ʤ��(storyscript,gold,exp)
		BattleLib.Win("cp38.lua",  addedgold);
	end
end

--�뿪���򴥷���
function outarea()
	local squad = ScriptCommonLib.GetTempString("squadid");
	local area = ScriptCommonLib.GetTempString("areaid");
end

--�������򴥷���
function inarea()
	local squad = ScriptCommonLib.GetTempString("squadid");
	local area = ScriptCommonLib.GetTempString("areaid");
	local faction = SquadLib.GetFaction(squad);
	
	if faction == 0 and area == "TargetArea" then
		BattleLib.AddGold(9000);
		BattleLib.DumpSquadData();
		local addedgold = ScriptCommonLib.GetInt("addedgold");
		addedgold = addedgold + 9000;
		local mission1state = ScriptCommonLib.GetInt("mission1state");
		if mission1state == 1 then
			BattleLib.AddGold(4800);
			addedgold = addedgold + 4800;
		end
		ScriptCommonLib.SetInt("addedgold", addedgold);
		--ʤ��(storyscript,gold,exp)
		BattleLib.Win("cp38.lua",  addedgold);
	end
end