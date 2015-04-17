//============================================================================
// Name        : Microbot_c++.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "kinematics.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <typeinfo>

#define INT_MAX 100


// Calculate difference between current position and input position //
// Ignore register 0 - is always 1 //
// Note: do NOT pass microbot object by value //
Registerspace reg_difference(Microbot *rob,Registerspace reg)
{
	using namespace std;

	Registerspace beta, *beta_ptr;
	beta_ptr = &beta;
	rob->SendRead(beta_ptr);

	// DEBUG //
	for(int i=0; i < 9 ; i++){
				cout << "Position delta-" << i << ": " << reg.r[i] << endl;
			}
	// DEBUG END //


	for(int i=1; i < 8 ; i++){
		reg.r[i] = reg.r[i] - beta.r[i];
	}


	// DEBUG //
	for(int i=0; i < 9 ; i++){
			cout << "Position delta-" << i << ": " << reg.r[i] << endl;
		}
	// DEBUG END //

	return reg;
}

// Safe user continue option //
bool contin()
{
    using namespace std;
    char input = 'a';

    // SAFE USER INPUT //
    cout << "continue? [y/n] : ";
    cin >> input;
    while(!cin.fail() && input!='y' && input!='n'){
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(),'\n');
        cout << endl << "Bad input -- try again: ";
        cin >> input;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    if(input == 'y'){
        return true;
    } else {
        return false;
    }
}

// Take x,y,z user input and set joints //
Registerspace xyz_set_joints(Registerspace d){

    using namespace std;
    int crd[3]={0,0,0};
    d.r[7]=0;
	d.r[6]=0;
	d.r[5]=0;
	d.r[4]=0;
    d.r[3]=0;
	d.r[2]=0;
    d.r[1]=0;

    // safely take user input for x, y, z //
    for(int i = 1; i<4; i++){

        switch(i){
            case 1:
                cout << endl << "Input coordinate x: ";
                break;
            case 2:
                cout << endl << "Input coordinate y: ";
                break;
            case 3:
                cout << endl << "Input coordinate z: ";
                break;
            }

        while (!(cin >> crd[i-1]) || crd[i-1] < -1000 || crd[i-1] > 1000)         //WARN: limits not properly set on x,y,z
        {
            cout << "Bad input - try again: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    }
    cout << "xyz set: " << d.r[0] << endl;

     d = inverse_kin(crd[0], crd[1], crd[2], d);




    cout << endl <<  setw( 8 ) << "Joint" << setw( 13 ) << "Value" << endl;
    cout << "---------------------------" << endl;
    cout << setw( 8 )<< "Base" << setw( 13 ) << d.r[1] << endl;
    cout << setw( 8 )<< "Shoulder" << setw( 13 ) << crd[ 1 ] << endl;
    cout << setw( 8 )<< "Elbow" << setw( 13 ) << crd[ 2 ] << endl << endl;
    return d;
}


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
    d.r[0]=1;

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
            cout << d.r[0] << endl;
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
    Registerspace delta;
    cout << "r0 init: " << delta.r[0] << endl;
    cout << "r0 init: " << delta.r[8] << endl;

    // SET SPEED //
    int spe = set_speed();

    // MOVE LOOP //
    do{
        // SET JOINTS //
        delta = manual_set_joints(delta);

        // MOVE //
        robot.SendStep(spe, delta);	        // commented out so it wont ruin my computer

    }while(contin());

    return;
}

// bot runtime for inverse kinematics operation
void inverse_bot()
{
    using namespace std;
    Microbot robot, *rob;
    rob = &robot;
    Registerspace invd;
    invd.r[0]=1;
    invd.r[1]=0;
    invd.r[2]=0;
    invd.r[3]=0;
    invd.r[4]=0;
    invd.r[5]=0;
    invd.r[6]=0;
    invd.r[7]=0;
    invd.r[8]=0;


    // SET SPEED //
    int spe = set_speed();

    // MOVE LOOP //
    do{
        // SET JOINTS //
    	invd = xyz_set_joints(invd);

        // COMPARE //
        invd = reg_difference(rob, invd);

        // MOVE //
        robot.SendStep(spe, invd);	        // commented out so it wont ruin my computer


    }while(contin());

    return;
}

void forward_bot2()
{
    using namespace std;
    int input;
    float *xyzP;
    int param[5] = {0,0,0,0,0};
    float cord[3] = {0,0,0};

    do{

        for(int i=1; i<6; i++){
            cout << endl << "Please enter joint " << i << ": ";
            while(!(cin >> input)){
                cout << endl << "Bad input -- try again: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            param[i-1] = input;
        }

        xyzP = forward_kin(cord,param[0],param[1],param[2],param[3],param[4]);
        cord[0] = *xyzP;
        cord[1] = *(xyzP + 1);
        cord[2] = *(xyzP + 2);

        cout << endl << "ONE: "  << cord[0]  << "  TWO: "  << cord[1]  << "  THREE: " << cord[2] << endl;

    } while(contin());


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
                forward_bot2();
                break;
            case 3:
                inverse_bot();
                break;
            case 0:
                cout << endl << "exiting..." << endl;
                break;
        }
    } while(input != 0);

    return;
}
