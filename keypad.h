
/***** 8051 keypad interfacing program*******************
************Written By Verissimo Michael     ************
******* The program recieves a keypress and returns the value to an lcd display****
*********** and a function that calls it *******/
//import needed header file
#include <REG51.H>

// define all the pins needed for the keypad control

//the row pins determine which row the pin pressed belongs to
sbit row1 = P0^0;
	sbit row2 = P0^1;
		sbit row3 = P0^2;
			sbit row4 = P0^3;
//the column pins determine which column the pin pressed belongs to

sbit col1 = P0^4;
	sbit col2 = P0^5;
		sbit col3 = P0^6;
			sbit col4 = P0^7;
// define pins to signal that a paricular row is been worked on

unsigned int number;  // variable to determine the number of time keys have been pressed
 unsigned int *typed; // recieves the address of typed keys values
		unsigned int incr;
			unsigned char p[4];
				unsigned char ret;
		
		// a keypad delay function
void padDelay (unsigned int cnt){

				unsigned int j;
	unsigned int l;
		for (l= 0; l< cnt; l++){
				for (j=0; j<100; j++);
		}
	}



// a function to actually read a keypree
		// by first applying a low to each row in sequence
			// it then checks the corresponding column with a high
					// then it rechecks if the column is still high after a 100 paddelay
void readPad (void){

		col1= 1;
			col2= 1;
				col3= 1;
					col4= 1;
							row1 =0;    // row one is made low here
													// the characters '1', '4', '7', and ' *' belongs to row 1
									row2 = 1;
										row3 = 1;
												row4 = 1;
	
	 // condition to check what column is LOW in other to give the corresponding character
	if (col1 == 0 ) {
		padDelay(100);
					while (col1 == 0);
							number++;
					ret = '1';}  // shows column 1 is low and returns the character '1'
	
		if (col2 == 0 ) {
			padDelay(100);
						while (col2 == 0);
									number++;
						ret =  '4';}// shows column 2 is low and returns the character '4'
	
				if (col3 == 0 ) {
						padDelay(100);
									while (col3 == 0);
												number++;
									ret = '7';}  // shows column 3 is low and returns the character '7'
	
									  if (col4 == 0 ) {
											padDelay(100);
													while (col4 == 0);
																number++;
													ret = '*';}	 // shows column 4 is low and returns the character '*'
	
			// row2 is made low here
			// the characters '2', '5', '8', and ' 0' belongs to row2
								row1 =1;
							row2 = 0;
						row3 = 1;
					row4 = 1;
				// condition to check what column is LOW in other to give the corresponding character
		if (col1 == 0 ) {
				padDelay(100);
						while (col1 == 0);
									number++;
						ret = '2';} // shows column 1 is low and returns the character '2'
	
			if (col2 == 0 ) {
					padDelay(100);
								while (col2 == 0);
										number++;
								ret = '5';}// shows column 2 is low and returns the character '5'
	
					if (col3 == 0 ) {
							padDelay(100);
									while (col3 == 0);
											number++;
									ret = '8';} // shows column 3 is low and returns the character '8'
							if (col4 == 0 ) {
									padDelay(100);
												while (col4 == 0);
														number++;
												ret = '0';}  // shows column 4 is low and returns the character '0'
	
	
								row1 =1;
							row2 = 1;
						row3 = 0;	// row3 is made low here
											// the characters '3', '6', '9', and '#' belongs to row2
					row4 = 1;
	
			// condition to check what column is LOW in other to give the corresponding character
	if (col1 == 0 ) {
			padDelay(100);
					while (col1 == 0);
								number++;
						ret = '3';} //shows column 1 is low and returns the character '3'
	
		if (col2 == 0 ) {
				padDelay(100);
							while (col2 == 0);
										number++;
							ret = '6';}	//shows column 2 is low and returns the character '5'
	
			if (col3 == 0 ) {
					padDelay(100);
								while (col3 == 0);
										number++;
					ret = '9';} //shows column 3 is low and returns the character '9'
	
				if (col4 == 0 ) {
							padDelay(100);
										while (col4 == 0);
												number++;
										ret = '#';} //shows column 4 is low and returns the character '#'
	
									row1 =1;
								row2 = 1;
							row3 = 1;
						row4 = 0;		// row3 is made low here
												// the characters '3', '6', '9', and '#' belongs to row2
	
					// condition to check what column is LOW in other to give the corresponding character
	if (col1 == 0 ) {
			padDelay(100);
						while (col1 == 0);
								number++;
						ret = 'A';}		//shows column 1 is low and returns the character 'A'
	
		if (col2 == 0 ) {
				padDelay(100);
							while (col2 == 0);
									number++;
							ret = 'B';}	 //shows column 2 is low and returns the character 'B'
	
			if (col3 == 0 ) {
					padDelay(100);
								while (col3 == 0);
										number++;
								ret = 'C';}  //shows column 3 is low and returns the character 'C'
	
					if (col4 == 0 ) {
							padDelay(100);
									while (col4 == 0);
											number++;
									ret = 'D';}	 //shows column 4 is low and returns the character 'D'
	
	
}


// the function "keypad" processes the number of keys needed to be pressed and displayed 
		// it accepts the val which is the number of values to be pressed
				// returns the pointer to an array which holds all the value of keys pressed

int *keypad (unsigned int val) {
	unsigned char c,p[1];  		// p variable holds the keypressed data sent to the display
			static int ret_word[4]; 		// variable that holds the returned key press
					unsigned int ses, key_num, checker;
							checker = val; 			// variable to check number of keys pressed
						number = 0;
					key_num=0;
			initial_lcd();			 // LCD display screen is being initiallized and cleared
		ses = 0;
	delay (100);
		ret = 'h';
			while (1){ 					//loops keep calling the "readpad" function until all the keys needed to be read are read
	 
						readPad();
							c= ret;
												//conditional check to confirm a key was pressed
						if (c == 'h'){
												//no key was pressed so it does nothing
														}
						else if (number != 0) {
													// key was pressed so it does the following
										p[0] = c;
											keypad_display(p, number);    // calling function to display the corresponding key pressed
													delay (100);
														ret_word[number -1] = c; // assigns values to the ret_word array variables
			
			// conditional check to know the number of keys already pressed
							
						if (number >= checker) {
									c= 'h';
										ret = 'h';
											break;
																			}
						ret = 'h';
		}
		
		}
		return ret_word;
	}
			




