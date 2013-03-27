using UnityEngine;
using System.Collections;

public class box : MonoBehaviour {
	
	tk2dAnimatedSprite animSprite;
	
	// Use this for initialization
	void Start () {
		animSprite = GetComponent<tk2dAnimatedSprite>();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
    void OnMouseDown() {
       animSprite.Play("demo_loop");
    }
}
