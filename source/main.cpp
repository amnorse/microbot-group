#include "kinematics.h"

void main()
{	
	Microbot robot;				// Local variable of the microbot class
    Registerspace delta;		// Local variable for input of motor steps
    int spe=240;				// Motor speed; should not be higher than 240


// Example; replace it with your own program

	delta.r[7]=0;				// Assign number of steps for each motor
	delta.r[6]=0;
	delta.r[5]=0;
	delta.r[4]=0;
    delta.r[3]=0;
	delta.r[2]=0;	
    delta.r[1]=-500;

	robot.SendStep(spe, delta);	// Send instruction to the microbot

}