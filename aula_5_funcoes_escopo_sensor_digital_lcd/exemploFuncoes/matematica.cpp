#include "matematica.h"

static int checaDivisor(int x);

int soma(int a, int b)
{
  int y = 0;
  y = a + b;
  return y;
}
// --------------------------------------
int subtrai(int a, int b)
{
  int y = 0;
  y = a - b;
  return y;
}
//---------------------------------------
float divide(int a, int b)
{
  float y = 0;

  if(checaDivisor(b) != 1)
  {
    return y = -999999;
  }

  return (float)a/b;
}
//---------------------------------------
static int checaDivisor(int b)
{
  return (b != 0);
}







