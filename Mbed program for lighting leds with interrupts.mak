

#define BUTTON_1 p5
#define BUTTON_2 p6
#define BUTTON_3 p7
#define BUTTON_4 p8

#define RED_LED p9
#define YELLOW_LED p10
#define BLUE_LED p11

//Define outputs
DigitalOut red(RED_LED);
DigitalOut yellow(YELLOW_LED);
DigitalOut blue(BLUE_LED);

//Define interrupt inputs
InterruptIn s1(BUTTON_1);
InterruptIn s2(BUTTON_2);
InterruptIn s3(BUTTON_3);
InterruptIn s4(BUTTON_4);



//Define ISRs for the interrupts
void button_1_handler(){

	red=!red;

}

void button_2_handler(){

	blue=!blue;

}

void button_3_handler(){

	yellow=!yellow;

}

void button_4_handler(){

	red=1;
	yellow=1;
	blue=1;

}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){

	//Initially turn off all LEDs
	red=0;
	blue=0;
	yellow=0;

    //Interrupt handlers
    //Attach the address of the ISR to the rising edge
	s1.rise(&button_1_handler);
	s2.rise(&button_2_handler);
	s3.rise(&button_3_handler);
	s4.rise(&button_4_handler);

	//wait 100 ms
	while(1)
		wait_ms(100);
}

