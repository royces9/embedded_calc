#include <Arduino.h>

#include "keypad.h"


char keypad[12] = {'1', '2', '3',
		   '4', '5', '6',
		   '7', '8', '9',
		   '+', '0', 0};


char get_key(void) {
	int col = -1;

	do {
		for(int i = 0; (col < 0) && i < 3; ++i) {
			if(digitalRead(i + 26) == LOW)
				col = i;
		}
	} while(col < 0);

	pinMode(col, OUTPUT);
	digitalWrite(col, LOW);


	int row = -1;
	for(int i = 0; (row < 0) && i < 4; ++i) {
		digitalWrite(i + 22, HIGH);

		if(digitalRead(col + 26) == HIGH)
			row = i;

		digitalWrite(i + 22, LOW);
	}

	pinMode(col, INPUT_PULLUP);

	int ind = (row) * 3 + (col);

	return keypad[ind];
}

