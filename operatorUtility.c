#include <stdint.h>

#include "operatorUtility.h"

const char FUNCTION_LIST[FUNCTION_COUNT][16] = {
  "pi",
  "e",
  "ans",

  "sin(",
  "cos(",
  "tan(",
  "ln(",
  "log(",

  "sqrt(",

  "asin(",
  "acos(",
  "atan(",

  "floor(",
  "ceil(",
  "round(",
  "min(",
  "max(",
  "avg(",

  "factorial(",
};


const char OPERATOR_LIST[OPERATOR_COUNT][4] = {
  "+",
  "-",
  "*",
  "/",

  "^",
  "=",
  "(",
  ")",

  "<",
  ">",
  "<=",
  ">=",

  "!=",
  "==",

  "&&",
  "||",
  "~",
};


const uint8_t operatorPrecedence[OPERATOR_COUNT] = {
  6,
  6,
  5,
  5,

  4,
  4,
  16,
  15,
  
  15,
  8,
  8,
  8,

  8,
  9,

  9,
  11,
  12,
}; //~is not implemented at the moment
