#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "sya.h"

int main(void) {
  char input[128];
  error_return error = 0;
  
  //initialize variable struct
  vari var = newVari();

  //main loop
  while(error <= 0) {

    //for the time being use this, probably want to switch to something else later
    //user input
    scanf("%s\n", &input);

    if(*input == 0) { //if the user enters an empty line, go to top of loop
      continue;
    } else{ //parses string and does all the calculations
      error = sya(input, &var);
    }

    if(error == 0) {
      printf("\n%lf\n\n", var.ans);

    } else{ //if the error is less than -1, prints an error code
      errorReport(error);
    }
  }

  freeVari(var);
  return 0;
}
