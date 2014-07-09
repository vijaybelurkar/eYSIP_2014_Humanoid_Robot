/*
 * Basic_Walk.c
 *
 * Created: 27-06-2014 18:12:56
 *  Author: Vijay
 */ 


#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "SERVO_16.h"

// initial values for all the servos
const int S1=90;
const int S2=94;
const int S3=98;
const int S4=84;
const int S5=19;
const int S6=167;
const int S7=85;
const int S8=88;
const int S9=90;
const int S10=93;

const int S11=87;
const int S12=90;
const int S13=150;
const int S14=30;
const int S15=90;
const int S16=90;


// initialize all the servos for the bot to be standing straight
void init_servos(void)
{
	angle_servo1(S1);
	angle_servo2(S2);
	angle_servo3(S3);
	angle_servo4(S4);
	angle_servo5(S5);
	angle_servo6(S6);
	angle_servo7(S7);
	angle_servo8(S8);
	angle_servo9(S9);
	angle_servo10(S10);
	angle_servo11(S11);
	angle_servo12(S12);
	angle_servo13(S13);
	angle_servo14(S14);
	angle_servo15(S15);
	angle_servo16(S16);
	

	_delay_ms(6000);     // delay of 4sec
}

/* ---------------This entire walking function is defined to start walking by first lifting the left only------------------ */


//----------------------------------------------------------------------------------------------------------
// This function is required to initiate the walking process. This function is called only once to trigger
// the walking process and then taken over by walk1 function
//----------------------------------------------------------------------------------------------------------
void prewalk(void)
{
	int i;     // variables required for loops
	int j=0;
	int r=17;  // 17 degree swing towards right for CG balance
	
	for(i=1; i<=r ; i++) // swing right for CG balance with specified angle (here r=17')
	{
		
		angle_servo1(S1+i);
		angle_servo2(S2+i);
		angle_servo9(S9+i);
		angle_servo10(S10+i);
		_delay_ms(30);
	}
	_delay_ms(500);
	
	angle_servo9(S9+r+6); // tilt body towards right. this for additional balancing of the bot
	
	for (i=1; i<=36; i++) //lift left leg using servo 4 , 6  and 8
	{
		j=j+2;
		angle_servo4(S4-i);
		angle_servo6(S6-j);
		angle_servo8(S8+i);
		_delay_ms(20);
		if (i==6)          //  tilt body right after the leg is lifted to certain amount (here 6')
		{
			angle_servo1(S1+r-10); //  tilt body right
			angle_servo2(S2+r+4); // tilt left leg outward to prevent clash with right leg using servo 2
		}
	}
	j=0;
	
}
//--------------------end of prewalk function

