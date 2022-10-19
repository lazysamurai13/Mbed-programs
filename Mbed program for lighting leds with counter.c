#include "mbed.h"

#define BUTTON_1 p5
#define BUTTON_2 p6
#define BUTTON_3 p7
#define BUTTON_4 p8

#define RED_LED p9
#define YELLOW_LED p10
#define BLUE_LED p11

//Define outputs
DigitalOut led1(RED_LED);
DigitalOut led2(YELLOW_LED);
DigitalOut led3(BLUE_LED);


//Define interrupt inputs
InterruptIn button_1(BUTTON_1);
InterruptIn button_2(BUTTON_2);
InterruptIn button_3(BUTTON_3);
InterruptIn button_4(BUTTON_4);

//Define counters
volatile unsigned int count1;
volatile unsigned int count2;
volatile unsigned int count3;
volatile unsigned int countmax;

void updateLEDs(){
    led1=0;
    led2=0;
    led3=0;

    if (count1==countmax)led1=1;
    if (count2==countmax)led2=1;
    if (count3==countmax)led3=1;

}


//Define ISRs for the interrupts
void button_1_handler(){

	count1++;
	if(count1>countmax)countmax=count1;
	updateLEDs();

}

void button_2_handler(){

	count2++;
	if(count2>countmax)countmax=count2;
	updateLEDs();

}

void button_3_handler(){

	count3++;
	if(count3>countmax)countmax=count3;
	updateLEDs();

}

void button_4_handler(){

	led1=0;
	led2=0;
	led3=0;
	count1=0;
	count2=0;
	count3=0;
	countmax=0;
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){

	//Initially turn off all LEDs and set all the counters to 0
	led1=0;
	led2=0;
	led3=0;
	countmax=0;

	//Interrupt handlers
	button_1.rise(&button_1_handler);
	button_2.rise(&button_2_handler);
	button_3.rise(&button_3_handler);
	button_4.rise(&button_4_handler);

	//wait 100 ms
	while(1)
		wait_ms(100);
}
