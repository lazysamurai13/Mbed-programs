#include "mbed.h"

InterruptIn adult_in (p5);  //adult requests entry
InterruptIn child_in (p6);  //child + parent request entry
InterruptIn fire_al (p7);   //Fire alarm

DigitalOut no_entry(p8);   //No entry sign
DigitalOut Barb1_ch(p9);   //Barber 1 chair
DigitalOut Barb2_ch(p10);  //Barber 2 chair
DigitalOut Barb3_ch(p11);  //Barber 3 chair
DigitalOut Wall_clk(p12);  //Wall clock
BusOut seating (p13,p14,p15,p16,p17,p18,p19,p20);
                                //waiting area chairs

int Time_ch1,Time_ch2,Time_ch3;
                        //Haircut timing info per chair

int Seats_pat,child_no,adult_no; //seating pattern,
                //no of children and parents waiting,
                //no of adults waiting

void adult_ISR(){
  if ((adult_no+child_no)<8){  //check for 1 space
      adult_no++;  //increase waiting adult no
      Seats_pat=Seats_pat<<1;  //customers shift left
      Seats_pat=Seats_pat|01;  //OR in new arrival
      }
      else {
          no_entry=1;
          wait_ms (40);
    //a symbolic flash, which upsets loop timing a little
          no_entry=0;
          }
}
 void child_ISR(){
   if ((adult_no+child_no)<7){
     //check for 2 spaces
      child_no=child_no+2;
     //increase waiting by child + parent
      Seats_pat=Seats_pat<<2;
     //increase seating pattern by 2
      Seats_pat=Seats_pat|03;  //OR in new arrivals
      }
      else {
          no_entry=1;
          wait_ms (40);
          no_entry=0;
          }
void fire_ISR(){
    no_entry=1;
    Barb1_ch=Barb2_ch=Barb3_ch=0;
     //clear barbers' chairs first
   while(Seats_pat!=0){
    //those in waiting area file out in orderly fashion
       Seats_pat=Seats_pat>>1;
       seating=Seats_pat;
    //update seating pattern display
       wait_ms(600);
       }
       child_no=0;
       adult_no=0;
       wait(20);
       no_entry=0;
}
int main(){
adult_in.rise(&adult_ISR);  //set up interrupts
child_in.rise(&child_ISR);
fire_al.rise(&fire_ISR);

    while(1){   // enter main while loop
        //Check seat 1
    //if chair occupied, decrement time counter
        if(Barb1_ch==1){
        Time_ch1--;
            if (Time_ch1==0)
            Barb1_ch=0;    //customer leaves chair and exits
            }
        else if(adult_no!=0){
            Barb1_ch=1;  //invite customer into chair
            adult_no--;  //one adult leaves waiting area
    //remaining customers shift right
            Seats_pat=Seats_pat>>1;
            Time_ch1=12; //set Timer
            }
//Check seat 3
   if(Barb3_ch==1){
          //if chair occupied, decrement time counter
    Time_ch3 --;
        if (Time_ch3==0){
        Barb3_ch=0;    //child leaves chair and exits
        child_no--;
  //accompanying parent leaves waiting area and exits
        Seats_pat=Seats_pat>>1;
  //remaining customers shift right
        }
    }
    else if(child_no!=0){
        Barb3_ch=1;  //invite child into chair
        child_no--;  //one child leaves waiting area
        Seats_pat=Seats_pat>>1;
   //remaining customers shift right
        Time_ch3=12; //set Timer
        }
    seating=Seats_pat;  //update seating pattern display
    wait_ms(1000);     //adjust for simulator convenience
   //notional time delay to set loop time
    Wall_clk=!Wall_clk;  //the wall clock ticks!
    }  //end of while (1)
}  //end of main()