#ifndef SERVO_INIT
#define SERVO_INIT

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
              angle_upper_byte_servo6, angle_lower_byte_servo6,
			  angle_upper_byte_servo10, angle_lower_byte_servo10,
              angle_upper_byte_servo7, angle_lower_byte_servo7,
			  angle_upper_byte_servo9, angle_lower_byte_servo9,
              angle_upper_byte_servo8, angle_lower_byte_servo8;
			  
unsigned char angle_upper_byte_servo11, angle_lower_byte_servo11,
			  angle_upper_byte_servo12, angle_lower_byte_servo12,
			  angle_upper_byte_servo13, angle_lower_byte_servo13,
			  angle_upper_byte_servo14, angle_lower_byte_servo14,
			  angle_upper_byte_servo15, angle_lower_byte_servo15,
              angle_upper_byte_servo16, angle_lower_byte_servo16;
//--------------------------------------------------------------------------------
//port initialisation for Servos i/p's
//--------------------------------------------------------------------------------
void servo_pin_config (void)
{
	DDRE  = 0xFF;    //declare 0,1,2,3,4,5,6,7 pins of PORTE as output
	PORTE = 0x00;
	DDRB = 0xFF;     //declare 0,1,2,3,4,5,6,7 pins of PORTB as output
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

void reset_servo11 (void)
{ PORTB = PORTB & 0xFB; }

void set_servo11 (void)
{ PORTB = PORTB | 0x04; }

void reset_servo12 (void)
{ PORTB = PORTB & 0xF7; }

void set_servo12 (void)
{ PORTB = PORTB | 0x08; }

void reset_servo13 (void)
{ PORTB = PORTB & 0xEF; }

void set_servo13 (void)
{ PORTB = PORTB | 0x10; }

void reset_servo14 (void)
{ PORTB = PORTB & 0xDF; }

void set_servo14 (void)
{ PORTB = PORTB | 0x20; }

void reset_servo15 (void)
{ PORTB = PORTB & 0xBF; }

void set_servo15 (void)
{ PORTB = PORTB | 0x40; }

void reset_servo16 (void)
{ PORTB = PORTB & 0x7F; }

void set_servo16 (void)
{ PORTB = PORTB | 0x80; }


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
	if (set_number == 4) { reset_servo13(); }
	if (set_number == 5) { reset_servo16(); }
	
		
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
	if (set_number == 3) { reset_servo11(); }
	if (set_number == 4) { reset_servo14(); }
	
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
	if (set_number == 3) { reset_servo12(); }
	if (set_number == 4) { reset_servo15(); }
	
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

	
	if (set_number == 3)               // 4th set of servo motor
	{
		set_servo10();
		set_servo11();
		set_servo12();

		OCR1AH = angle_upper_byte_servo10;
		OCR1AL = angle_lower_byte_servo10;
		OCR1BH = angle_upper_byte_servo11;
		OCR1BL = angle_lower_byte_servo11;
		OCR1CH = angle_upper_byte_servo12;
		OCR1CL = angle_lower_byte_servo12;

	}
	
	if (set_number == 4)               // 5th set of servo motor
	{
		set_servo13();
		set_servo14();
		set_servo15();
		OCR1AH = angle_upper_byte_servo13;
		OCR1AL = angle_lower_byte_servo13;
		OCR1BH = angle_upper_byte_servo14;
		OCR1BL = angle_lower_byte_servo14;
		OCR1CH = angle_upper_byte_servo15;
		OCR1CL = angle_lower_byte_servo15;
	}
	
	if (set_number == 5)               // 6th set of servo motor
	{
		set_servo16();
		
		OCR1AH = angle_upper_byte_servo16;
		OCR1AL = angle_lower_byte_servo16;
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


void angle_servo10 (unsigned char angle)                // for servo10
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo10 = angle_upper_byte;
	angle_lower_byte_servo10 = angle_lower_byte;
}


void angle_servo11 (unsigned char angle)                // for servo11
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo11 = angle_upper_byte;
	angle_lower_byte_servo11 = angle_lower_byte;
}

void angle_servo12 (unsigned char angle)                // for servo12
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo12 = angle_upper_byte;
	angle_lower_byte_servo12 = angle_lower_byte;
}

void angle_servo13 (unsigned char angle)                // for servo13
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo13 = angle_upper_byte;
	angle_lower_byte_servo13 = angle_lower_byte;
}

void angle_servo14 (unsigned char angle)                // for servo14
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo14 = angle_upper_byte;
	angle_lower_byte_servo14 = angle_lower_byte;
}

void angle_servo15 (unsigned char angle)                // for servo15
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo15 = angle_upper_byte;
	angle_lower_byte_servo15 = angle_lower_byte;
}

void angle_servo16 (unsigned char angle)                // for servo16
{
	degree = angle;
	angle_value_calculation();
	angle_upper_byte_servo16 = angle_upper_byte;
	angle_lower_byte_servo16 = angle_lower_byte;
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


#endif