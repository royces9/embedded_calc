#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "functions.h"
#include "operator.h"
#include "sya.h"


//search in FUNCTION_LIST
int searchFunctionArray(char *buffer) {
  for(int i = 0; i < FUNCTION_COUNT; ++i) {
    if(!strcmp(FUNCTION_LIST[i], buffer)) {
      return i;
    }
  }
  return FUNCTION_COUNT;
}


//search in OPERATOR_COUNT
int searchOperatorArray(char *buffer) {
  for(int i = 0; i < OPERATOR_COUNT; ++i) {
    if(!strcmp(OPERATOR_LIST[i], buffer)) {
      return i;
    }
  }
  return OPERATOR_COUNT;
}


//executes either one argument function or two argument function
error_return execNum(numberStack *num, vari *var, operatorStruct ch) {
  error_return error = 0;

  element a = 0, b = 0;

  switch(ch.argNo) {
  case 1:
    a = popn(num);
    pushn(oneArg(a, ch.enumeration, &error), num);
    break;

  case 2:
    b = popn(num);
    a = popn(num);
    pushn(twoArg(a, b, ch.enumeration, &error), num);
    break;

  case 3:
    b = popn(num);
    a = popn(num);

    pushn(assign(a, b, var, &error), num);
    break;

  default:
    break;
  }
  return error;
}


error_return findFunction(char *buffer, numberStack *num, operatorStack *ch, vari *var, uint8_t *tok, uint8_t *start, char *input) {
  char **separatedString = NULL;
  int i = searchFunctionArray(buffer);
  error_return error = 0;

  switch(i) {

  case ePi:
    pushn(M_PI, num);
    *tok = 1;
    return 0;

  case eE:
    pushn(M_E, num);
    *tok = 1;
    return 0;

  case eAns:
    {
      pushn(var->ans, num);
      *tok = 1;
    }
    return 0;

  case eSin:
  case eCos:
  case eTan:
  case eLn:
  case eLog:
  case eSqrt:
  case eAsin:
  case eAcos:
  case eAtan:
  case eFloor:
  case eCeil:
  case eRound:
  case eFactorial:
  case eMin:
  case eMax:
  case eAvg:
    pushch(initOperatorStruct(FUNCTION_LIST[i], 1, 2, i), ch);
    *tok = 0;
    return 0;
/*
  case eDeri:
    separatedString = separateString(input, "()", ',', start, &error);
    pushn(deri(separatedString, var, &error), num);
    freeDoubleArray(separatedString);
    *tok = 0;
    return error;

  case eInte:
    separatedString = separateString(input, "()", ',', start, &error);
    pushn(inte(separatedString, var, &error), num);
    freeDoubleArray(separatedString);
    *tok = 0;
    return error;

  case eSolve:
    separatedString = separateString(input, "()", ',', start, &error);
    pushn(solve(separatedString, var, &error), num);
    freeDoubleArray(separatedString);
    *tok = 0;
    return error;

  case eRand:
    separatedString = separateString(input, "()", ',', start, &error);
    //pushn(randMatrix(separatedString, var, &error), num);
    freeDoubleArray(separatedString);
    *tok = 0;
    return error;
    */

  case FUNCTION_COUNT: //variables
    break;
    //return checkVariable(buffer, tok, input, start, var, num, ch);

  default:
    error = -5;
    break;

  }//end of switch

  return error;
}


