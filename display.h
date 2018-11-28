
/***** 8051 LCD interfacing program*******************
************Written By Verissimo Michael     ************
******* The program recieves a data to be displayed and ****
*********** sends it to the LCD *******/

//import needed header file
#include <REG51.H>
#include <DELAY.H>
#include <string.H>
#include <stdio.H>
// assign the LCD data pins to port 2
#define Lcd  P2
//assigning the LCD control pins to the microcontroller pins

sbit RS = P2^0;
	//sbit RW = P2^1;
			sbit EN = P2^1;

void lcdDelay (int );


//  the "writ_lcd" function does the transmission of either data or command to the LCD
// it recieves two values from the calling fuction
// the first value is the data, while the other value is to determine weather it is a data or command write
void writ_lcd (unsigned char dat, unsigned int com){
					
	// the hardware connection made is for the data to be sent in 4 bits rather than 8bits
	// hence  the byte data is splitted into two and the MSB is sent firts followed by the LSB
	// the reason for the right shift is due to the pin positions of the hardware connection  
	
	
	//sending the MSB
	Lcd = (dat & 0xF0)>>2;
	RS = com;
	EN= 1;
	lcdDelay(1000);
	EN = 0;
	delay(1);
	
	
	//sending the LSB
	Lcd = ((dat << 4) & 0xF0)>>2;
	RS = com;
	EN= 1;
	lcdDelay(1000);
	EN = 0;
	delay(10);
	
	
	
}

// the function "initial_lcd" helps to initiallize the lcd by passing some command data into the LCD
// the function clears the lcd screen and places the cursor at the begining of the first line
void initial_lcd(void){
				Lcd = 0x00;
writ_lcd(0x02, 0);
writ_lcd(0x28, 0);
writ_lcd(0x0E,0);
writ_lcd(0x01,0);
writ_lcd(0x80, 0);
	writ_lcd (0x0C, 0);
	
}

// the function "string_to_lcd" helps to convert an array of characters i.e a string into single characters each
// it passes each character singely into the "writ_lcd" function, as the function can only process one byte at a time
void string_to_lcd ( unsigned char *s){
	
	unsigned char i, l;
	l = strlen (s);  // lenght of the array to be used for the FOR loop range
	
	// for loop to split the string into single character
	for ( i=0; i< l ; i++){
		
		writ_lcd ( *s, 1); //passing a data byte to the writ_lcd function 
		delay (50);
		s++;
	}
}


// a delay function for the lcd
void lcdDelay (unsigned int cnt){

				unsigned int i ;
				for (i=0; i<cnt;  i++);
}

// this is the function that is called from outside the program class
// it recieves the data for line 1 and line 2
void display (unsigned char *T1, unsigned char *T2)
	{

	delay (20);
	initial_lcd ();    //initialize lcd#
	writ_lcd (0x01, 0); //clear display screen
	writ_lcd (0x80, 0); //force cursor to begining of first line 
	string_to_lcd (T1);  // pass the line 1 string of data for display
		delay (50);
	writ_lcd(0xc0, 0);	//force cursor to begining of second line 
	string_to_lcd (T2);// pass the line 2 string of data for display
	delay (50);
	
}
	
// this function is called by the keypad class whenever a keypad is pressed
// the function displays the corresponding value of the keypad pressed
void keypad_display (unsigned char *key, unsigned int num){
						unsigned char temp5;
	
	temp5 = *key;
	if (num ==1){
					writ_lcd (0x01, 0);
	writ_lcd (0x80, 0);
		string_to_lcd (key);
		delay (300);
	}
			else if (num > 1  && num <5){
					writ_lcd (temp5,1);
				delay (300);
			}


}

