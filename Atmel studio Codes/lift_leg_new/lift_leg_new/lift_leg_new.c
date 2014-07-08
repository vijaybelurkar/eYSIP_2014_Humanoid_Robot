/*
 * lift_leg_new.c
 *
 * Created: 18-06-2014 20:01:26
 *  Author: Vijay
 */ 



#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char set_number = 0;           // selecting the ser of servo
unsigned char angle_upper_byte = 0; 	// temprory storing upper byte of desired angle value
unsigned char angle_lower_byte = 0; 	// temprory storing lower byte of desired angle value
unsigned char degree = 0;
// final storing of temprory variable for individual servo as upper & lower bytes
unsigned char angle_upper_byte_servo1, angle_lower_byte_servo1,
              angle_upper_byte_servo2, angle_lower_byte_servo2,
              angle_upper_byte_servo3, angle_lower_byte_servo3,
              angle_upper_byte_servo4, angle_lower_byte_servo4;
unsigned char angle_upper_byte_servo5, angle_lower_byte_servo5,
              angle_upper_byte_servo6, angle_lower_byte_servo6,angle_upper_byte_servo10, angle_lower_byte_servo10,
              angle_upper_byte_servo7, angle_lower_byte_servo7,angle_upper_byte_servo9, angle_lower_byte_servo9,
              angle_upper_byte_servo8, angle_lower_byte_servo8;
//--------------------------------------------------------------------------------
//port initialisation for Servos i/p's
//--------------------------------------------------------------------------------
void servo_pin_config (void)
{
	DDRE  = 0xFF;    //PL 1,2,3,4,5,6,7 as output
	PORTE = 0x00;
	DDRB = 0x03;
	PORTB = 0x00;
}

//--------------------------------------------------------------------------------
// reset & set function of servos
//--------------------------------------------------------------------------------
void reset_servo1 (void)
{PORTE = PORTE & 0xFE;  }

void set_servo1 (void)
{ PORTE = PORTE | 0x01; }

void reset_servo2 (void)
{ PORTE = PORTE & 0xFD; }

void set_servo2 (void)
{ PORTE = PORTE | 0x02; }

void reset_servo3 (void)
{ PORTE = PORTE & 0xFB; }

void set_servo3 (void)
{ PORTE = PORTE | 0x04; }

void reset_servo4 (void)
{ PORTE = PORTE & 0xF7; }

void set_servo4 (void)
{ PORTE = PORTE | 0x08; }

void reset_servo5 (void)
{ PORTE = PORTE & 0xEF; }

void set_servo5 (void)
{ PORTE = PORTE | 0x10; }

void reset_servo6 (void)
{ PORTE = PORTE & 0xDF; }

void set_servo6 (void)
{ PORTE = PORTE | 0x20; }

void reset_servo7 (void)
{ PORTE = PORTE & 0xBF; }

void set_servo7 (void)
{ PORTE = PORTE | 0x40; }

void reset_servo8 (void)
{ PORTE = PORTE & 0x7F; }

void set_servo8 (void)
{ PORTE = PORTE | 0x80; }

void reset_servo9 (void)
{PORTB = PORTB & 0xFE;  }

void set_servo9 (void)
{ PORTB = PORTB | 0x01; }

void reset_servo10 (void)
{ PORTB = PORTB & 0xFD; }

void set_servo10 (void)
{ PORTB = PORTB | 0x02; }

//--------------------------------------------------------------------------------
// TIMER1 initialize - prescale:1
// WGM: 0) Normal, TOP=0xFFFF
// desired value: 400Hz
// actual value: 400.007Hz (0.0%)
//--------------------------------------------------------------------------------
void timer1_init(void)
{
	TCCR1B = 0x00; //stop
	TCNT1H = 0x70; //setup
	TCNT1L = 0x01;
	OCR1AH = 0x8F;
	OCR1AL = 0xFF;
	OCR1BH = 0x8F;
	OCR1BL = 0xFF;
	OCR1CH = 0x00;
	OCR1CL = 0x00;
	ICR1H  = 0x8F;
	ICR1L  = 0xFF;
	TCCR1A = 0x00;
	TCCR1C = 0x00;
	TCCR1B = 0x01; //start Timer
}


