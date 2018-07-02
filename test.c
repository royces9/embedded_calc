#include <stdio.h>


int main(void){
  int a = 0;
  int b = 0;

  b += !!(a);
  a++;

  printf("%d\n", b);

  return 0;
}
