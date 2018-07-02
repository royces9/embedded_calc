#ifndef OPERATOR
#define OPERATOR

#include "stack.h"
#include "operatorUtility.h"

int searchFunctionArray(char *buffer);
int searchOperatorArray(char *buffer);
error_return execNum(numberStack *num, vari *var, operatorStruct ch);

error_return findFunction(char *buffer, numberStack *num, operatorStack *ch, vari *var, uint8_t *tok, uint8_t *start, char *input);
error_return findOperator(char *buffer, numberStack *num, operatorStack *ch, vari *var, uint8_t *tok);

void freeDoubleArray(char **input);
void helpPrint(void);

#endif //OPERATOR
