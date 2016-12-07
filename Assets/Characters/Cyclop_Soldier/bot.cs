using System.Collections;
using System.Collections.Generic;
using UnityEngine;


[RequireComponent(typeof(CharacterController))]
public class bot : MonoBehaviour {
    public float MoveSpeed;
    public float RotationSpeed;
    CharacterController cc;
    private CharacterController controller;
    // Use this for initialization
    void Start()
    {
        cc = GetComponent<CharacterController>();

    }

    // Update is called once per frame
    void Update()
    {

        cc.SimpleMove(Physics.gravity);
       



    }
    
}