//--------------------------------------------------------------------------------
// timer1 comparatorA match with timer register ISR,
// This ISR used for reset servo on set number
//--------------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)
{
	//compare occured TCNT1=OCR1A
	if (set_number == 0) { reset_servo2(); }
	if (set_number == 1) { reset_servo3(); }
	if (set_number == 2) { reset_servo1(); }
	if (set_number == 3) { reset_servo10(); }
	
}

//--------------------------------------------------------------------------------
// timer1 comparatorB match with timer register ISR,
// This ISR used for reset servo set number
//--------------------------------------------------------------------------------
ISR(TIMER1_COMPB_vect)
{
	//compare occured TCNT1=OCR1B
	if (set_number == 0) { reset_servo4(); }
	if (set_number == 1) { reset_servo5(); }
	if (set_number == 2) { reset_servo8(); }
}

//--------------------------------------------------------------------------------
// timer1 comparatorC match with timer register ISR,
// This ISR used for reset servo set number
//--------------------------------------------------------------------------------
ISR(TIMER1_COMPC_vect)
{
	//compare occured TCNT1=OCR1c
	if (set_number == 0) { reset_servo6(); }
	if (set_number == 1) { reset_servo7(); }
	if (set_number == 2) { reset_servo9(); }
}

//--------------------------------------------------------------------------------
// timer1 overflow ISR,
// This ISR can be used to load the PWM value. Here each Servo motor is
// move between 0 to 180 degrees proportional to the pulse ON time between
// 0.5 to 2.2 ms with the frequency between 40 to 60 Hz. ie. 400Hz/8 = 50Hz
//--------------------------------------------------------------------------------
ISR(TIMER1_OVF_vect)
{
	//TIMER1 has overflowed
	TCNT1H = 0x70; //reload counter high value	for 400Hz
	TCNT1L = 0x01; //reload counter low value for 400Hz

	set_number ++;

	if (set_number>7)     				// 400Hz/8 = 50Hz
	{
		set_number = 0;
	}

	if (set_number == 0)               // 1st set of servo motor
	{
		set_servo2();
		set_servo4();
		set_servo6();
		OCR1AH = angle_upper_byte_servo2;
		OCR1AL = angle_lower_byte_servo2;
		OCR1BH = angle_upper_byte_servo4;
		OCR1BL = angle_lower_byte_servo4;
		OCR1CH = angle_upper_byte_servo6;
		OCR1CL = angle_lower_byte_servo6;
	}
	
	if (set_number == 1)               // 2nd set of servo motor
	{
		set_servo3();
		set_servo5();
		set_servo7();
		
		OCR1AH = angle_upper_byte_servo3;
		OCR1AL = angle_lower_byte_servo3;
		OCR1BH = angle_upper_byte_servo5;
		OCR1BL = angle_lower_byte_servo5;
		OCR1CH = angle_upper_byte_servo7;
		OCR1CL = angle_lower_byte_servo7;
	}
	
	if (set_number == 2)               // 3rd set of servo motor
	{
		set_servo1();
		set_servo8();
		set_servo9();
		OCR1AH = angle_upper_byte_servo1;
		OCR1AL = angle_lower_byte_servo1;
		OCR1BH = angle_upper_byte_servo8;
		OCR1BL = angle_lower_byte_servo8;
		OCR1CH = angle_upper_byte_servo9;
		OCR1CL = angle_lower_byte_servo9;
		
	}

	
	if (set_number == 3)               // 2nd set of servo motor
	{
		set_servo10();

		OCR1AH = angle_upper_byte_servo10;
		OCR1AL = angle_lower_byte_servo10;
	}
}

