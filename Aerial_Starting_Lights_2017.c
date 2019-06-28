#include <kipr/botball.h>

void timer(int light, int delay, char message[]);
void flash_five();

int i =0;
double start=0;
double counter=0;
double game_time=0;

int main()
{
    set_a_button_text("End");
  	set_c_button_text("Start");
 	//enable digital outs
 	for (i=0;i<10; i++){
    	set_digital_value(i,0);}
    ao();
  	for (i=0;i<10; i++){
    	set_digital_output(i,1);}
	while(!b_button()){
        display_clear();
  		printf("Press C Button to Start, Press A Button to end\n"); 
  
  		while(!c_button()){}       
		game_time=5.1+seconds();		
  		while(!a_button()&&game_time>seconds()){
    		timer(0, 5, "Game Starts in");
    		game_time=180+seconds();
    		timer(1, 175, "Lights on for");
    		//timer(0, 100, "Lights off for");
    		flash_five();
        }
    }
  	return 0;
}

void timer(int light, int delay, char message[])
{
	for (i=0;i<10; i++){
    	set_digital_value(i,light);}
  	for (i=0;i<4; i++){
    	if(light==1){mav(i,1500);}
		else{ao();}
    }
  	start=(delay+seconds()+0.1);
  	while(start>seconds()){
    	display_clear();
    	printf("%s %d seconds\n\n\n%d Seconds Remaining\n\nPress A Button to end\n", message, (int)(start-seconds()), (int)(game_time-seconds()));
    	counter=seconds()+1;
    	while(seconds()<counter){if(a_button()){break;}}
    	if(a_button()){break;}
    }
 
  	for (i=0;i<10; i++){
    	set_digital_value(i,0);}
    ao();
}

void flash_five()
{
	int j=0;
 
  	for(j=6;j>0;j--){
  		display_clear();
    	printf("\n\n\n%d Seconds Remaining\n\nPress A Button to end\n", (int)(game_time-seconds()));
    
    	if(a_button()){break;}
   
  		for (i=0;i<10; i++){
    		set_digital_value(i,1);}
  		for (i=0;i<4; i++){
    		mav(i,1500);}
 
		display_clear();
    	printf("\n\n\n%d Seconds Remaining\n\nPress A Button to end\n", (int)(game_time-seconds()));
		if(i>5){msleep(500);}
    	else{msleep(50*j);}
		if(a_button()){break;}
  
		for (i=0;i<10; i++){
    		set_digital_value(i,0);}
    	ao();

   		display_clear();
    	printf("\n\n\n%d Seconds Remaining\n\nPress A Button to end\n", (int)(game_time-seconds()));
		if(i>5){msleep(500);}
    	else{msleep(50*j);}
		if(a_button()){break;}
	}
}
