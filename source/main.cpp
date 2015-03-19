//============================================================================
// Name        : Microbot_c++.cpp
// Author      : Andrew Norster, Michael Moon, Luke Bennett, Nathan Thurlow
// Version     :
// Copyright   : 
// Description : robotic control in progress
//============================================================================
#include "kinematics.h"
#include <iostream>
#define INT_MAX 100


// Requests user input for setting up robot motor speeds //
int set_speed()
{
    using namespace std;
    int spd;
    cout << endl << "Please select motor speed (0-240)"<< endl;
    cout << "input: ";

    while (!(cin >> spd) || spd < 1 || spd > 240)
    {
        cout << "Bad input - try again: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return spd;
}

// set joint values through the console //
Registerspace manual_set_joints(Registerspace d)
{
    d.r[7]=0;				// Zero Steps for each joint
    d.r[6]=0;
    d.r[5]=0;
    d.r[4]=0;
    d.r[3]=0;
    d.r[2]=0;
    d.r[1]=0;
    using namespace std;
    int joint_in;
    int value_in;

    do
    {
        cout << endl << "Please select which joint (1-6) to move. Type 0 to execute: " << endl;
        cout << "Input: ";
            while (!(cin >> joint_in) || joint_in < 0 || joint_in > 6)                  //WARN: just hitting enter is bad
            {
                cout << "Bad input - try again: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }

        if(joint_in != 0){
            cout << endl << "Please enter the number of steps " << joint_in << endl;
            cout << "input: ";
            cin >> value_in;
            d.r[joint_in]= value_in;
        }

    } while (joint_in!=0);

    return d;

}

// Bot runtime for forward-kinematic operation with manually entered joint values //
void forward_bot1()
{
    using namespace std;
    Microbot robot;
    char input = 'y';         // not the best, i know
    Registerspace delta;

    // SET SPEED //
    int spe = set_speed();

    // MOVE LOOP //
    do{
        // SET JOINTS //
        delta = manual_set_joints(delta);

        // MOVE //
     //   robot.SendStep(spe, delta);	        // commented out so it wont ruin my computer
        do
        {
            cout << "Continue? [y/n]" << endl;
            cin >> input;
        } while( !cin.fail() && input!='y' && input!='n' );
        cin.clear();
        cin.ignore(INT_MAX, '\n');

    }while(input == 'y');

    return;

}

// Main Menu
void main_menu()
{
    int input = 1;
    do{
        using namespace std;
        cout << endl << endl;
        cout << "-----WELCOME TO MICROBOT CONTROL-----" << endl << endl;
        cout << "Please select from the following options..." << endl;
        cout << "1. manual joint value entry" << endl;
        cout << "2. forward kinematics calculator" << endl;
        cout << "3. inverse kinematics calculator" << endl;
        cout << "0. exit" << endl;
        cout << endl << ">>";

        while (!(cin >> input) || input < 0 || input > 3)    //WARN: just hitting enter is bad
        {
            cout << "Bad input - try again: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }

        switch(input){
            case 1:
                forward_bot1();
                break;
            case 2:
                cout << endl << "Function not yet complete!" << endl;
                break;
            case 3:
                cout << endl << "Function not yet complete!" << endl;
                break;
            case 0:
                cout << endl << "exiting..." << endl;
                break;
        }
    } while(input != 0);

    return;
}



int main()
{

    main_menu();


    return 0;

}
