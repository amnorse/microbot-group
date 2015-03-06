//============================================================================
// Name        : Microbot_c++.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "kinematics.h"
#include <iostream>

int main()
{
  using namespace std;

	Microbot robot;				// Local var24iable of the microbot class
    Registerspace delta;		// Local variable for input of motor steps
    int spe=240;				// Motor speed; should not be higher than 240


//this is an edit



    int input;
    int steps;

// Set Motor Speed

do{
    cout << "Please select motor speed (0-240)"<< endl;
   cout<< "input: ";
    cin >> spe; }
while (spe>240);


// Joint and step loop begins

    do
    {
        delta.r[7]=0;				// Zero Steps for each joint
	      delta.r[6]=0;
	      delta.r[5]=0;
	      delta.r[4]=0;
        delta.r[3]=0;
	      delta.r[2]=0;
        delta.r[1]=0;


// Joint selection loop

    do
    {
        cout << "Please select which joint to move or type 0 to exit: " << endl;
        cout << "Joint: 1 " << endl; // Base Negative CW
        cout << "Joint: 2 " << endl; // First Linkage  Negative up
        cout << "Joint: 3 " << endl; // Second Linkage Negative up
        cout << "Joint: 4 " << endl; // Right Gear CW
        cout << "Joint: 5 " << endl; // Left Gear CW
        cout << "Joint: 6 " << endl; // Gripper Negative Close
        cout << "Exit: 0" << endl;
        cout << endl;
        cout << "Input: ";
        cin >> input;
        cout << endl;

    } while (input != 1 && input != 2 &&
            input != 3 && input != 4 && input != 5 && input != 6 && input!=0);

// Verify that an acceptable number was chosen

     if((input==1)||(input==2)||(input==3)||(input==4)||(input==5)||(input==6)){

// Select number of steps

        cout << "Please select the number of steps to move joint " << input << ", or type                 0 to exit.";
        cout << endl;
        cout << "Input: ";
        cin >> steps;
        cout << endl;

// Move joint

        if(steps!=0){
        cout << "moving joint " << input << ", " << steps << " steps";
        delta.r[input]=steps;				// Assign number of steps to joint


        robot.SendStep(spe, delta);	// Send instruction to the microbot

        }

        cout << endl;
        }
        cout << endl;
        cout << endl;

// Return to beginning of control loop provided user has not chosen to exit by typing 0

    } while ((input!=0)&&(steps!=0));

    return 0;

}
