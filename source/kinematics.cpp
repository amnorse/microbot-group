#include "kinematics.h"
#include <math.h>
#define PI 3.141592653589793238462643383279502884197169399375105820974944
#define CONVERT 180.0/PI
#define L1 100
#define L2 100


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
