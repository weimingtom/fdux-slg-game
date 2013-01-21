function useskill()
	sid = ScriptCommonLib.GetTempString("squadid");
	tgtx = ScriptCommonLib.GetTempInt("targetx");
	tgty = ScriptCommonLib.GetTempInt("targety");
	sf = SquadLib.GetFaction(sid);
	for x = tgtx - 1, tgtx + 1, 1 do
		for y = tgty - 1, tgty + 1, 1 do
			tgtsid = BattleLib.GetSquadAt(x, y, 1, sf);
			if tgtsid ~= "" then 
				tgtf = SquadLib.GetFaction(sid);
				if sf == tgtf then
					SquadLib.ApplyEffect(tgtsid, "Inspired");
				end
			end
		end
	end
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
	pid = ScriptCommonLib.GetString("particleid");
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
	if pid == "" then
		pid = SquadLib.AddParticle(sid, "mp_spell_effect_06", 3);
	end
	ScriptCommonLib.SetString("particleid", pid);
	ScriptCommonLib.SetInt("turn", 0);
end

function onremove()
	sid = ScriptCommonLib.GetTempString("squadid");
	mid = ScriptCommonLib.GetString("modifierid");
	tid = ScriptCommonLib.GetString("triggerid");
	pid = ScriptCommonLib.GetString("particleid");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
	if pid ~= "" then
		SquadLib.DelParticle(sid, pid);
	end
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