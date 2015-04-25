#include "kinematics.h"

Microbot::Microbot(){
	
	port.Open(1,9600);

};

int Microbot::SendStep(int speed, Registerspace del)
{
	int i;
	int ret_num=0;
	double timer=1000000;
	char ret[2];
	char spe[5], m1[6], m2[6], m3[6], m4[6], m5[6], m6[6], m7[6];
	char c[80] = "@STE ";
	

	_itoa(speed, spe, 10);
	_itoa(del.r[1], m1, 10);
	_itoa(del.r[2], m2, 10);
	_itoa(del.r[3], m3, 10);
	_itoa(del.r[4], m4, 10);
	_itoa(del.r[5], m5, 10);
	_itoa(del.r[6], m6, 10);
    _itoa(del.r[7], m7, 10);
	
	strcat(c, spe);
	strcat(c, ",");
	strcat(c, m1);
	strcat(c, ",");
	strcat(c, m2);
	strcat(c, ",");
	strcat(c, m3);
	strcat(c, ",");
	strcat(c, m4);
	strcat(c, ",");
	strcat(c, m5);
	strcat(c, ",");
	strcat(c, m6);	
	strcat(c, ",");
	strcat(c, m7);	
	strcat(c, "\r");

	// print statement for debugging; may be commented out afterwards
	printf("String = %s\n",c);

	fflush( stdin );

	i = strlen(c);
	port.SendData(c,i);

	
	while((ret_num==0) && (timer > 0))
			{			
			ret_num = port.ReadData(ret,2);
			timer = (timer - 0.25);
			}
	
	if(timer <= 0)
		printf("Error");
	
	if(ret_num!=0)
		{
		// print statement for debugging; may be commented out afterwards
		printf( "Return from Microbot: %c\n", ret[0]);
		ret[1] = '\0';
		i = atoi(ret);
		}
	
	return i;
	
}


int Microbot::SendClose(int speed, int force)
{

	int i;
	int ret_num=0;
	char ret[2];
	char spe[5];
	char c[80] = "@CLO ";

	Registerspace r;

	_itoa(speed, spe, 10);
	

	if (speed != -1)
	{
	strcat(c, spe);
	
	}

	strcat(c, "\r");

	printf("String = %s\n",c);

	fflush( stdin );

	i = strlen(c);

	port.SendData(c,i);

	i = 0;

	while(i==0)
		i = port.ReadData(ret,2);

	i = 1;

if (force != -1)
	{

	if (speed == -1)
	{speed = 221;}

	r.r[1] = 0;
	r.r[2] = 0;
	r.r[3] = 0;
	r.r[4] = 0;
	r.r[5] = 0;
	r.r[6] = -10*force;

	i = SendStep( speed, r );
	}

return i;		

}



int Microbot::SendRead(Registerspace *read)
{
	int	i, count=1;
	int a=0;
	int ret_num=0;


	char c[10] = "@READ\r";
	char d[80];

	i = strlen(c);
	port.SendData(c,i);

	while(ret_num==0)
		{			
			
			ret_num = port.ReadData(d,1);
	
		}
	

	while(a<2)
	{
		ret_num = 0;

		while(ret_num==0)
			ret_num = port.ReadData(d+count,1);
		
		if(d[count]=='\r')
			a++;

		count++;
	
	}
	
	d[count-1] = '\0';

	int index=2;
	int index1=1;

	while(d[index]!='\0')
	{

	read->r[index1]	 = atoi(d+index);

	index1++;

		while(d[index]!=','&&d[index]!='\0')
			index++;

		if(d[index]==',')
			index++;
	}

	//printf("Motor steps in ascii =  %s\n", d+2);
	
	

	return 0;
}


int Microbot::SendSet(int speed)
{	
	int	i;
	int ret_num=0;
	char ret[2], spe[5];
	char c[15] = "@SET";
	
	_itoa(speed, spe, 10);
	
	strcat(c, spe);
	strcat(c, ",");
	strcat(c, "\r");
	
	printf("String = %s\n",c);
	
	i = strlen(c);
	port.SendData(c,i);
	
	while(ret_num==0)
		ret_num = port.ReadData(ret,2);

	ret[1] = '\0';
	i = atoi(ret);
	
	return i;
}

int Microbot::SendReset()
{

	int i;
	int ret_num=0;
	char ret[2];
	char c[80] = "@RESET ";

	
	strcat(c, "\r");

	printf("String = %s\n",c);

	fflush( stdin );

	i = strlen(c);

	port.SendData(c,i);

	i = 0;

	while(i==0)
		i = port.ReadData(ret,2);

	i = 1;
return i;		

}
