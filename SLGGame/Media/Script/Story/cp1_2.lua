GUI.ButtonLock();
GUI.SetDialogVisible(1);
GUI.ShowImage("zhiyin2.png",4,1000);
GUI.ShowImage("qitaw_zc.png",left,300);
GUI.ShowRoleName("齐塔");
GUI.ShowText("敌人在树林之中隐蔽着一些部队，在行军时发现它们将使我军行军停止以等待新的指令。",1);
GUI.ClearText();
GUI.ShowText("部队受到回合开始时未被发现的敌军攻击会受到突袭。为了避免遭到突袭打击，请先使用侦察值更高的轻装步兵前往探查。",1);
GUI.ClearText();
GUI.ShowText("当然我军也可以利用突袭效果对敌军低侦察值单位进行突袭打击。",1);
GUI.ClearText();
GUI.ShowRoleName("");
GUI.ShowImage("",right,300);
GUI.ShowImage("",left,300);
GUI.ShowImage("",4,1000);
GUI.SetDialogVisible(0);
GUI.StoryOver();