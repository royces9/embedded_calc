#ifndef STACK
#define STACK

#include <stdint.h>


//macro for malloc failure
#define __MALLOC_CHECK(pointer, error) \
  if(pointer == NULL) {\
  error = -6; \
  return 0; \
  }


#define VARIABLE_COUNT 32

typedef float element;
typedef int8_t error_return;

typedef struct { //struct for operators, +, -, etc
  //order of operation, higher is higher priority
  uint8_t precedence;

  //number of arguments it takes, generally two or one
  uint8_t argNo;

  //corresponding enum, in operatorUtility.h
  uint16_t _enum;

} operatorStruct;


typedef struct { //struct for stack of numbers
  //stack array
  element stk[32];

  //index for the top index
  //-1 is empty
  int8_t top;

} numberStack;


typedef struct { //same as numberStack, except for operators
  //stack array
  operatorStruct stk[32];

  //index for the top index
  //-1 is empty
  int8_t top;

} operatorStack;


typedef struct { //variable storage
  //stores variable values
  element value[VARIABLE_COUNT];

  //stores variable names
  char name[VARIABLE_COUNT];
  
  //answer matrix
  element ans;

  //flag if an assignment occured
  int8_t assignFlag;

} vari;


void pushn(element inp, numberStack *st);
element popn(numberStack *st);

void pushch(operatorStruct inp, operatorStack *st);
operatorStruct popch(operatorStack *st);

operatorStruct initOperatorStruct(uint8_t argNo, uint8_t precedence, uint8_t _enum);

numberStack *newNumberStack(void);
operatorStack newOperatorStack(void);

vari newVari(void);
vari *copyVari(vari *var, error_return *error);

error_return setVariable(vari *var, element a, int *check);
void freeVari(vari var);

void freeNumberStack(numberStack *st);

#endif //STACK
