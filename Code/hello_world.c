/* hello_world.c */

/* Define IO Pins */
#define DIG0 PB0
#define DIG1 PB1
#define DIG2 PB2
#define DIG3 PB3
#define DIG4 PB4

#define SEGA PD0
#define SEGB PD1
#define SEGC PD2
#define SEGD PD3
#define SEGE PD4
#define SEGF PD5
#define SEGG PD6
#define SEGDP PA0

#define TILT PA1

/* Define Polarity of Various IO Signals */
#define SEG_ON 1
#define DIG_ON 0  /* pull the digit's common-cathode to ground */
#define ENGLISH 1
#define ITALIAN 0

/* Just to Make Things More Convoluted */
#define HIGH 1
#define LOW 0
#define COMMON_TONGUE ENGLISH
#define VALERIAN ITALIAN


#include <avr/io.h>

int main (void) {
  DDRD = 0x7F; /* Set Port D pins 0, 1, 2, 3, 4, 5, & 6 pins to output */
  DDRB = 0x1F; /* Set Prot B pins 0, 1, 2, 3, & 4 to output */
  DDRA = (1 << SEGDP) | (0 << TILT);
  PORTD = 1 << SEGC;
  PORTB = 1 << DIG0;
  for (;;) {
    if ( (PORTA & (1<<TILT)) == (ENGLISH << TILT) )
      PORTD = 1 << SEGD;
    else
      PORTD = 1 << SEGA;
  }
  PORTD = 1 << SEGD;
  return 1;
}
