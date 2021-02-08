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
char left_joy_string[12];

char right_joy_string[12];

void left_joy_callback(int x, int y, void *user_data){
	char *p= (char*) user_data;
	printf("Left joy ");
	sprintf(p, "x:%d  y:%d ", x, y);
}

void right_joy_callback(int x, int y, void *user_data){
	char *p= (char*)user_data;
	sprintf(p, "x:%d  y:%d ", x, y);
}

void xaction(int pressure, void* user_data)
{
	printf("X pressed\n");
}

void startaction(int pressure, void* user_data)
{
		printf("START pressed\n");
}

void squareaction(int pressure, void* user_data)
{
		printf("SQUARE pressed\n");
}

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
	
	pips2.begin(11, 3, 5, 13);

	int returnVal = pips2.reInitializeController(ANALOGMODE);
	delay(50);
	pips2.printData();

	pips2.setXAction(xaction, cmd_string);
	pips2.setStartAction(startaction, NULL);
	pips2.setSquareAction(squareaction, NULL);
	pips2.setLeftJoyCallback(left_joy_callback, left_joy_string);
	
	while (1) {
		pips2.readPS2();
		pips2.dispatch();
		printf("\r%s ", left_joy_string);
	}
}
