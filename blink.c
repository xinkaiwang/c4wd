#include <wiringPi.h>
int main (void)
{
  wiringPiSetup () ;
  pinMode (6, OUTPUT) ;
  for (;;)
  {
    digitalWrite (6, HIGH) ; delay (500) ;
    digitalWrite (6,  LOW) ; delay (500) ;
  }
  return 0 ;
}