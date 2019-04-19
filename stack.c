#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

void pushn(element inp, numberStack *st) {
  st->stk[++st->top] = inp;
}


element popn(numberStack *st) { //pop a matrix from the stack
  element out = 0;

  if(st->top > -1){
    out = st->stk[st->top--];
  }

  return out;
}


//characters
void pushch(operatorStruct inp, operatorStack *st) {
    st->stk[++st->top] = inp;
}


operatorStruct popch(operatorStack *st) {
  operatorStruct out;

  if(st->top > -1){
    out = st->stk[st->top--];

  } else {
    out.argNo = 0;
  }

  return out;
}


//initialize operatorStruct
operatorStruct initOperatorStruct(uint8_t argNo, uint8_t precedence, uint8_t _enum){
  operatorStruct out;

  out.precedence = precedence;
  out.argNo = argNo;
  out._enum = _enum;

  return out;
}


numberStack *newNumberStack(void) { //make new number stack
  numberStack *out = calloc(1, sizeof(*out));
  out->top = -1;
  return out;
}


operatorStack newOperatorStack(void) { //make new operator stack
  operatorStack out;

  out.top = -1;
  memset(out.stk, '\0', sizeof(out.stk));

  return out;
}


vari newVari(void) {
  vari var;
  var.ans = 0;

  return var;
}


vari *copyVari(vari *var, error_return *error){
  vari *out = malloc(sizeof(*out));

  out->ans = 0;

  out->assignFlag = var->assignFlag;

  for(int i = 0; i < VARIABLE_COUNT; ++i){
    out->value[i] = var->value[i];
  }

  return out;
}


error_return setVariable(vari *var, element a, int *check){
  //check is from the output of varcheck

  int index = 0;
  error_return error = 0;

  *check = index;

  var->value[index] = a;

  return error;
}


void freeVari(vari var){
  //free(var);
}


void freeNumberStack(numberStack *st){
  free(st);
}
