#include <Arduino.h>

#include "keypad.h"

#ifndef ROW_START
#endif

#ifndef COL_START
#endif

#ifndef ROW_COUNT
#endif

#ifndef COL_COUNT
#endif

char keypad[12] = {'1', '2', '3',
		   '4', '5', '6',
		   '7', '8', '9',
		   '+', '0', 0};



char get_key(void) {
	int col = -1;

	do {
		for(int i = 0; (col < 0) && i < COL_COUNT; ++i) {
			if(digitalRead(i + COL_START) == LOW)
				col = i;
		}
	} while(col < 0);


	int row = -1;
	for(int i = 0; (row < 0) && i < ROW_COUNT; ++i) {
		digitalWrite(i + ROW_START, HIGH);

		if(digitalRead(col + COL_START) == HIGH)
			row = i;

		digitalWrite(i + ROW_START, LOW);
	}

	int ind = (row) * 3 + (col);

	return keypad[ind];
}

