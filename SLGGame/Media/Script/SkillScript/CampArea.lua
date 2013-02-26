function onmap()
	x = ScriptCommonLib.GetTempInt("x");
	y = ScriptCommonLib.GetTempInt("y");
	areaid = MapLib.AddMapArea(x, y);
	ScriptCommonLib.SetString("areaid",areaid);
	
	trigerid = MapLib.AddMapTrigger("GetOutArea","outarea");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("outareatriger",trigerid);
	
	trigerid = MapLib.AddMapTrigger("GetInArea","inarea");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("inareatriger",trigerid);
end

function inarea()
	squad = ScriptCommonLib.GetTempString("squadid");
	area = ScriptCommonLib.GetTempString("areaid");
	areaid = ScriptCommonLib.GetString("areaid");
	if area == areaid then
		SquadLib.ApplyEffect(squad, "Camp");
	end
end

function outarea()
	squad = ScriptCommonLib.GetTempString("squadid");
	area = ScriptCommonLib.GetTempString("areaid");
	areaid = ScriptCommonLib.GetString("areaid");
	if area == areaid then
		elv, eid = SquadLib.GetEffectLevelByName(squad, "Camp");
		SquadLib.RemoveEffect(squad, eid);
	end
end