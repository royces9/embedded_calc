#include <Arduino.h>
#include "lcd.h"

char disp_0[] = {1, 1, 1, 1, 1, 1, 0, 0};
char disp_1[] = {0, 1, 1, 0, 0, 0, 0, 0};
char disp_2[] = {1, 1, 0, 1, 1, 0, 1, 0};
char disp_3[] = {1, 1, 1, 1, 0, 0, 1, 0};
char disp_4[] = {0, 1, 1, 0, 0, 1, 1, 0};
char disp_5[] = {1, 0, 1, 1, 0, 1, 1, 0};
char disp_6[] = {1, 0, 1, 1, 1, 1, 1, 0};
char disp_7[] = {1, 1, 1, 0, 0, 0, 0, 0};
char disp_8[] = {1, 1, 1, 1, 1, 1, 1, 0};
char disp_9[] = {1, 1, 1, 0, 0, 1, 1, 0};
char disp_a[] = {1, 1, 1, 0, 1, 1, 1, 0};
char disp_b[] = {0, 0, 1, 1, 1, 1, 1, 0};
char disp_c[] = {0, 0, 0, 1, 1, 0, 1, 0};
char disp_d[] = {0, 1, 1, 1, 1, 0, 1, 0};
char disp_e[] =  {1, 0, 0, 1, 1, 1, 1, 0};
char disp_dp[] = {0, 0, 0, 0, 0, 0, 0, 1};

char *ssd[] = {
	       disp_0,
	       disp_1,
	       disp_2,
	       disp_3,
	       disp_4,
	       disp_5,
	       disp_6,
	       disp_7,
	       disp_8,
	       disp_9,
	       disp_a,
	       disp_b,
	       disp_c,
	       disp_d,
	       disp_e,
	       disp_dp
};


void lcd(int a) {
	if(a > 15)
		a = 15;

	for(int i = 0; i < 8; ++i) {
		if(ssd[a][i])
			digitalWrite(PORT + i, HIGH);
		else
			digitalWrite(PORT + i, LOW);
	}
}


void turn_off(void) {
	for(int i = 0; i < 8; ++i) {
		digitalWrite(PORT + i, LOW);
	}
}
