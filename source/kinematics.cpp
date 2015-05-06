#include "kinematics.h"
#include <math.h>
#include <iostream>
#define PI 3.141592653589793238462643383279502884197169399375105820974944
#define CONVERT 180.0/PI
#define L1 100
#define L2 100
#define A1 177.8
#define A2 177.8

#define L 177.8
#define LL 96.5
#define H 195.0

#define AW 96.5


<<<<<<< HEAD
float *forward_kin(float xyz[3], int t1, int t2, int t3, int t4, int t5)
=======
int forward_kin(float *xyzp, int t1, int t2, int t3, int t4, int t5)
>>>>>>> origin/lab2-norse
{

    float a1 = 177.8;
    float a2 = 177.8;
    float aw = 96.5;
    float p = .5 * (t5 + t4);
    float r = .5 * (t5 - t4);
    float h = 195.0;
    float z = h + a1*sin(t2*CONVERT) + a2*sin(t3*CONVERT) + aw*sin(p*CONVERT);
    float rad = a1*cos(t2*CONVERT) + a2*cos(t3*CONVERT) + aw*cos(p*CONVERT);
    float x = rad*cos(t1*CONVERT);
    float y = rad*sin(t1*CONVERT);

    *xyzp = x;
    std::cout << "x: " << x << std::endl;
    *(xyzp+1) = y;
    std::cout << "y: " << y << std::endl;
    *(xyzp+2) = z;
    std::cout << "z: " << z << std::endl;

    return 0;

}

int base(int x, int y) // Returns base movement
{
   return atan2(y,x)*CONVERT;
}

int shoulder(int x, int y, int z) // Returns shoulder movement
{
   double di = pow(x,2)+pow(y,2)+pow(z,2); //Origin to point
   double phi = acos((pow(L1,2)+pow(L2,2)-di)/(2*L1*L2))*CONVERT; // angle between L1 and L2

   double theta2 = 180-phi;
   int theta1 = atan2(z,(sqrt(pow(x,2)+pow(y,2))))*CONVERT;


   return theta1;
}


/*
Registerspace inverse_kin2(int xin, int yin, int zin, int roll, int pitch, int yaw, Registerspace reg)
{

    double hyp;
    double theta0;
    double theta1;
    double theta2;
    double theta3;
    double theta4;
    double theta5;
    double alpha;
    double beta;
    double phi;

    double np1;
    double np2;
    double z1;
    double wristz;
    double wristnp;

    int x;
    int y;
    int z;

    theta0 = atan2(yin,xin); //base

    // work backwards from the EOF to the wrist //
    wristnp = AW*cos(pitch*(PI/180));
    std::cout << "wrist np: " << wristnp << std::endl;
    wristz = AW*sin(pitch*(PI/180));
    std::cout << "wrist z: " << wristz << std::endl;
    z = zin - wristz;
    std::cout << "z: " << z << std::endl;
    x = xin - wristnp*cos(theta0);
    y = yin - wristnp*sin(theta0);


    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;




    hyp = sqrt(pow(x,2) + pow(y,2) + pow(z,2)); //true 3d hypotenuse
    np2 = sqrt(pow(x,2) + pow(y,2));			//length of line in plane of x and y

    beta = atan2(z,np2);
    std::cout << "beta: " << beta << std::endl;
    alpha = acos((-pow(A2,2) + pow(A1,2) + pow(hyp,2))/(2*A1*hyp));
    std::cout << "alpha: " << alpha << std::endl;
    theta1 = (alpha + beta);
    std::cout << "theta1: " << theta1 << std::endl;

    np1 = A1 * cos(theta1);
    std::cout << "np1: " << np1 << std::endl;
    z1 = A1 * sin(theta1);
    std::cout << "z1: " << z1 << std::endl;
    theta2 = atan2((z - z1),(np2 - np1));


    theta4 = roll + pitch;
    theta3 = pitch - roll;

    std::cout << "theta0: " << theta0 << std::endl;
    std::cout << "theta1: " << theta1 << std::endl;
    std::cout << "theta2: " << theta2 << std::endl;
    std::cout << "roll: " << roll << std::endl;
    std::cout << "pitch: " << pitch << std::endl;
    std::cout << "grip: " << yaw << std::endl;


    reg.r[1] =  theta0*19.64*(180/PI);
    reg.r[2] = -(theta1*19.64)*(180/PI);
    reg.r[3] = -((theta2)*11.55)*(180/PI);
    reg.r[4] = -(theta3*4.27);
    reg.r[5] = -((theta4)*4.27);
    reg.r[6] = -(theta2*11.55)*(180/PI);
    return reg;
}
*/
<<<<<<< HEAD


