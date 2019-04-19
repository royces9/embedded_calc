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
		pushn(oneArg(a, ch._enum, &error), num);
		break;

	case 2:
		b = popn(num);
		a = popn(num);
		pushn(twoArg(a, b, ch._enum, &error), num);
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
		pushch(initOperatorStruct(1, 2, i), ch);
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
			while((oper->top > -1) && (oper->stk[oper->top].precedence <= 6)) {
				error = execNum(num, var, popch(oper));
			}
			pushch(initOperatorStruct(2, 6, eAdd), oper);
		}

		*tok = 0;
		pushch(initOperatorStruct(2, 5, eMultiply), oper);
		pushn(-1, num);
		break;

	case eExponent:
		*tok = 0;
		pushch(initOperatorStruct(2, 4, eExponent), oper);
		break;

	case eLeftParen:
		*tok = 0;
		pushch(initOperatorStruct(0, 15, eLeftParen), oper);
		break;

	case eRightParen:
		do {
			error = execNum(num, var, popch(oper));
		} while((oper->top > -1) && (oper->stk[oper->top]._enum != eLeftParen) );


		*tok = 1;
		popch(oper);
		break;


	case eAssign:
		*tok = 0;
		pushch(initOperatorStruct(3, 16, eAssign), oper);
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
		pushch(initOperatorStruct(2, operatorPrecedence[i], i), oper);
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


void freeDoubleArray(char **input) {
	int i = 0;
	for(i = 0; input[i]; ++i)
		free(input[i]);

	free(input[i]);
	free(input);
}

