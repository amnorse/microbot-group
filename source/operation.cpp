//============================================================================
// Name        : Microbot_c++.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "kinematics.h"
#include "operation.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <typeinfo>

#define INT_MAX 100

// memory for current x,y,z location
//
// access type 1 = set memory, 2 = get, 3 = set and get
int get_steps(Registerspace *present_mem_contents, Registerspace new_mem_contents, const int access_type)
{
    if(access_type != 1 and access_type != 2 and access_type != 3){
        std::cout << "access type error" << std::endl;
        return 1;
    }

	static int mem1;
	static int mem2;
	static int mem3;
	static int mem4;
	static int mem5;
	static int mem6;
	static int mem7;
	static bool mem_init;

	if(!mem_init){
		mem1 = 0;
		mem2 = 10;
		mem3 = 1238;
		mem4 = 384;
		mem5 = 384;
		mem6 = 1238;
		mem7 = 0;
		mem_init = true;
	}

// DEBUG
//    std::cout << "mem: " << mem1 << std::endl;
//    std::cout << "mem: " << mem2 << std::endl;
//    std::cout << "mem: " << mem3 << std::endl;
//    std::cout << "mem: " << mem4 << std::endl;

	if(access_type == 2 or access_type == 3){
        present_mem_contents->r[1] = mem1;
        present_mem_contents->r[2] = mem2;
        present_mem_contents->r[3] = mem3;
        present_mem_contents->r[4] = mem4;
        present_mem_contents->r[5] = mem5;
        present_mem_contents->r[6] = mem6;
        present_mem_contents->r[7] = mem7;
	}

    if(access_type == 1 or access_type == 3){
	mem1 = new_mem_contents.r[1] ;
	mem2 = new_mem_contents.r[2] ;
	mem3 = new_mem_contents.r[3] ;
	mem4 = new_mem_contents.r[4] ;
	mem5 = new_mem_contents.r[5] ;
	mem6 = new_mem_contents.r[6] ;
	mem7 = new_mem_contents.r[7] ;
    }

	return 0;

}

