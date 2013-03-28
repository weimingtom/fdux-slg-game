using UnityEngine;
using System.Collections;

public class box : MonoBehaviour {
	
	tk2dAnimatedSprite animSprite;
	
	public int mInitState;
	
	// Use this for initialization
	void Start () {
		animSprite = GetComponent<tk2dAnimatedSprite>();
		setState(mInitState);
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	public void setState(int state)
	{
		animSprite.SetFrame(state);
	}
	
    void OnMouseDown() {
       animSprite.Play("demo_loop");
    }
}
