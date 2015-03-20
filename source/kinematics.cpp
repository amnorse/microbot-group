#include "kinematics.h"
#include <math.h>
#define PI 3.141592653589793238462643383279502884197169399375105820974944
#define CONVERT 180.0/PI
#define L1 100
#define L2 100

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
