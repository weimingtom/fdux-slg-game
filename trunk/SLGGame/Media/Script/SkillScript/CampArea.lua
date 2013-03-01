function onmap()
	local x = ScriptCommonLib.GetTempInt("x");
	local y = ScriptCommonLib.GetTempInt("y");
	local areaid = MapLib.AddMapArea(x, y);
	ScriptCommonLib.SetString("areaid",areaid);
	
	local trigerid = MapLib.AddMapTrigger("GetOutArea","outarea");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("outareatriger",trigerid);
	
	trigerid = MapLib.AddMapTrigger("GetInArea","inarea");
	MapLib.ActiveMapTrigger(trigerid);
	ScriptCommonLib.SetString("inareatriger",trigerid);
end

function inarea()
	local squad = ScriptCommonLib.GetTempString("squadid");
	local area = ScriptCommonLib.GetTempString("areaid");
	local areaid = ScriptCommonLib.GetString("areaid");
	if area == areaid then
		SquadLib.ApplyEffect(squad, "Camp");
	end
end

function outarea()
	local squad = ScriptCommonLib.GetTempString("squadid");
	local area = ScriptCommonLib.GetTempString("areaid");
	local areaid = ScriptCommonLib.GetString("areaid");
	if area == areaid then
		local elv, eid = SquadLib.GetEffectLevelByName(squad, "Camp");
		SquadLib.RemoveEffect(squad, eid);
	end
end