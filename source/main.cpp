#include "kinematics.h"
#include<iostream> 	// get standard I/O facilities
#include<string> 	// get standard string facilities

void main()
{	
	Microbot robot;				// Local variable of the microbot class
    Registerspace delta;		// Local variable for input of motor steps
    int spe=240;				// Motor speed; should not be higher than 240


// Example; replace it with your own program

	using namespace std; 					// gain access to standard library
	cout<< "Please enter delta.r[7]:";
	string d7;
	cin>> d7;
	cout<< "Please enter delta.r[6]:";
	string d6;
	cin>> d6;
	cout<< "Please enter delta.r[5]:";
	string d5;
	cin>> d5;
	cout<< "Please enter delta.r[4]:";
	string d4;
	cin>> d4;
	cout<< "Please enter delta.r[3]:";
	string d3;
	cin>> d3;
	cout<< "Please enter delta.r[2]:";
	string d2;
	cin>> d2;
	cout<< "Please enter delta.r[1]:";
	string d1;
	cin>> d1;


	
	delta.r[7]=std::stoi( d7 );				// Assign number of steps for each motor
	delta.r[6]=std::stoi( d6 );				// converting strings to integers 
	delta.r[5]=std::stoi( d5 );
	delta.r[4]=std::stoi( d4 );
    delta.r[3]=std::stoi( d3 );
	delta.r[2]=std::stoi( d2 );	
    delta.r[1]=-std::stoi( d1 ); 			//previously 500 constant

	robot.SendStep(spe, delta);	// Send instruction to the microbot

}