//--------------------------------------------------------------------------------
// function for angular movement calculation
//--------------------------------------------------------------------------------
void angle_value_calculation (void)
{
	unsigned int angle_value = 0;
	unsigned int temp = 0;
	if (degree > 180)
	degree = 180; // limiting the scope of the servo rotation
	
	angle_value = 0x8FAE + (139 * (unsigned char) degree); //actual constant is 139.4
	angle_lower_byte = (unsigned char) angle_value;        //separating the lower byte
	
	temp = angle_value >> 8;
	angle_upper_byte = (unsigned char) temp;               //separating the upper byte
}

//---------------------.-----------------------------------------------------------
// Function for individual servo angle calculation call with degree as parameter &
// store into respective variables.
//--------------------------------------------------------------------------------

void angle_servo1 (unsigned char angle)                // for servo1
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo1 = angle_upper_byte;
	angle_lower_byte_servo1 = angle_lower_byte;
}

void angle_servo2 (unsigned char angle)                // for servo2
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo2 = angle_upper_byte;
	angle_lower_byte_servo2 = angle_lower_byte;
}

void angle_servo3 (unsigned char angle)                // for servo3
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo3 = angle_upper_byte;
	angle_lower_byte_servo3 = angle_lower_byte;
}

void angle_servo4 (unsigned char angle)                // for servo4
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo4 = angle_upper_byte;
	angle_lower_byte_servo4 = angle_lower_byte;
}

void angle_servo5 (unsigned char angle)                // for servo5
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo5 = angle_upper_byte;
	angle_lower_byte_servo5 = angle_lower_byte;
}

void angle_servo6 (unsigned char angle)                // for servo6
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo6 = angle_upper_byte;
	angle_lower_byte_servo6 = angle_lower_byte;
}

void angle_servo7 (unsigned char angle)                // for servo7
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo7 = angle_upper_byte;
	angle_lower_byte_servo7 = angle_lower_byte;
}


void angle_servo8 (unsigned char angle)                // for servo8
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo8 = angle_upper_byte;
	angle_lower_byte_servo8 = angle_lower_byte;
}

void angle_servo9 (unsigned char angle)                // for servo9
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo9 = angle_upper_byte;
	angle_lower_byte_servo9 = angle_lower_byte;
}


void angle_servo10 (unsigned char angle)                // for servo1
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo10 = angle_upper_byte;
	angle_lower_byte_servo10 = angle_lower_byte;
}

//--------------------------------------------------------------------------------
//call this routine to initialize all peripherals
//--------------------------------------------------------------------------------
void init_devices(void)
{
	//stop errant interrupts until set up
	cli();                                // disable all interrupts

	servo_pin_config();                   // servo configuration
	timer1_init();                        // initilize timer1

	TIMSK1 = 0x0F;                        // timer1 interrupt sources
	
	sei(); //re-enable interrupts
	//all peripherals are now initialized
}

// initial values for all the servos