//----------------------------------------------------------------------------------------------------------
// This function is used to walk 1 step each with right and left leg from a predefined position
// The angle values specified are applicable to change by small amount depending upon the use servo motors
//----------------------------------------------------------------------------------------------------------
void walk(void)
{
	int i;
	int j=0;
	int r=17;  // 17 degree swing towards right for CG balance
	int l=17;  // 17 degree swing towards left for CG balance
	//----------------------------------------------------------------------------------------------------------
	// right and left angles are defined separately because they may vary with time due to wear and tear of servo
	// motors
	//----------------------------------------------------------------------------------------------------------
	
	//----------------------------------------------------------------------------------------------------------
	// position of bot : left leg raised and body balanced on right leg using right swing and right leg is fully
	// straight
	// step.1. tilt body back for balancing by 10'
	//----------------------------------------------------------------------------------------------------------
	angle_servo3(S3-10);
	
	//----------------------------------------------------------------------------------------------------------
	// position of bot : left leg lifted by right swing with body backwards
	// step.2. bring the left leg down by straightening the left leg
	//----------------------------------------------------------------------------------------------------------
	for(i=1; i<=36; i++)
	{
		j=j+2;
		if(i<=23)
		{
		angle_servo6(S6-72+j); // change done
			
		}
		angle_servo8(S8+36-i);
		
		if(i<=10)
		{
			angle_servo3(S3-10+i);   // inversion of step.1. bring the body to its original position
		}
		_delay_ms(20);   //this delay basically gives the speed of the servo
	}
	j=0;
	//----------------------------------------------------------------------------------------------------------
	// position of bot : left leg forward with right still back
	// step.3.(mirror of step.9.) swing the body back to initial position i.e straight. for first iteration the
	// right swing was done by the prewalk function and then for successive iterations this right swing was done
	//	by step..
	// this loop also places left leg on the ground
	//----------------------------------------------------------------------------------------------------------
	for(i=1; i<=21 ; i++)
	{
		if(i<=7)
		{
			angle_servo1(S1+7-i);  // get the last position of servo and from there on get to the desired position
					// for which this loop is intended
			
		}
		if (i<=12)
		{
			
		}
		if(i<=r)
		{
			angle_servo9(S9+r-i);
			angle_servo10(S10+r-i);
			 // bring the entire body forward and place left leg o the ground using the ankle
			angle_servo7(S7-i);// of right leg servo 7
			
			
		}
		
		angle_servo2(S2+r+4-i);  // get the last position of servo and from there on get to the desired position
		// for which this loop is intended
		
		_delay_ms(30);  //this delay basically gives the speed of the servo
	}
	_delay_ms(500);
	
	
	
	angle_servo3(S3-10); // step.4. bring the body back for balancing
	
	//----------------------------------------------------------------------------------------------------------
	// position of bot : left leg placed on the ground with straight body and still the right leg back
	// Step.5.(mirror of step.10.) this loop is used to swing left side to transfer the CG towards left
	//----------------------------------------------------------------------------------------------------------
	for(i=1; i<=l ; i++)
	{
		
		angle_servo1(S1-i);
		angle_servo2(S2-i);
		angle_servo9(S9-i);
		angle_servo10(S10-i);
		if(i<=9)
		{
			angle_servo8(S8+i); // used to get body front using left upper ankle (servo 8)
			
		}
		_delay_ms(30);   //this delay basically gives the speed of the servo
	}
	_delay_ms(500);
	
	angle_servo10(S10-l-4);  // tilt body towards left. this for additional balancing of the bot
	
	
	//----------------------------------------------------------------------------------------------------------
	// position of bot : left leg placed on the ground with bot tilted towards left and still the right leg back
	// step.6.(mirror of step.11.) this loop lifts and brings the right forward and straightens the left leg which
	// is still slightly bent
	//----------------------------------------------------------------------------------------------------------
	for (i=1; i<=36; i++)
	{
		
		j=j+2;
		angle_servo3(S3+i);
		angle_servo5(S5+j);
		if(i<=19)
		{
			angle_servo7(S7-r-i);
		}
		
		
		if(i<=27)
		{
			angle_servo6(S6-27+i);  // get the last position of servo and from there on get to the desired position for
									// which this loop is intended
			angle_servo4(S4-36+i);  // get the last position of servo and from there on get to the desired position for
									// which this loop is intended
		}
		if(i<=9)
		{
			angle_servo8(S8+9-i); // get the last position of servo and from there on get to the desired position
								// for which this loop is intended
			
			
		}
		
		
		if (i==15)           // 15 indicates that in the loop at time the body looses its balance and the following
					       	// actions have to be taken to correct it
		{
			angle_servo1(S1-l-9); // tilt right leg outward to prevent clash with left leg using servo 1 and servo 2
			angle_servo2(S2-l+13);
		}
		
		angle_servo11(S11+i); // take the hands backwards
		angle_servo12(S12-i);
		
		_delay_ms(20);   //this delay basically gives the speed of the servo
	}
	_delay_ms(500);
	j=0;
	
	
	//----------------------------------------------------------------------------------------------------------
	// position of bot : right leg raised and body balanced on left leg using left swing and left leg not fully
	// straight
	// step.7.(mirror of step.12.) straightens the left leg by nullifying the offsets in servos 4 or 8 or 6 to
	// get it back to its initial positions
	//----------------------------------------------------------------------------------------------------------
	for(i=1; i<=36; i++)
	{
		if(i<=4)
		{
			angle_servo4(S4-9+i);  // bring the left close to initial but not fully. This is done for balancing.
								   // (angles are arbitrary found by observations)
		}
		if(i<=3)
		{
			angle_servo8(S8-i);
		}
		angle_servo11(S11+36-i);  // brings both the hands backwards
		angle_servo12(S12-36+i);
		_delay_ms(30);  //this delay basically gives the speed of the servo
	}
	
	
	
	//----------------------------------------------------------------------------------------------------------
	// position of bot : right leg raised and body balanced on left leg using left swing and left leg is now fully
	// straight
	// step.8. (mirror of step.2.) bring the right leg down by straightening the right leg
	//----------------------------------------------------------------------------------------------------------
	for(i=1; i<=36; i++)
	{
		j=j+2;
		if(i<=25)
		{
			angle_servo5(S5+72-j);; // changedone
		}
			angle_servo7(S7-36+i);
		
		_delay_ms(20);
	}
	_delay_ms(500);  //this delay basically gives the speed of the servo
	j=0;
	
	//----------------------------------------------------------------------------------------------------------
	// position of bot : right leg forward with left back
	// step.9. (mirror of step.3.) swing the body back to initial position i.e straight. this left swing was done
	// by step.5.
	// this loop also places right leg on the ground
	//----------------------------------------------------------------------------------------------------------
	for(i=1; i<=20 ; i++)
	{
		if(i<=2)
		{
			angle_servo2(S2-2+i);
			
		}
		if(i<=l)
		{
			angle_servo9(S9-l+i);
			angle_servo10(S10-l+i);
			angle_servo8(S8+i); // bring the entire body forward and place right leg on the ground using the upper
			                    // ankle of left leg servo 8
			angle_servo4(S4-5+i); // brings the body backwards for balancing
		}
		if(i<=8)
		{
			angle_servo6(S6-i);   // brings the body backwards for balancing
		}
		angle_servo1(S1-l-9+i);  // get the last position of servo and from there on get to the desired position
		                         // for which this loop is intended
		
		_delay_ms(30);    //this delay basically gives the speed of the servo
	}
	_delay_ms(500);
	
	
	//----------------------------------------------------------------------------------------------------------
	// position of bot : right leg placed on the ground with straight body and still the left leg back
	// Step.10. (mirror of step.5.) this loop is used to swing left side to transfer the CG towards left
	//----------------------------------------------------------------------------------------------------------
	for(i=1; i<=r ; i++)
	{
		
		angle_servo1(S1-5+i);  // get the last position of servo and from there on get to the desired position
		                       // for which this loop is intended
		angle_servo2(S2+i);
		angle_servo9(S9+i);
		angle_servo10(S10+i);
		if (i<=7)
		{
			angle_servo7(S7-i);  // used to get body front using right upper ankle (servo 7)
		}
		_delay_ms(30);   //this delay basically gives the speed of the servo
	}
	_delay_ms(500);
	
	
	angle_servo9(S9+r+6);  // tilt body towards right. this for additional balancing of the bot
	
	//----------------------------------------------------------------------------------------------------------
	// position of bot : right leg placed on the ground with bot tilted towards right and still the left leg back
	// step.11. (mirror of step.6.) this loop lifts and brings the left leg forward and straightens the right leg
	// which is still slightly bent
	//----------------------------------------------------------------------------------------------------------
	for (i=1; i<=48; i++)
	{
		
		j=j+2;
		// left leg is lifted using servo 4 and 6
		
			angle_servo4(S4+12-i);
		
		if(i<=32)
		{
			angle_servo6(S6-8-j);
		}
		
		if(i<=22) // straighten the right leg using servo 5 ,3 and 7
		{
			angle_servo5(S5+27-i);  // get the last position of servo and from there on get to the desired position
									// for which this loop is intended
			angle_servo3(S3+36-i);  // get the last position of servo and from there on get to the desired position
									// for which this loop is intended
			
		}
		if(i<=7)
		{
			angle_servo7(S7-7+i);  // get the last position of servo and from there on get to the desired position
								   // for which this loop is intended
		}
		
		if(i<=19)
		{
			angle_servo8(S8+l+i);
		}
		
		
		if (i==15)           // 15 indicates that in the loop at time the body looses its balance and the following
							 // actions have to be taken to correct it
		{
			
			angle_servo1(S1+r-10); //tilt left leg outward to prevent clash with right leg using servo 1 and 2
			angle_servo2(S2+r+4);
		}
		angle_servo11(S11+i); // take both the hands backwards
		angle_servo12(S12-i);
		
		_delay_ms(20);   //this delay basically gives the speed of the servo
	}
	_delay_ms(500);
	j=0;
	
	//angle_servo3(S3-10); // tilt body back for balancing
	
	
	//----------------------------------------------------------------------------------------------------------
	// position of bot : left leg raised and body balanced on right leg using right swing and right leg not fully
	// straight
	// step.12.(mirror of step.7.) straightens the right leg by nullifying the offsets in servos 3 or 5 or 7 to
	// get it back to its initial positions
	//----------------------------------------------------------------------------------------------------------
	for(i=1; i<=14; i++)
	{
		if(i<=5)
		{
			angle_servo5(S5+5-i);
		}
		if(i<=14)
		{
			angle_servo3(S3+14-i);
		}
		
		_delay_ms(30);  //this delay basically gives the speed of the servo
	}
	_delay_ms(500);
}

//-----------------------------------------------------------------------------------------------------end of function


//------------------------------------MAIN FUNCTION----------------------------------------------------------------
int main(void)
{
	init_devices();
	
	//initilise all servo with 90 degree calibration
	init_servos();
	
	angle_servo11(S11+30);
	angle_servo12(S12-30);
	_delay_ms(2000);
	prewalk();
	while(1)
	{
		
		walk();
	}
	
}