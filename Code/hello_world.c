/* hello_world.c */

/* Is this Board 1 or 2? */
#define BOARD 1

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
#define ENGLISH 0
#define ITALIAN 1

/* Just to Make Things More Convoluted */
#define HIGH 1
#define LOW 0
#define COMMON_TONGUE ENGLISH
#define VALERIAN ITALIAN

#include <string.h>
#include <avr/io.h>

const char en_H = 1 << SEGF | 1 << SEGE | 1 << SEGG | 1 << SEGB | 1 << SEGC;
const char en_E = 1 << SEGB | 1 << SEGC | 1 << SEGA | 1 << SEGG | 1 << SEGD;
const char en_L = 1 << SEGB | 1 << SEGC | 1 << SEGA;
const char en_O = ~(1 << SEGG);
const char en_o = 1 << SEGF | 1 << SEGA | 1 << SEGB | 1 << SEGG;
const char en_r = 1 << SEGB | 1 << SEGG;
const char en_l = 1 << SEGB | 1 << SEGC;
const char en_d = 1 << SEGA | 1 << SEGB | 1 << SEGE | 1 << SEGF | 1 << SEGG;
const char en_exclamation = 1 << SEGE;
const char en_decimal = 1 << SEGDP;
const char it_C = 1 << SEGA | 1 << SEGF | 1 << SEGE | 1 << SEGD;
const char it_i = 1 << SEGA | 1 << SEGG | 1 << SEGD | 1 << SEGE | 1 << SEGC;
const char it_A = ~(1 << SEGD);
const char it_o = 1 << SEGE | 1 << SEGD | 1 << SEGC | 1 << SEGG;
const char it_n = 1 << SEGE | 1 << SEGG | 1 << SEGC;
const char it_d = 1 << SEGE | 1 << SEGD | 1 << SEGC | 1 << SEGG | 1 << SEGB;
const char it_exclamation = 1 << SEGB;
const char it_decimal = 1 << SEGDP;

void display_function (const char *, const char *);

int main (void) {
  DDRD = 0x7F; /* Set Port D pins 0, 1, 2, 3, 4, 5, & 6 pins to output */
  DDRB = 0x1F; /* Set Prot B pins 0, 1, 2, 3, & 4 to output */
  DDRA = (1 << SEGDP) | (0 << TILT);
  PORTD = 1 << SEGC;
  PORTB = 0xFE;
  char five_letters[5];
  char punctuations[5];
  for (;;) {
    memset (punctuations, 0, 5);
    /* If board #1 and tilted English, display "HELLO"              */
    if (BOARD == 1 && (PINA & 1<<TILT) == (ENGLISH << TILT) )
    {
      five_letters[4] = en_H;
      five_letters[3] = en_E;
      five_letters[2] = en_L;
      five_letters[1] = en_L;
      five_letters[0] = en_O;
    }
    /* If board #2 and tilted English, display W "orld!"            */
    else if (BOARD == 2 && (PINA & 1<<TILT) == (ENGLISH << TILT))
    {
      five_letters[4] = en_o;
      five_letters[3] = en_r;
      five_letters[2] = en_l;
      five_letters[1] = en_d;
      five_letters[0] = en_exclamation;
      punctuations[0] = en_decimal;
    }
    /* If board #2 and tilted Italian, display "ciao" M             */
    else if (BOARD == 2 && (PINA & 1<<TILT) == (ITALIAN << TILT))
    {
      five_letters[0] = 0;
      five_letters[1] = it_C;
      five_letters[2] = it_i;
      five_letters[3] = it_A;
      five_letters[4] = en_O;
    }
    /* If board #1 and tilted Italian, display "ondo!"              */
    else
    {
      five_letters[0] = it_o;
      five_letters[1] = it_n;
      five_letters[2] = it_d;
      five_letters[3] = it_o;
      five_letters[4] = it_exclamation;
      punctuations[4] = it_decimal;
    }

    /* Multiplex the 5 letters, timesharing between the 5 displays  */
    display_function (five_letters, punctuations);
  }
  /* This Point Should Never be Reached! */
  return 1;
}

void display_function (const char *letters, const char *decimals)
{
  int time;
  for (time = 0; time < 256; time++)
  {
    if (time < 50) {
      PORTB = ~ (1 << DIG0);
      PORTD = letters[0];
      PORTA = decimals[0];
    }
    else if (time < 100) {
      PORTB = ~ (1 << DIG1);
      PORTD = letters[1];
      PORTA = decimals[1];
    }
    else if (time < 150) {
      PORTB = ~ (1 << DIG2);
      PORTD = letters[2];
      PORTA = decimals[2];
    }
    else if (time < 200) {
      PORTB = ~ (1 << DIG3);
      PORTD = letters[3];
      PORTA = decimals[3];
    }
    else {
      PORTB = ~ (1 << DIG4);
      PORTD = letters[4];
      PORTA = decimals[4];
    }
  }
  return;
}
