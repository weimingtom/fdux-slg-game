using UnityEngine;
using System.Collections;
using System.Xml;

public class StartGame : MonoBehaviour {
	
	// Use this for initialization
	void Start () {
		
		string data = Resources.Load("level").ToString();
		
		XmlDocument xmlDoc = new XmlDocument();
		xmlDoc.LoadXml(data);
		
		XmlNode contentNode=xmlDoc.SelectSingleNode("Level/LevelContent");
		string content=contentNode.InnerText;
		

		
		for(int i=0;i<25;i++)
		{
			string s=content.Substring(i,1);
			int state=System.Convert.ToInt32(s);
			
			box block = GameObject.Find("block"+i).GetComponent("box") as box;
			block.mInitState=state;
		}
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
