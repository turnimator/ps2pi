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
#include "ps2pi.h"

#define READDELAYMS 10

int main(int argc, char **argv)
{
    unsigned char cmd_string[21] = { 0x01, 0x42, 0, 0, 0, 0, 0, 0, 0 };

    printf("Atles PS2 Controller\n");

    if (wiringPiSetupPhys() == -1) {
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		return 1;
    }
    
    // Create a PIPS2 object
    ps2pi_t pips2;
    int nextRead = READDELAYMS;
    pips2.begin(11, 3, 5, 13);

    int returnVal = pips2.reInitializeController(ANALOGMODE);
    delay(50);
    pips2.printData();

    while (1) {
	    pips2.readPS2();    
		printf("  %d %d %d %d          ", pips2.getLeftX(), pips2.getLeftY(), pips2.getRighX(), pips2.getRighY());
		printf("\r");
	    if (pips2.isXPressed()) {
			printf("\n");
			pips2.printData();
			printf("X\n"); 
		}
	    if (pips2.isCirclePressed()) {
			printf("\n");
			pips2.printData();
			printf("O\n"); 
		}
	    if (pips2.isSquarePressed()) {
			printf("\n");
			pips2.printData();
			printf("[]\n"); 
		}
	    if (pips2.isTrianglePressed()){
			printf("\n");
			pips2.printData();
			printf("/\\\n"); 
		}
		if (pips2.isSelectPressed()){
			printf("\n");
			pips2.printData();
			printf("Select\n");
		}
		if (pips2.isLeftJoyPressed()){
			printf("\n");
			pips2.printData();
			printf("Left Joy\n");
		}
		if (pips2.isRightJoyPressed()){
			printf("\n");
			pips2.printData();
			printf("Right Joy\n");
		}
		if (pips2.isL1Pressed()){
			printf("\n");
			pips2.printData();
			printf("L1\n");
		}
		if (pips2.isL2Pressed()){
			printf("\n");
			pips2.printData();
			printf("L2\n");
		}
		if (pips2.isPadDownPressed()){
			printf("\n");
			pips2.printData();
			printf("Pad Down\n");
		}
		if (pips2.isPadLeftPressed()){
			printf("\n");
			pips2.printData();
			printf("Pad Left\n");
		}
		if (pips2.isPadRightPressed()){
			printf("\n");
			pips2.printData();
			printf("Pad Right\n");
		}
		if (pips2.isPadUpPressed()){
			printf("\n");
			pips2.printData();
			printf("Pad Up\n");
		}
		if (pips2.isR1Pressed()){
			printf("\n");
			pips2.printData();
			printf("R1\n");
		}
		if (pips2.isR2Pressed()){
			printf("\n");
			pips2.printData();
			printf("R2\n");
		}
		if (pips2.isStartPressed()){
			printf("\n");
			pips2.printData();
			printf("Start\n");
		}
    }

    return 0;
}
