/*
	KIPR 2022 TOURNAMENT STARTING LIGHTS
    by: Zachary Sasser
    
    This program is based on the KIPR Aerial starting light program. It has been reconfigured for the 2022 game.
	The program displays a UI that has the KIPR logo, then when the user presses the right button it starts a countdown.
    After the 3 second countdown, the lights turn on for <initialOnTime> seconds, then turn off and stay off for <timeLimit> seconds.
	Finally, the lights flash for <flashTime> seconds to signal the end of the round.
*/

//Note: Total time = (initialOnTime + timeLimit + flashTime) seconds
int initialOnTime = 15; //Amount of time the lights are on in the beginning
int timeLimit = 100; //Amount of time the lights are off while the game is running
int flashTime = 5; //Amount of time the lights flash at the end


#include <kipr/botball.h>

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
        graphics_rectangle(x1,x2,x1+190,x2+50,BLACK);
        graphics_rectangle_fill(x1+1,x2+1,x1+1+188*abs(time(NULL)-startTime)/timeLimit,x2+49,GREEN);
        g_printString("Keep It Simple",x1+5,x2+5,WHITE,1.8);
        g_printString("Stupid.",x1+30,x2+25,WHITE,2);
        graphics_update();
        msleep(500);
        if(left_button()){
            break;   
        }
    }
}

//Flashes the lights for a set amount of time
void flash(int timeLimit){
    int startTime = time(NULL);
    while(time(NULL)-startTime<=timeLimit){
        
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

//Generates the boxes for the graphic
void bottomSquares(int x1,int x2,int size){
	
    graphics_rectangle_fill(x1,x2,x1+4*size,x2+size,BROWN);
    
    graphics_rectangle(x1,x2,x1+size,x2+size,BLACK);
    graphics_rectangle(x1+size,x2,x1+2*size,x2+size,BLACK);
    graphics_rectangle(x1+2*size,x2,x1+3*size,x2+size,BLACK);
    graphics_rectangle(x1+3*size,x2,x1+4*size,x2+size,BLACK);
    
    graphics_update();
}

//Generates the other boxes for the graphic
void topSquares(int x1,int x2,int size){
 	graphics_rectangle_fill(x1,x2-size,x1+2*size,x2,BROWN);
    graphics_rectangle_fill(x1+0.5*size,x2-2*size,x1+1.5*size,x2-size,BROWN);
    
    
    graphics_rectangle(x1+size,x2-size,x1+2*size,x2,BLACK);
    graphics_rectangle(x1,x2-size,x1+size,x2,BLACK);
    graphics_rectangle(x1+0.5*size,x2-2*size,x1+1.5*size,x2-size,BLACK);
    graphics_update();
    
}

//Generates a square at the given coordinates
void squares(int x1,int x2, int size){
 	bottomSquares(x1,x2,size);
    topSquares(x1+0.5*size*(rand()%5),x2,size);
}

//Generates botguy graphic
void botguy(int x1, int x2, int size){
    graphics_rectangle_fill(x1-size/2,x2-size/2,x1+size/2,x2+size/2,RED);//BODY
    graphics_circle_fill(x1,x2,size/8,BLACK);//Antenna
    
    graphics_rectangle_fill(x1-size/4,x2-size/2,x1+size/4,x2-size,BLACK);//WHEELS
    graphics_rectangle_fill(x1-size/4,x2+size/2,x1+size/4,x2+size,BLACK);
}

//Generates the board graphic
void board(int x1, int x2, int size){
 	    graphics_rectangle(x1,x2,x1+2*size,x2+size,BLACK); //STARTBOX
		graphics_rectangle(x1,x2+size/2,x1+0.3*size,x2+size,BLACK);  
    
    	graphics_rectangle(x1+size/8,x2+size/8,x1+size/4,x2+size/4,RED); //POM BOX
    	graphics_circle_fill(x1+size*3/16,x2+size*3/16,size/32,GREEN);
    
    	graphics_circle_fill(x1+size*1.75,x2+size/4,size/4,RED); //CIRCLE TOP
    	graphics_circle_fill(x1+size*1.75,x2+size/4,size/4-3,WHITE);
    
        graphics_circle_fill(x1+size*1.75,x2+size*0.75,size/4,RED); //CIRCLE BOTTOM
    	graphics_circle_fill(x1+size*1.75,x2+size*0.75,size/4-3,WHITE);
    	
    	botguy(x1+size*1.75,x2+size*0.25+size*(0.5*(rand()%2)),size/8); //PUT BOTGUY IN A RANDOM PLACE
    
        squares(x1+size/2,x2+size*0.75,size*5/24);
    	graphics_update();
}

//Generates the initial 3 second countdown
void countDown(int x, int y){
 	graphics_rectangle_fill(x,y,472,y+35,WHITE);
    g_printString("3",x,y,BLACK,4);
    graphics_update();
    msleep(1000);

    graphics_rectangle_fill(x,y,472,y+35,WHITE);
    g_printString("2",x+30,y,BLACK,4);
    graphics_update();
    msleep(1000);

    graphics_rectangle_fill(x,y,472,y+35,WHITE);
    g_printString("1",x+60,y,BLACK,4);
    graphics_update();
    msleep(1000);

    graphics_rectangle_fill(x,y,472,y+35,WHITE);
    g_printString("GO!!!!",x+100,y,BLACK,4);
    graphics_update();   
}

int main()
{
    while(0<300){
        //initial setup
        srand(time(NULL));
        graphics_open(472,278);
        
        //KIPR logo
        graphics_fill(GRAY);
        graphics_rectangle_fill(120,20,310,200,BLACK);
        g_printString("KISS",125,25,WHITE,2.5);
        g_printString("INSTITUTE",125,70,WHITE,2.5);
        g_printString("FOR",280,70,WHITE,0.75);
        g_printString("PRACTICAL",125,115,WHITE,2.5);
        g_printString("ROBOTICS",125,160,WHITE,2.5);
        g_printString("Press right button to continue.",120,205,BLACK,1);
        g_printString("Press left button to exit.",120,215,BLACK,1);
        graphics_update();
        
        //Wait until user presses right or left button
        while(!right_button()){
            if(left_button()){
                return 0;   
            }
        }
    	while(right_button()){
            
        }
        
        
        //blank screen
		graphics_clear();
        graphics_fill(WHITE);
        
        //Create the game board graphic (KIPR aerial)
        board(2,40,200);

        g_printString("Press right button to start the game...",2,2,BLACK,1.70);
        graphics_update();

        //Wait for user input
        while(!right_button()){
            if(left_button()){
                return 0;   
            }
        }
    	while(right_button()){
            
        }
        msleep(1000);

        //Countdown for graphical effect
        countDown(2,2);
        
        //Turn lights on for <initialOnTime> seconds
        int i;
        for (i=0;i<10; i++){
                set_digital_value(i,1);}
        for (i=0;i<4; i++){
            mav(i,1500);}
        msleep(initialOnTime*1000);
        
        //Set lights off
        for (i=0;i<10; i++){
                set_digital_value(i,0);}
        ao();
        
        //Start timer and loading bar
        timer(100,50,timeLimit);
        
        //Flash the lights for <flashTime> seconds
        flash(flashTime);
        
        //Turn the lights off to finish
        for (i=0;i<10; i++){
                set_digital_value(i,0);}
        ao();
        
        //Close graphic window
    	graphics_close();
    }
    return 0;
}
