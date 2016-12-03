using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cube : MonoBehaviour {
    public float moveSpeed;
	// Use this for initialization
	void Start () {
        moveSpeed = 10f;
	}
	
	// Update is called once per frame
	void Update () {
        print(Input.GetAxis("Horizontal"));
        transform.Translate(Input.GetAxis("Horizontal") * Time.deltaTime, 0f,Input.GetAxis("Vertical")*Time.deltaTime);
    }
}
