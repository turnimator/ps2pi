/*
 * Sample program for PiPS2 library.
 * Compile: g++ sample.cpp PiPS2.cpp -o sample -lwiringPi
 *
 * Sets up the PS2 remote for analog mode and to return all pressure values.
 * Reads controller every 10ms and prints the buttons that are pressed to the console.
 * BTN_START uses the functionality to detect a button push or release. 
 * Holding R2 will print the pressure values of the right analog stick to console.
 * All other buttons just cause a message to be printed after every read if they are being pressed.
 *
 * You can just implement the same functionality from the Start button or from the R2 functionality 
 * for any keys.
 *
 */

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "PiPS2.h"

#define READDELAYMS 10

void printPS2data(PIPS2 * ps)
{
	static bool busy=false;
	if (busy){
		return;
	}
	if (!ps->isValid()){
		return;
	}
	busy = true;
	printf("%02x %02x %02x  ", ps->PS2data[0],ps->PS2data[1],ps->PS2data[2]);
	for(int i = 0; i < 8; i++){
		if (ps->PS2data[3]&(1<<i)){
			printf(" ");
		}
		else {
			printf("%d",i);
		}
	}
	for(int i = 0; i < 8; i++){
		if (ps->PS2data[4]&(1<<i)){
			printf(" ");
		}
		else {
			printf("X");
		}
	}
	for (int i = 5; i < 9; i++){
		printf("%2x ",ps->PS2data[i]);
	}
	busy = false;
}

int main(int argc, char **argv)
{
    unsigned char cmd_string[21] = { 0x01, 0x42, 0, 0, 0, 0, 0, 0, 0 };

    printf("Atles PS2 Controller\n");

    if (wiringPiSetupPhys() == -1) {
	fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
	return 1;
    }
    // //////////// PiPS2 stuff ////////////////////////////
    // Create a PIPS2 object
    PIPS2 pips2;
    int nextRead = READDELAYMS;
    pips2.begin(11, 3, 5, 13);

    int returnVal = pips2.reInitializeController(ANALOGMODE);
    delay(50);
    printf("Control mode = %2x\n", pips2.PS2data[1]);

    while (1) {
	    pips2.readPS2();    
		printf("  %d %d %d %d          ", pips2.getLeftX(), pips2.getLeftY(), pips2.getRighX(), pips2.getRighY());
		printf("\r");
	    if (pips2.isXPressed()) {
			printf("\n");
			printPS2data(&pips2);
			printf("X\n"); 
		}
	    if (pips2.isCirclePressed()) {
			printf("\n");
			printPS2data(&pips2);
			printf("O\n"); 
		}
	    if (pips2.isSquarePressed()) {
			printf("\n");
			printPS2data(&pips2);
			printf("[]\n"); 
		}
	    if (pips2.isTrianglePressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("/\\\n"); 
		}
		if (pips2.isSelectPressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("Select\n");
		}
		if (pips2.isLeftJoyPressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("Left Joy\n");
		}
		if (pips2.isRightJoyPressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("Right Joy\n");
		}
		if (pips2.isL1Pressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("L1\n");
		}
		if (pips2.isL2Pressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("L2\n");
		}
		if (pips2.isPadDownPressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("Pad Down\n");
		}
		if (pips2.isPadLeftPressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("Pad Left\n");
		}
		if (pips2.isPadRightPressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("Pad Right\n");
		}
		if (pips2.isPadUpPressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("Pad Up\n");
		}
		if (pips2.isR1Pressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("R1\n");
		}
		if (pips2.isR2Pressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("R2\n");
		}
		if (pips2.isStartPressed()){
			printf("\n");
			printPS2data(&pips2);
			printf("Start\n");
		}






    }

    return 0;
}
