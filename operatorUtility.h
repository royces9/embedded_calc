#ifndef UTILITY
#define UTILITY

//file including all the utility
//enums/constants/etc

#define FUNCTION_COUNT 19
#define OPERATOR_COUNT 18

extern const char OPERATOR_LIST[OPERATOR_COUNT][4];
extern const char FUNCTION_LIST[FUNCTION_COUNT][16];
extern const uint8_t operatorPrecedence[OPERATOR_COUNT];

enum functionEnums {
  ePi,
  eE,
  eAns,

  eSin,
  eCos,
  eTan,
  eLn,
  eLog,

  eSqrt,

  eAsin,
  eAcos,
  eAtan,

  eFloor,
  eCeil,
  eRound,
  eMin,
  eMax,
  eAvg,

  eFactorial,
};


enum operatorEnum {
  eAdd,
  eSubtract,
  eMultiply,
  eDivide,

  eExponent,
  eAssign,
  eLeftParen,
  eRightParen,

  eLess,
  eGreater,
  eLessEqual,
  eGreaterEqual,

  eNotEqual,
  eEqual,

  eAnd,
  eOr,
  eNot,
};


#endif //UTILITY
