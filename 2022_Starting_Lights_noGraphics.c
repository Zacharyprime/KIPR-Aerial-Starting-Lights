/*
	KIPR 2022 TOURNAMENT STARTING LIGHTS
    by: Zachary Sasser
    
    This program is based on the KIPR Aerial starting light program. It has been reconfigured for the 2022 game.
	When the user presses the button it starts a countdown.
    The lights turn on for <initialOnTime> seconds, then turn off and stay off for <timeLimit> seconds.
	Finally, the lights flash for <flashTime> seconds to signal the end of the round.
*/

//Note: Total time = (initialOnTime + timeLimit + flashTime) seconds
int initialOnTime = 15; //Amount of time the lights are on in the beginning
int timeLimit = 100; //Amount of time the lights are off while the game is running
int flashTime = 5; //Amount of time the lights flash at the end


#include <kipr/wombat.h>

#define BLUE 0,0,255
#define YELLOW 255,255,0
#define GREEN 0,255,0
#define RED 255,0,0
#define WHITE 255,255,255
#define BLACK 0,0,0
#define GRAY 155,155,155
#define BROWN 101,67,33

//Timer and loading bar
void timer(int x1, int x2,int timeLimit){
    int startTime = time(NULL);
    while(time(NULL)-startTime<=timeLimit){
        printf("Game in Session: \n Time Remaining: %d seconds \n", abs(timeLimit - (time(NULL)-startTime)) + flashTime);
        msleep(500);
        console_clear();
    }
}

//Flashes the lights for a set amount of time
void flash(int timeLimit){
    int startTime = time(0);
    while(time(0)-startTime<=timeLimit){
        
        int i;
        for (i=0;i<10; i++){
                set_digital_value(i,0);}
        ao();
        msleep(600);
        for (i=0;i<10; i++){
                set_digital_value(i,1);}
        for (i=0;i<4; i++){
            mav(i,1);}
        msleep(500);
        
        if(left_button()){
            break;   
        }
    }
}

int main()
{
    while(0<300){ 
	console_clear();
        printf("Starting Light Controll System: \n\n -- Press button to start game. -- \n \n \n Note: \nThis program cannot be ran from the IDE. Run on controller menu.");
        
        //Wait until user presses any button
        while(!any_button()){
            
        }
    	while(any_button()){
            
        }
        
        console_clear();
        
        printf("Ready, \n");
        msleep(1000);
        console_clear();
        printf("Set, \n");
        msleep(1000);
        console_clear();
        printf("GO!!! \n \n");
        
        //Turn lights on for <initialOnTime> seconds
        int i;
        for (i=0;i<10; i++){
                set_digital_value(i,1);}
        for (i=0;i<4; i++){
            mav(i,1500);}
		printf("Signalling Start (%d seconds) \n", initialOnTime);
        msleep(initialOnTime*1000);
        
        
        //Set lights off
        for (i=0;i<10; i++){
                set_digital_value(i,0);}
        ao();
        
        //Start timer and loading bar
        timer(100,50,timeLimit);
        
        console_clear();
        printf("Game in Session: \n Flashing to signal end of round for %d seconds \n.", flashTime);
        
        //Flash the lights for <flashTime> seconds
        flash(flashTime);
        
        console_clear();
        printf("Game complete! \n\n Judges may now score the round. \n \n Robots should not be moving at this time. \n Do not touch the board until scored. \n");
        
        //Turn the lights off to finish
        for (i=0;i<10; i++){
                set_digital_value(i,0);}
        ao();
        msleep(1000);
     	printf("\n Press button to reset game. \n");
        //Wait until user presses any button
        while(!any_button()){
            
        }
    	while(any_button()){
            
        }
    }
    return 0;
}