const int S1=90;
const int S2=94;
const int S3=98;
const int S4=84;
const int S5=16;
const int S6=170;
const int S7=85;
const int S8=88;
const int S9=90;
const int S10=93;




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
	

	_delay_ms(4000);     // delay of 4sec
}
//--------------------------------------------------------------------------------
//main fuction starts here
//--------------------------------------------------------------------------------
int main(void)
{
	
	int i;
	int j=0;
	//int k=0;
	init_devices();
    int r=17;
	int l=15;
	//initilise all servo with 90 degree calibration
	init_servos();
	
	
	
	
	//swing right lift left leg and get back to initial position
//----------------------------------------------------------------------------------	
	for(i=1; i<=r ; i++) //1. swing right
	{
		
		angle_servo1(S1+i);
		angle_servo2(S2+i);
		angle_servo9(S9+i);
		angle_servo10(S10+i);
		_delay_ms(50);
	}
	_delay_ms(1000);
	
		angle_servo9(S9+r+5); //2. tilt body towards left
	
	for (i=1; i<=36; i++) //3.lift left leg using servo 4 , 6  and 8
	{
		j=j+2;
		angle_servo4(S4-i);
		//angle_servo3(S3+i);
		
		angle_servo8(S8+i);
		//angle_servo7(S7-i);
		
		//angle_servo5(S5+j);
		angle_servo6(S6-j);
		_delay_ms(30);
		if (i==6)
		{
			
			angle_servo2(S2+r+4); //4. tilt left leg outward to prevent clash with right leg using servo 2
		}
	}
	angle_servo1(S1+r-10); // 5. tilt body right

	angle_servo3(S3-10); // 6. tilt body back for balancing
	
	_delay_ms(2000);
	j=0;
	
	
	
	//get to original position
	angle_servo3(S3);   // 7. inversion of step 6. Get body to original position
	for (i=1; i<=36; i++) // 8. inversion step 3 bend leg to initial
	{
		j=j+2;
		angle_servo4(S4-36+i);
		//angle_servo3(S3+30-i);
		
		angle_servo8(S8+36-i);
		//angle_servo7(S7-30+i);
		
		//angle_servo5(S5+60-j);
		angle_servo6(S6-72+j);
		_delay_ms(30);
	}
	
	_delay_ms(2000);
	j=0;
	angle_servo2(S2+r); // 9. inversion of step 4
	angle_servo9(S9+r); // 10. inversion of step 2
	angle_servo1(S1+r); // 11. inversion of step 5
	
	for(i=1; i<=r ; i++) // 12. inversion of 1. swing left back to initial position
	{
		angle_servo1(S1+r-i);
		angle_servo2(S2+r-i);
		angle_servo9(S9+r-i);
		angle_servo10(S10+r-i);
		_delay_ms(50);
	}
	_delay_ms(2000);
//-----------------------------------------------------------------------------



//swing left lift right leg and get back to initial position
//----------------------------------------------------------------------------------
for(i=1; i<=l ; i++) //1. swing left
{
	
	angle_servo1(S1-i);
	angle_servo2(S2-i);
	angle_servo9(S9-i);
	angle_servo10(S10-i);
	_delay_ms(50);
}
_delay_ms(1000);

angle_servo10(S10-l-3); //2. tilt body towards left

for (i=1; i<=36; i++) //3.lift left leg using servo 4 , 6  and 8
{
	j=j+2;
	//angle_servo4(S4-i);
	angle_servo3(S3+i);
	
	//angle_servo8(S8+i);
	angle_servo7(S7-i);
	
	angle_servo5(S5+j);
	//angle_servo6(S6-j);
	_delay_ms(30);
	if (i==6)
	{
		
		angle_servo1(S1-l-4); //4. tilt left leg outward to prevent clash with right leg using servo 2
	}
}
angle_servo2(S2-l+10); // 5. tilt body right

angle_servo4(S4+10); // 6. tilt body back for balancing

_delay_ms(2000);
j=0;



//get to original position
angle_servo4(S4);   // 7. inversion of step 6. Get body to original position
for (i=1; i<=36; i++) // 8. inversion step 3 bend leg to initial
{
	j=j+2;
	//angle_servo4(S4-30+i);
	angle_servo3(S3+36-i);
	
	//angle_servo8(S8+30-i);
	angle_servo7(S7-36+i);
	
	angle_servo5(S5+72-j);
	//angle_servo6(S6-60+j);
	_delay_ms(30);
}

_delay_ms(2000);
j=0;
angle_servo1(S1-l); // 9. inversion of step 4
angle_servo10(S10-l); // 10. inversion of step 2
angle_servo2(S2-l); // 11. inversion of step 5

for(i=1; i<=l ; i++) // 12. inversion of 1. swing left back to initial position
{
	angle_servo1(S1-l+i);
	angle_servo2(S2-l+i);
	angle_servo9(S9-l+i);
	angle_servo10(S10-l+i);
	_delay_ms(50);
}
_delay_ms(2000);
while(1)
{
	
}
//while(1);
}


//--------------------------------------------------------------------------------
