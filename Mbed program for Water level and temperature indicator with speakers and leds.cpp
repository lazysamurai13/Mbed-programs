#include "mbed.h"

#define SPEAKER p21
#define AIN1 p15
#define AIN2 p16
#define LED p22


//Define the PWM speaker output
PwmOut speaker(SPEAKER);
DigitalOut led(LED);

//Define analog inputs
AnalogIn temp(AIN1);
AnalogIn level(AIN2);
float val1;
float val2;
float i,hival, loval;


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
int main(){
    while(1) {
        speaker=0.5;//set a 0.5 duty cycle, which won't change
        while (level.read()<0.75){
            led = !led;
            for(i=0; i<1; i+=0.05){   //20 steps
                speaker.period(0.010-(0.008*i)); //sweep starts f=100, ends f=500
                wait_ms (50);
                }//end of for, which lasts approx
             //20x50 = 1000 ms
            }
        led=0;
        if((temp.read()>0.66) && (level.read() == 1)){ //is temp too high?
            hival = 0.001; //set 1000 Hz as upper tone
            loval = 0.005; //set 200 Hz as lower tone
        }
        if((temp.read()<0.66) && (temp.read()>0.33) && (level.read() ==1)){
            hival = 0.002; //set 500 Hz as upper tone
            loval = 0.002; //set 500 Hz as lower tone
        }
        if((temp.read()<0.33) && (level.read() == 1)){ //is temp too cold?
            hival = 0.005; //set 200 Hz as tone
            loval = 1; //no output wanted for 2nd tone, //so set to (inaudible)1 Hz == 1)
        }
        //emit tones
        speaker.period (hival);
        wait_ms (500);
        speaker.period (loval);
        wait_ms (500);
    }// end of while(1)
}


