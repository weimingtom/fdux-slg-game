function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	ap = SquadLib.GetActionPoint(caster);
	maxnum = SquadLib.GetUnitMaxNum(caster);
	num = SquadLib.GetUnitNum(caster);
	num = num + ap;
	if num > maxnum then
		num = maxnum;
	end
	SquadLib.SetUnitNum(caster, num);
	ep = 10 * num;
	SquadLib.AddExp(caster, ep);	
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	ScriptCommonLib.SetTempInt("validtarget", 1);
end