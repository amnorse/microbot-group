#include "kinematics.h"
#include <math.h>
#include <iostream>
#define PI 3.141592653589793238462643383279502884197169399375105820974944
#define CONVERT 180.0/PI
#define L1 100
#define L2 100
#define A1 177.8
#define A2 177.8
#define AW 96.5
#define H 195.0

float *forward_kin(float xyz[3], int t1, int t2, int t3, int t4, int t5)
{
    // SET DEFAULT FAIL //
    xyz[0] = -1;
    xyz[1] = -1;
    xyz[2] = -1;

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

    xyz[0] = x;
    xyz[1] = y;
    xyz[2] = z;

    return xyz;
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
// calculated inverse kinematics with magic //
Registerspace inverse_kin(int x, int y, int z, Registerspace reg)
{

    double hyp;
    double theta1;
    double theta2;
    double theta3;
    double alpha;
    double beta;


    hyp = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    theta1 = atan2(y,x)*(180/PI);
    //std::cout << "theta1: " << theta1 << std::endl;
    theta3 = acos((pow(hyp,2) - pow(A1,2) - pow(A2,2))/(2*A1*A2))*(180/PI);
    alpha = atan2(z, sqrt(pow(x,2) + pow(y,2)));
    beta = acos((pow(A2,2) - pow(A1,2) - pow(hyp,2))/(2*A1*hyp));
    theta2 = (alpha+beta)*(180/PI);
    theta3=180-theta2-theta3;
    std::cout << "theta2: " << theta2 << std::endl;

    reg.r[1] = theta1*19.64;
    reg.r[2] = -(theta2*19.64);
    reg.r[3] = -(theta3*11.55);
    return reg;
}

*/

Registerspace inverse_kin(int x, int y, int z, Registerspace reg)
{

    double hyp;
    double theta0;
    double theta1;
    double theta2;
    double theta3;
    double alpha;
    double beta;
    double phi;

    double np1;
    double np2;
    double z1;

/*
    z=z-250;
    theta1 = atan2(y,x)*(180/PI);
    hyp = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    alpha = atan2(z, sqrt(pow(x,2) + pow(y,2)));
    beta = acos((pow(A2,2) - pow(A1,2) - pow(hyp,2))/(-2*A1*hyp));
    theta2 = ((alpha+beta)*(180/PI));
    phi = acos((pow(A1,2) - pow(A2,2) - pow(hyp,2))/(-2*A2*hyp));
    theta3 = (180-(90-alpha)-phi)*(180/PI);


    //std::cout << "theta1: " << theta1 << std::endl;
    //theta3 = acos((pow(hyp,2) - pow(A1,2) - pow(A2,2))/(2*A1*A2))*(180/PI);
    //std::cout << "theta2: " << theta2 << std::endl;
*/


    theta0 = atan2(y,x);
    hyp = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    np2 = sqrt(pow(x,2) + pow(y,2));

    beta = atan2(z,np2);
    alpha = acos((-pow(A2,2) + pow(A1,2) + pow(hyp,2))/(2*A1*hyp));
    theta1 = (alpha + beta);

    np1 = A1 * cos(theta1);
    std::cout << "np1: " << np1 << std::endl;
    z1 = A1 * sin(theta1);
    std::cout << "z1: " << z1 << std::endl;
    theta2 = atan2((z - z1),(np2 - np1));

    std::cout << "theta0: " << theta0 << std::endl;
    std::cout << "theta1: " << theta1 << std::endl;
    std::cout << "theta2: " << theta2 << std::endl;


    reg.r[1] = theta0*19.64*(180/PI);
    reg.r[2] = -(theta1*19.64)*(180/PI);
    reg.r[3] = -(theta2*11.55)*(180/PI);
    return reg;
}


