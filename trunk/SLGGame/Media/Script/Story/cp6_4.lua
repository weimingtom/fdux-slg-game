GUI.ButtonLock();
GUI.SetDialogVisible(1);
GUI.ShowImage("fuguan_zi.png",left,300);
GUI.ShowRoleName("法卫队长");
GUI.ShowText("据斥候报告敌方军中有巨剑步兵，这种步兵杀伤力惊人，但防御力较低且阵型加成较低，用远程单位或者法师削弱他们非常有效。",1);
GUI.ClearText();
GUI.ShowText("此战敌方人数占优，请坚守阵地，待法师队突袭扰乱敌军后再发起进攻。",1);
GUI.ClearText();
GUI.ShowText("那么，作战开始！",1);
GUI.ClearText();
GUI.ShowRoleName("");
GUI.ShowImage("",right,300);
GUI.ShowImage("",left,300);
GUI.SetDialogVisible(0);
GUI.StoryOver();