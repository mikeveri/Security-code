/********************************* 8051 SECURITY CHECK program***********************************
***********************************Written By Verissimo Michael**********************************
****************************The program allows or denies an individual access********************
************************** to particular place or accessory being secured************************
******************************* by asking for the entry password*********************************
**********The program interfaces a keypad and LCD to the microcontroller*************************
***********and also provides the  additional feature of being able to change the password*******/


//import needed header file
#include <REG51.H>
//#include <eprom.h>
#include <display.H>
#include <keypad.H>

// define special function register for interupt
sfr EECON  = 0x96;

void enter (void);
	void cancel (void);
		unsigned int opt;
			unsigned int stage;
				void  option (void);
					void secure (void);
						int old_code (unsigned int);
							unsigned char known_code[4] = "1111";
								void set_code ();
									//int check_code (unsigned char, int );
									
/**** the main function of the program********
***** it initializes the global variable that helps 
*****determine what part of the code we are on to enable the interupt cancel
************operation***********/
void main (void){
	P3 = 0x0C;
		opt = 0; // global variable that helps determine what stage of the program we are on
			stage = 1;
				EECON = 0x0B;
	while (1){
						delay (3000);
							IE = 0x85;
								IT0 = 0;
									IT1 =0; 
										opt = 0;
	
							secure(); // call to the secure function that performs the check
					}
		}

// the enter key interupt when P3.2 is pressed
		
	void enter (void) interrupt 0{
				if (stage == 1) {
									opt = 1;
														}	
															}
	//the cancel key interrupt when P3.3 is pressed
	void cancel (void) interrupt 2{
				if (stage == 1) {
							opt = 2;
														}
				else if (stage == 3){
		
		number = 7;
			
		}
	}
	
	
	
	// the  begining of the actual performance of the program
	
	void secure (void){
			display ("  WELCOME TO"," SECURITY  CODE");
					delay (100);
							stage = 1;
								opt =0;
					option ();  // function that displays the features and options of the program
		
		// conditional check to know weather the individual wants to enter
		// or wants to do a password change
							if (stage ==1 && opt ==1){
										stage = 2;
											old_code(1);  // a call to the function that accepts password because 
																		// the individual wants to enter
												stage =1;
																}
		
							if (stage ==1 && opt ==2){
										set_code();		// a call to the function that changes password because 
																		// the individual wants to change the password
											stage = 1;
												}
								delay (200);
		}
	
	
	  // function that displays the features and options of the program
	void  option (void){
		
			 while (opt == 0){
				 if (opt == 0)	display ("TO GO INSIDE"," PLS PRESS P3.2");
	delay (100);
			if (opt == 0)display ("TO CHANGE CODE"," PLS PRESS P3.3 ");
	delay (100);
			
		}
	
	}
		
			
	// function "check_code" that helps to compare the typed code and the stored code
	
		int check_code (unsigned char *coded ){
		int q;
		int correct ;
						
		for (q= 0; q<4; q++){
		if (known_code[q] == coded[q])
		{
		correct = 1;
					}
		else {
		correct = 0;
			break;
		}
		}
		if (correct == 1 ){
			correct = 1;
					return correct;
						}
		else    { 
			correct == 0;
		return correct;
		}
		}
		
				//this function processes the retrieval of typed code
			// the call to the function check code that does the comparison
		//also displays the corresponding result based on its comparison
		
		int old_code (unsigned int cORe){
				int pass;
					display ("  PLEASE ENTER ","   PASSWORD");
		delay (100);
			
	typed = keypad (4); //call for keypad entry
		for ( incr = 0; incr <4 ; incr++ ) 
{ 
	p[incr] = *(typed + incr); // store the retrieved value in the variable p
}
delay (300);
			pass =	check_code(p); //call to compare the code entered
				  // conditional checks to determine the outpu
				if (pass == 1 && cORe == 1){
					delay (20);
	display ("  CORRECT ","YOU MAY PROCEED");
		delay (1000);
					return pass;
				}
				else if (pass == 1 && cORe == 2){
									return pass;
				}
			
				else {
				display ("    WRONG","   PASSWORD");
		delay (2000);
					secure ();
				}

	}
		
	// this function processes the password reset option whne choosen
	



	
	void set_code (){
		
		unsigned char holder1[4] , holder2[4] ;
		
		int statu;
		
		int q, correct;

		stage = 3;
	delay (20);
		statu = old_code(2);

		if (statu == 1){
			display (" PLEASE ENTER"," NEW PASSWORD ");
			delay(100);
			typed = keypad (4);
			if (number == 7){
				stage =1;
 secure ();
}
				for ( incr = 0; incr <4 ; incr++ ) 
{ 
	holder1[incr] = *(typed + incr);

}
display ("PLEASE RE-ENTER"," NEW PASSORD");
typed = keypad (4);
if (number == 7){
	stage =1;
 secure ();
}
				for ( incr = 0; incr <4 ; incr++ ) 
{ 
	holder2[incr] = *(typed + incr);

}
delay (20);
for (q= 0; q<4; q++){
		if (holder1[q] == holder2[q])
		{
		correct = 1;
					}
		else {
		correct = 0;
			break;
		}
	}
if (correct == 1){
	int t;
	for (t= 0 ; t < 4; t++ ){
			known_code[t] = holder2[t];}
display ("PASSWORD CHANGE","   SUCCESSFUL");
	delay (20);
			stage = 1;
	secure();
}
else {
			display (" PASSWORD NOT","   COHERENT");
	delay (20);
	display ("PASSWORD CHANGE"," UNSUCCESSFUL");
	delay (20);
	secure();
}


}


}

	