/*
	ELE418 - Robot Intelligence.
	Header file containing definitions of the Microbot class.
	This class contains data members and functions dealing
	with the Microbot, under development for the Simubot Project.

	Last revision date : 2-4-99

	by Jamie Stultz
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serial.h"


#define OUT_OF_WORKSPACE -1
#define BASE_ANGLE_EXCEEDED -2
#define SHOULDER_ANGLE_EXCEEDED -3
#define ELBOW_ANGLE_EXCEEDED -4
#define PITCH_ANGLE_EXCEEDED -5
#define ROLL_ANGLE_EXCEEDED -6
#define FINGER_HITS_BODY -7
#define WRIST_HITS_BODY -8
#define FINGER_HITS_TABLE -9
#define WRIST_HITS_TABLE -10
#define FINGER_HITS_BASE -11
#define GRIPPER_WIDTH -12
#define	LL 3.8
#define L 7.0
#define H 7.68
#define R1 0.0
#define HAND_WIDTH 1.5
#define WRIST_WIDTH 0.6
#define MAX_GRIP_WIDTH 2.5
#define BODY_RADIUS 2
#define BASE_HEIGHT 1.5
#define BASE_X 2
#define BASE_Y 3
#define ROBOT_BASE_HEIGHT 10
#define PI 3.141592653589793238462643383279502884197169399375105820974944
#define CONVER PI/180.0
#define BASE_STEPS 7072
#define SHOULDER_STEPS 7072
#define ELBOW_STEPS 4158
#define RIGHT_STEPS 1536
#define LEFT_STEPS 1536
#define GRIPPER_STEPS 375

//Function forward declarations
int base(int x, int y);
int shoulder(int x, int y, int z);

// Public Data Structures
	struct Taskspace
	{
		double x,y,z,p,r,g;
	}; typedef struct Taskspace Taskspace;

	struct Jointspace
	{
		double t[7];
	}; typedef struct Jointspace Jointspace;

	struct Registerspace
	{
		int r[9];
	}; typedef struct Registerspace Registerspace;

	struct Pose
	{
		Taskspace ts;
		Jointspace js;
		Registerspace rs;
	}; typedef struct Pose Pose;

    struct IOspace
	{
		int lastkey;
		int enc;
		int open;
		int ctrl[4];
		int latch;
		int reg;
	}; typedef struct IOspace IOspace;


class Microbot
{
public:

// Constructors
	Microbot();
	Microbot(Taskspace home);

// Public Member Functions
	int MoveTo(Taskspace *t);
	int Error(int);
	int SetSpeed(int);
	void CurrentPosition(Taskspace *t);
	void CurrentPosition(Jointspace *j);
	void CurrentPosition(Registerspace *r);
	int SendStep(int speed, Registerspace delta);
	int SendClose(int speed, int force);
	int SendRead(Registerspace *read);
	int SendSet(int speed);
    int SendReset();

private:

// Private Data Members
	CSerial port;
	Pose pose;
	Registerspace delta;
	Pose home;
	int microbot_speed;

// Private Utility Member Functions
	double ABS(double);
	int ROUND(double);

// Private Kinematic Member Functions
	void SetTaskspace(Taskspace t);
	void SetJointspace(Jointspace j);
	void SetRegisterspace(Registerspace r);
	int InverseKinematics(Taskspace t, Jointspace *j);
	int ForwardKinematics(Jointspace j, Taskspace *t);
	int JointToRegister(Jointspace j, Registerspace *r);
	int RegisterToJoint(Registerspace r, Jointspace *j);
	int SetDelta(Registerspace start, Registerspace finish);

};
