#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"
#include "keypad.h"
#include "stack.h"
#include "sya.h"


char input[128];
error_return error = 0;
vari var;


void setup() {
	var = newVari();

	//rows
	for(int i = 22; i < 26; ++i) {
		pinMode(i, OUTPUT);
	}

	pinMode(41, OUTPUT);
	digitalWrite(41, LOW);

	//columns
	for(int i = 26; i < 29; ++i) {
		pinMode(i, INPUT_PULLUP);
	}


	for(int i = 7; i < 14; ++i) {
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
	}
}

void loop() {
	int count = 0;

	for(;(input[count] = get_key()); ++count)
		delay(500);

	//turn_off();
	//lcd(count);

	if(*input) {
		turn_off();
		if( !(error = sya(&input[0], &var))) {
			printf("\n%lf\n\n", var.ans);
			if((var.ans) < 15)
				lcd((int)(var.ans));

		} else { //if the error is less than -1, prints an error code
			digitalWrite(41, HIGH);
			errorReport(error);
			lcd(15);
			delay(500);
			digitalWrite(41, LOW);
		}
	}
	for(int i = 0;i < 128; ++i)
		count[i] = 0;
}
