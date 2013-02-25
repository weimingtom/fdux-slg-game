function useskill()
	caster  = ScriptCommonLib.GetTempString("squadid");
	eid = SquadLib.ApplyEffect(caster, "Defence");
	ScriptCommonLib.SetTempInt("castsuccess", 1);
end

function onaffect()
	mid = ScriptCommonLib.GetString("modifierid");
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetTempString("effectid");
	tid = ScriptCommonLib.GetString("triggerid");
	tid1 = ScriptCommonLib.GetString("triggerid1");
	tid2 = ScriptCommonLib.GetString("triggerid2");
	tid3 = ScriptCommonLib.GetString("triggerid3");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	lv = SquadLib.GetEffectLevel(sid, eid);
	ap = SquadLib.GetActionPoint(sid);
	defence = lv + (ap - 2) / 2;
	if defence > 2 + lv then
		defence = 2 + lv;
	end
	mid = SquadLib.ApplyModifier(sid, 0, 0.0, 0.0, defence, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	ScriptCommonLib.SetString("modifierid", mid);
	if tid == "" then
		tid = SquadLib.AddSquadTrigger(sid, "TurnStart", "onturnstart");
		SquadLib.ActiveSquadTrigger(sid, tid);
		ScriptCommonLib.SetString("triggerid", tid);
	end
	if tid1 == "" then
		tid1 = SquadLib.AddSquadTrigger(sid, "OnUnderRangedAttack", "onunderrangedattack");
		SquadLib.ActiveSquadTrigger(sid, tid1);
		ScriptCommonLib.SetString("triggerid1", tid1);
	end
	if tid2 == "" then
		tid2 = SquadLib.AddSquadTrigger(sid, "OnUnderMagicAttack", "onundermagicattack");
		SquadLib.ActiveSquadTrigger(sid, tid2);
		ScriptCommonLib.SetString("triggerid2", tid2);
	end
	if tid3 == "" then
		tid3 = SquadLib.AddSquadTrigger(sid, "OnMeleeAttack", "onmeleeattack");
		SquadLib.ActiveSquadTrigger(sid, tid3);
		ScriptCommonLib.SetString("triggerid3", tid3);
	end
	ScriptCommonLib.SetString("effectid", eid);
	
	SquadLib.ShowValue1(sid, "Skills_DefendEffect", defence, 1.0, 1.0, 1.0);
end

function onremove()
	mid = ScriptCommonLib.GetString("modifierid");
	sid = ScriptCommonLib.GetTempString("squadid");
	tid = ScriptCommonLib.GetString("triggerid");
	tid1 = ScriptCommonLib.GetString("triggerid1");
	tid2 = ScriptCommonLib.GetString("triggerid2");
	tid3 = ScriptCommonLib.GetString("triggerid3");
	if mid ~= "" then
		SquadLib.RemoveModifier(sid, mid);
	end
	if tid ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid);
	end
	if tid1 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid1);
	end
	if tid2 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid2);
	end
	if tid3 ~= "" then
		SquadLib.RemoveSquadTrigger(sid, tid3);
	end
end

function onturnstart()
	sid = ScriptCommonLib.GetTempString("squadid");
	eid = ScriptCommonLib.GetString("effectid");
	SquadLib.RemoveEffect(sid, eid);
end

function onunderrangedattack()
	sid = ScriptCommonLib.GetTempString("squadid");
	tsid = ScriptCommonLib.GetTempString("targetsquadid");
	casterlv = SquadLib.GetSquadLevel(sid);
	targetlv = SquadLib.GetSquadLevel(tsid);
	ep = 25;
	if targetlv > casterlv then
		ep = ep + (targetlv - casterlv) * 3;
	end
	SquadLib.AddExp(sid, ep);	
end

function onundermagicattack()
	sid = ScriptCommonLib.GetTempString("squadid");
	tsid = ScriptCommonLib.GetTempString("targetsquadid");
	casterlv = SquadLib.GetSquadLevel(sid);
	targetlv = SquadLib.GetSquadLevel(tsid);
	ep = 25;
	if targetlv > casterlv then
		ep = ep + (targetlv - casterlv) * 3;
	end
	SquadLib.AddExp(sid, ep);	
end

function onmeleeattack()
	sid = ScriptCommonLib.GetTempString("squadid");
	tsid = ScriptCommonLib.GetTempString("targetsquadid");
	isdefender = ScriptCommonLib.GetTempInt("asdefender");
	if isdefender == 1 then
		casterlv = SquadLib.GetSquadLevel(sid);
		targetlv = SquadLib.GetSquadLevel(tsid);
		ep = 25;
		if targetlv > casterlv then
			ep = ep + (targetlv - casterlv) * 3;
		end
		SquadLib.AddExp(sid, ep);	
	end
end

function validarea()
	ScriptCommonLib.SetTempInt("validarea", 1);
end

function validtarget()
	ScriptCommonLib.SetTempInt("validtarget", 1);
end

function canaffect()
	ScriptCommonLib.SetTempInt("affect", 1);
end