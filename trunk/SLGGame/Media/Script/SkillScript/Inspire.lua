function useskill()
	sid = ScriptCommonLib.GetTempString("squadid");
	ep = 0;
	tgtx = ScriptCommonLib.GetTempInt("targetx");
	tgty = ScriptCommonLib.GetTempInt("targety");
	sf = SquadLib.GetFaction(sid);
	croodlist = {
		{tgtx, tgty},
		{tgtx - 1, tgty},
		{tgtx, tgty - 1},
		{tgtx + 1, tgty},
		{tgtx, tgty + 1},
	};
	for i = 1, 5 do
		tgtsid = BattleLib.GetSquadAt(croodlist[i][1], croodlist[i][2], 1, sf);
		if tgtsid ~= "" then
			tgtf = SquadLib.GetFaction(tgtsid);
			if tgtf == sf then
				SquadLib.ApplyEffect(tgtsid, "Inspired");
				ep = ep + 20;
			end
		end
	end	
	SquadLib.AddExp(caster, ep);
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validaffectarea()
	ScriptCommonLib.SetTempInt("validaffectarea", 1);
end

function onaffect()
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetTempString("effectid");
	mid = ScriptCommonLib.GetString("modifierid");
	tid = ScriptCommonLib.GetString("triggerid");
	--pid = ScriptCommonLib.GetString("particleid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	lv = SquadLib.GetEffectLevel(sid, eid);
	mid = SquadLib.ApplyModifier(sid, 1, lv, lv, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnStart", "onturnstart");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	ScriptCommonLib.SetString("effectid", eid);
	--if pid == "" then
	--	pid = SquadLib.AddParticle(sid, "mp_spell_effect_06", 3);
	--end
	--ScriptCommonLib.SetString("particleid", pid);
	
	SquadLib.ShowValue1(sid, "Skills_Inspire", lv, 1.0, 1.0, 1.0);
	
	ScriptCommonLib.SetInt("turn", 0);
end

function onremove()
	sid = ScriptCommonLib.GetTempString("squadid");
	mid = ScriptCommonLib.GetString("modifierid");
	tid = ScriptCommonLib.GetString("triggerid");
	--pid = ScriptCommonLib.GetString("particleid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
	--if pid ~= "" then
	--	SquadLib.DelParticle(sid, pid);
	--end
end

function onturnstart()
	sid = ScriptCommonLib.GetTempString("squadid");
	turn = ScriptCommonLib.GetInt("turn");
	if turn == 2 then
		eid = ScriptCommonLib.GetString("effectid");
		SquadLib.RemoveEffect(sid, eid);
	else
		ScriptCommonLib.SetInt("turn", turn + 1);
	end
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end