error_return findOperator(char *buffer, numberStack *num, operatorStack *oper, vari *var, uint8_t *tok) {
  int i = searchOperatorArray(buffer);
  error_return error = 0;

  /*                                                                                                                  
  **Precedence values for operators: Reference wiki page of C/C++ operators
  **1                                                
  **2 f(x)-calls
  **3
  **4 ^ !
  **5
  **6 + -
  **7
  **8 < <= > >=
  **9 == !=
  **10
  **11 &&
  **12 ||
  **13
  **14
  **15 parens
  **16 =
*/

  switch(i) {

  case eSubtract:
    if(*tok == 1) {
      while((oper->stk[oper->top].precedence <= 6) && (oper->top > -1)) {
	error = execNum(num, var, popch(oper));
      }
      pushch(initOperatorStruct("+", 2, 6, eAdd), oper);
    }

    *tok = 0;
    pushch(initOperatorStruct("*", 2, 5, eMultiply), oper);
    pushn(-1, num);
    break;

  case eExponent:
    *tok = 0;
    pushch(initOperatorStruct(".^", 2, 4, eExponent), oper);
    break;

  case eLeftParen:
    *tok = 0;
    pushch(initOperatorStruct("(", 0, 15, eLeftParen), oper);
    break;

  case eRightParen:
    do {
      error = execNum(num, var, popch(oper));
    } while(strcmp(oper->stk[oper->top].operator, "(") && (oper->top > -1));

    *tok = 1;
    popch(oper);
    break;


  case eAssign:
    *tok = 0;
    pushch(initOperatorStruct("=", 3, 16, eAssign), oper);
    break;

  case eAdd:
  case eMultiply:
  case eDivide:
  case eLess:
  case eGreater:
  case eLessEqual:
  case eGreaterEqual:
  case eNotEqual:
  case eEqual:
  case eAnd:
  case eOr:

    while((oper->top > -1) && (oper->stk[oper->top].precedence <= operatorPrecedence[i])) {
      error = execNum(num, var, popch(oper));
    }

    *tok = 0;
    pushch(initOperatorStruct(buffer, 2, operatorPrecedence[i], i), oper);
    break;

  default:
    return -7;
  }

  return 0;
}


int countDelimiter(char *input){
  int out = 0;
  int bracketCount[2] = {0, 0};

  for(int i = 0; input[i]; ++i){
    switch(input[i]){
    case '(':
      ++bracketCount[0];
      break;

    case ')':
      --bracketCount[0];
      break;

    case '[':
      ++bracketCount[1];
      break;

    case ']':
      --bracketCount[1];
      break;

    case ',':
    case ';':
      if(!(bracketCount[0] || bracketCount[1])){
	++out;
      }
      break;

    default: break;
    }
  }

  return out;
}

/*
int varcheck(vari *list, char input[]) {
  if(list->count < 0) {
    return -1;
  }

  for(int i = 0; i<=list->count; ++i) {
    if(!strcmp(input, list->name[i])) {
      return i;
    }
  }

  return -2;
}
*/


void freeDoubleArray(char **input) {
  int i = 0;
  for(i = 0; input[i]; ++i) {
    free(input[i]);
  }
  free(input[i]);
  free(input);
}


void helpPrint(void) {
  printf("quit - quit program\n");
  printf("list - list variables\n");
  printf("clear - clear variables\n\n");

  printf("derivative(f(x), x, c, delta)\n   f(x) - function\n   x - variable used in function\n   c - point of the tangent line\n   delta - the difference used (finite difference)\n\n");

  printf("integral(f(x), x, a, b, n)\n   f(x) - function\n   x - variable used in function\n   a - starting point\nb - ending point\n   n - number of partitions (composite Simpson's rule, odd n is equivalent to n-1)\n\n");

  printf("solve(f(x), x, guess, delta)\n   f(x) - function\n   x - variable used in function\n   guess - initial guess (Newton's Method)\n   delta - largest difference allowed between x_n+1 and x_n\n\n");

  printf("run(file)\n   file - path to a text file\n   This function parses each line of the file as if it were entered into the console directly, with the exception of \"while\", \"if/else\" and \"end\".\n    \"while\" - loops until the statement inside the \"while\"'s conditional is false. The inside is executed as if it were entered into the console directly. There may be floating point round off errors.\n   \"if/else\" - Executes the block of lines inside the \"if\"'s conditional if the statement is true, Otherwise it will execute the \"else\" block.\n   '#' at the beginning of\
 a line comments out a line\n   ';' at the end of a line suppresses output\n\n");
}