// Calculate difference between current position and input position //
// Ignore register 0 - is always 1 //
// Note: do NOT pass microbot object by value //
Registerspace reg_difference(Microbot *rob,Registerspace reg)
{
	using namespace std;
    int error = 0;
	Registerspace beta, *beta_ptr;
	beta_ptr = &beta;

	error = get_steps(beta_ptr, reg, 3);
	if (error > 0)
        cout << "MEMORY ACCESS ERROR" << endl;


	// DEBUG //
//	for(int i=0; i < 9 ; i++){
//				cout << "Position delta-" << i << ": " << reg.r[i] << endl;
//			}
	// DEBUG END //

	for(int i=1; i < 8 ; i++){
		reg.r[i] = reg.r[i] - beta.r[i];
	}

	// DEBUG //
//	for(int i=0; i < 9 ; i++){
//			cout << "Position delta-" << i << ": " << reg.r[i] << endl;
//		}
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
    int crd[6]={0,0,0,0,0,0};
    d.r[7]=0;
	d.r[6]=0;
	d.r[5]=0;
	d.r[4]=0;
    d.r[3]=0;
	d.r[2]=0;
    d.r[1]=0;

    // safely take user input for x, y, z //
    for(int i = 1; i<7; i++){

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
            case 4:
				cout << endl << "Input roll: ";
				break;
            case 5:
				cout << endl << "Input pitch: ";
				break;
            case 6:
				cout << endl << "Input gripper: ";
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

     d = inverse_kin(crd[0], crd[1], crd[2],crd[3],crd[4],crd[5], d);

//    cout << endl <<  setw( 8 ) << "Joint" << setw( 13 ) << "Value" << endl;
//    cout << "---------------------------" << endl;
//    cout << setw( 8 )<< "Base" << setw( 13 ) << d.r[1] << endl;
//    cout << setw( 8 )<< "Shoulder" << setw( 13 ) << crd[ 1 ] << endl;
//    cout << setw( 8 )<< "Elbow" << setw( 13 ) << crd[ 2 ] << endl << endl;
    return d;
}

Registerspace move_vector_calc(Registerspace reg)
{

	Registerspace previous, *prev;
	prev = &previous;
	float  xyz[3], *xyzp;
	xyzp = &xyz[0];

    // SET DEFAULT FAIL //
    xyz[0] = -1;
    xyz[1] = -1;
    xyz[2] = -1;

	get_steps(prev, reg, 2);

	forward_kin(xyzp, previous.r[1], previous.r[2], previous.r[3], previous.r[4], previous.r[5]);

	std::cout << "  X: " << xyz[0] << "  Y: " <<  xyz[1] << "  Z: " <<xyz[2] << std::endl;

	return previous; // WRONG, just placeholder
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
//        robot.SendStep(spe, delta);	        // commented out so it wont ruin my computer

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
    invd.r[0]= 1;
    invd.r[1]= 0;
    invd.r[2]= 0;
    invd.r[3]= 0;
    invd.r[4]= 0;
    invd.r[5]= 0;
    invd.r[6]= 0;
    invd.r[7]= 0;
    invd.r[8]= 0;


    // SET SPEED //
    int spe = set_speed();

    // MOVE LOOP //
    do{
        // SET JOINTS //
    	invd = xyz_set_joints(invd);

        // COMPARE //
    	invd = reg_difference(rob, invd);

        // MOVE //
//       	robot.SendStep(spe, invd);	        // commented out so it wont ruin my computer


    }while(contin());

    return;
}

void line_bot()
{

    using namespace std;

    Microbot robot, *rob;
    rob = &robot;
    Registerspace previous, *prev;
    prev = &previous;
    Registerspace line_bot_reg;
    line_bot_reg.r[0]= 1;
    line_bot_reg.r[1]= 0;
    line_bot_reg.r[2]= 0;
    line_bot_reg.r[3]= 0;
    line_bot_reg.r[4]= 0;
    line_bot_reg.r[5]= 0;
    line_bot_reg.r[6]= 0;
    line_bot_reg.r[7]= 0;
    line_bot_reg.r[8]= 0;

    float xyz_start[6] = {125, 0, 0, 0, -90, 0};
    float *xyz_start_ptr = &xyz_start[0];
    float xyz_dest[6] = {125, 0, 0, 0, -90, 0};
    float xyz_vector[3] = {0, 0, 0};
    float xyz_dist;
    float x_slope, y_slope, z_slope;

    // SET SPEED //
    int spe = set_speed();

    // MOVE LOOP //
    do{


        // SAFE USER INPUT //
        for(int i = 1; i<7; i++){
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
                case 4:
                    cout << endl << "Input roll: ";
                    break;
                case 5:
                    cout << endl << "Input pitch: ";
                    break;
                case 6:
                    cout << endl << "Input gripper: ";
                    break;
                }

            while (!(cin >> xyz_dest[i-1]) || xyz_dest[i-1] < -1000 || xyz_dest[i-1] > 1000)         //WARN: limits not properly set on x,y,z
            {
                cout << "Bad input - try again: " << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
        }
        cout << endl;

        xyz_dist = sqrt(
                        pow( (xyz_start[0]-xyz_dest[0]) , 2)
                        +
                        pow( (xyz_start[1]-xyz_dest[1]) , 2)
                        +
                        pow( (xyz_start[2]-xyz_dest[2]) , 2));
        cout << "xyz_dist: " << xyz_dist << endl;

        x_slope = (xyz_dest[0]-xyz_start[0]) / xyz_dist;
        y_slope = (xyz_dest[1]-xyz_start[1]) / xyz_dist;
        z_slope = (xyz_dest[2]-xyz_start[2]) / xyz_dist;

        cout << "x slope: " << x_slope << endl;
        cout << "y slope: " << y_slope << endl;
        cout << "z slope: " << z_slope << endl;


                                // STEP THROUGH MOVE IN A LINE //
        // LINE IN 3D =  <x_start, y_start, z_start> + t * <x_slope, y_slope, z_slope> //

        for(float t = 10; t < xyz_dist; t = t + 10.0 ){

            xyz_vector[0] = xyz_start[0] + t * x_slope;
            xyz_vector[1] = xyz_start[1] + t * y_slope;
            xyz_vector[2] = xyz_start[2] + t * z_slope;
            cout << "x vec: " << xyz_vector[0] << endl;
            cout << "y vec: " << xyz_vector[1] << endl;
            cout << "z vec: " << xyz_vector[2] << endl;
            line_bot_reg = inverse_kin(xyz_vector[0], xyz_vector[1], xyz_vector[2], xyz_dest[3], xyz_dest[4], xyz_dest[5], line_bot_reg);
            line_bot_reg = reg_difference(rob, line_bot_reg);
  //          robot.SendStep(spe, line_bot_reg);
        }
        // final step //
        line_bot_reg = inverse_kin(xyz_dest[0], xyz_dest[1], xyz_dest[2], xyz_dest[3], xyz_dest[4], xyz_dest[5], line_bot_reg);
//        robot.SendStep(spe, line_bot_reg);

        // set starting position to new position //
        xyz_start[0] = xyz_dest[0];
        xyz_start[1] = xyz_dest[1];
        xyz_start[2] = xyz_dest[2];
        xyz_start[3] = xyz_dest[3];
        xyz_start[4] = xyz_dest[4];
        xyz_start[5] = xyz_dest[5];

    }while(contin());

    return;
}

void forward_bot2()
{
    using namespace std;
    int input;
    float xyz[3], *xyzp;
    int param[5] = {0,0,0,0,0};
    float cord[3] = {0,0,0};
    xyzp = &xyz[0];

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

        forward_kin(xyzp,param[0],param[1],param[2],param[3],param[4]);
        cord[0] = xyz[0];
        cord[1] = xyz[1];
        cord[2] = xyz[2];

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
        cout << "1. manual joint entry move" << endl;
        cout << "2. forward kinematics calculator" << endl;
        cout << "3. Move with XYZ coordinates" << endl;
        cout << "4. Move in a line with XYZ coordinates" << endl;
        cout << "0. exit" << endl;
        cout << endl << ">>";

        while (!(cin >> input) || input < 0 || input > 4)    //WARN: just hitting enter is bad
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
            case 4:
                line_bot();
                break;
            case 0:
                cout << endl << "exiting..." << endl;
                break;
        }
    } while(input != 0);

    return;
}