Registerspace inverse_kin(int x, int y, int zin, int roll, int pitch, int yaw, Registerspace reg)
{
	double theta1;
	double RR;
	double theta5;
	double theta4;
	double R0;
	double Z0;
	double beta;
	double alpha;
	double theta2;
	double theta3;
	int z;

	z = zin - 263;
=======
>>>>>>> origin/lab2-norse

	theta1 = atan2(y,x);
	std::cout << "theta1: " << theta1 << std::endl;

	RR = sqrt( pow(x,2) + pow(y,2) );
	std::cout << "RR: " << RR << std::endl;

	theta5 = pitch + roll;
	std::cout << "theta5: " << theta5 << std::endl;

	theta4 = pitch - roll;
	std::cout << "theta4: " << theta4 << std::endl;

	R0 = RR - LL * cos(pitch*(PI/180));
	std::cout << "R0: " << R0 << std::endl;

	Z0 = z - LL * sin(pitch*(PI/180));// - H;
	std::cout << "Z0: " << Z0 << std::endl;

	beta = atan2(Z0, R0);
	std::cout << "beta: " << beta << std::endl;

	alpha = atan(   sqrt(   ((4 * pow(L,2)) / (pow(R0,2) + pow(Z0,2))) - 1 )  );
	std::cout << "alpha: " << alpha << std::endl;

	theta2 = alpha + beta;
	std::cout << "theta2: " << theta2*(180/PI) << std::endl;

	theta3 = beta - alpha;
	std::cout << "theta3: " << theta3*(180/PI) << std::endl;

    reg.r[1] =  theta1*19.64*(180/PI);
    reg.r[2] =  -theta2*19.64*(180/PI);
    reg.r[3] =  -theta3*11.55*(180/PI);
    reg.r[4] =  -theta4*4.27;
    reg.r[5] =  -theta5*4.27;
    reg.r[6] =  -theta3*11.55*(180/PI);
    return reg;
}

Registerspace inverse_kin(int x, int y, int zin, int roll, int pitch, int yaw, Registerspace reg)
{
	double theta1;
	double RR;
	double theta5;
	double theta4;
	double R0;
	double Z0;
	double beta;
	double alpha;
	double theta2;
	double theta3;
	int z;

	z = zin - 263;
	theta1 = atan2(y,x);
	RR = sqrt( pow(x,2) + pow(y,2) );
	theta5 = pitch + roll;
	theta4 = pitch - roll;
	R0 = RR - LL * cos(pitch*(PI/180));
	Z0 = z - LL * sin(pitch*(PI/180));// - H;
	beta = atan2(Z0, R0);
	alpha = atan(   sqrt(   ((4 * pow(L,2)) / (pow(R0,2) + pow(Z0,2))) - 1 )  );
	theta2 = alpha + beta;
	theta3 = beta - alpha;

//    std::cout << "theta1: " << theta1 << std::endl;
//    std::cout << "RR: " << RR << std::endl;
//    std::cout << "theta5: " << theta5 << std::endl;
//    std::cout << "theta4: " << theta4 << std::endl;
//    std::cout << "R0: " << R0 << std::endl;
//    std::cout << "Z0: " << Z0 << std::endl;
//    std::cout << "beta: " << beta << std::endl;
//    std::cout << "alpha: " << alpha << std::endl;
//    std::cout << "theta2: " << theta2*(180/PI) << std::endl;
//    std::cout << "theta3: " << theta3*(180/PI) << std::endl;


    reg.r[1] =  theta1*19.64*(180/PI);
    reg.r[2] =  -theta2*19.64*(180/PI);
    reg.r[3] =  -theta3*11.55*(180/PI);
    reg.r[4] =  -theta4*4.27;
    reg.r[5] =  -theta5*4.27;
    reg.r[6] =  -theta3*11.55*(180/PI);
    return reg;
}

