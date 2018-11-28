#include<reg51.h>
#include<stdio.h>
#include<intrins.h>
#include <display.h> 
#include <string.h>
#define ACK 1
#define NO_ACK 0

unsigned char i;
int lav;
unsigned char EData[8];
unsigned char PData[8];
unsigned char oro[8] = "0000";
unsigned char Data;
void InitSerial(void);
void DelayMs(unsigned int);
void WriteI2C(unsigned char);
void Start(void);
void Stop(void);
void ReadBYTE(unsigned long);
void WriteBYTE(unsigned long);
unsigned char ReadI2C(bit);
unsigned long device  ;
sbit SCL = P1^0; // connect to SCL pin (Clock)
sbit SDA = P1^1; // connect to SDA pin (Data)

//—————————————
// Main program
//—————————————

void myeprom_write (unsigned long dev_addr, unsigned long mydev_add, unsigned char stored[])
{
	 
	char p;
	int i =0;
	int g;
	unsigned long dat_address = mydev_add;
	unsigned char say[16];
	lav = strlen(stored);
	for (g= 0; g <lav; g++){
					say[g] = stored[g];
	}
 device = dev_addr;
	InitSerial(); // Initialize serial port
putchar(0x0C); // clear hyper terminal
DelayMs(5);
	WriteBYTE(dat_address);
while (i<lav){
	
			p = say[i];
		WriteI2C(p);
	
		i++;
	}
	Stop();
DelayMs(10);
}

char * myeprom_read (unsigned long dev_addr, unsigned long mydev_add, int dat_num)
{
	unsigned char said[16];
	int lav = dat_num;
	char p;
	int i =0;
	int g;
	unsigned long dat_address = mydev_add;
	
	
 device = dev_addr;
	InitSerial(); // Initialize serial port
putchar(0x0C); // clear hyper terminal
DelayMs(5);
ReadBYTE(dat_address);
	while (i<lav){
		
	EData[i] =  (char)ReadI2C(NO_ACK);
		i++;
	}
	Stop();
DelayMs(10);
	for (g= 0; g <lav; g++){
					said[g] = EData[g];
	}
	
	return said;
}

/*
void main(void)
{
	
	int incr;
	char p[8];
	int i =0;
	char *todisp;
	lav = strlen(oro);
	//int lav = strlen(oro);
	myeprom_write (0xA0, 0x0080, oro);
	
	
todisp = myeprom_read (0xA0, 0x0080, lav);
		for ( incr = 0; incr <lav ; incr++ ) 
{ 
	p[incr] = *(todisp + incr); // store the retrieved value in the variable p
}


	i=0;


display (p , "stored");
	
	


while(1);
}
*/
//—————————————
// Initialize serial port
//—————————————
void InitSerial(void)
{
SCON = 0x52; // setup serial port control
TMOD = 0x20; // hardware (9600 BAUD @11.0592MHZ)
TH1 = 0xFD; // TH1
TR1 = 1; // Timer 1 on
}

//——————————-
// start I2C
//——————————-
void Start(void)
{
SDA = 1;
SCL = 1;
_nop_();_nop_();
SDA = 0;
_nop_();_nop_();
SCL = 0;
_nop_();_nop_();
}

//——————————-
// stop I2C
//——————————-
void Stop(void)
{
SDA = 0;
_nop_();_nop_();
SCL = 1;
_nop_();_nop_();
SDA = 1;
}

//——————————-
// Write I2C
//——————————-
void WriteI2C(unsigned char Data)
{

for (i=0;i<8;i++)
{
SDA = (Data & 0x80) ? 1:0;
SCL=1;SCL=0;
Data<<=1;
}

SCL = 1;
_nop_();_nop_();
SCL = 0;

}

//——————————-
// Read I2C
//——————————-
unsigned char ReadI2C(bit ACK_Bit)
{

Start();
WriteI2C(0xA1);

SDA = 1;
for (i=0;i<8;i++)
{
SCL = 1;
Data<<= 1;
Data = (Data | SDA);
SCL = 0;
_nop_();
}

if (ACK_Bit == 1)
SDA = 0; // Send ACK
else
SDA = 1; // Send NO ACK

_nop_();_nop_();
SCL = 1;
_nop_();_nop_();
SCL = 0;
Stop();
return Data;
}

//——————————-
// Read 1 byte form I2C
//——————————-
void ReadBYTE(unsigned long Addr)
{
Start();
WriteI2C(device);
WriteI2C((unsigned char)(Addr>>8)&0xFF);
WriteI2C((unsigned char)Addr&0xFF);
}

//——————————-
// Write 1 byte to I2C
//——————————-
void WriteBYTE(unsigned long Addr)
{
Start();
WriteI2C(device);
WriteI2C((unsigned char)(Addr>>8)&0xFF); // send address high
WriteI2C((unsigned char)Addr&0xFF); // send address low
}

//—————————————
// Delay mS function
//—————————————
void DelayMs(unsigned int count)
{ // mSec Delay 11.0592 Mhz
unsigned int i; // Keil v7.5a
while(count)
{
i = 115;
while(i>0) i--;
count--;
}
}