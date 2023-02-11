#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <uart.h>
#include <string.h>

#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

volatile int duration = 0;
volatile int printed = 0;
volatile int startTime = 0;
volatile int num_appended = 0;
volatile int decode = 0;


char container[8];

#define small 233
#define medium 1562
// #define large 3124
# define large 24992

typedef struct
{
    char* morse;
    char* ascii;
} morse_table_t;

morse_table_t table[] = {
                        {".-", "A"},
                        {"-...", "B"},
                        {"-.-.", "C"},
                        {"-..",  "D"},
                        {".",    "E"},
                        {"..-.", "F"},
                        {"--.",  "G"},
                        {"....", "H"},
                        {"..",   "I"},
                        {".---", "J"},
                        {"-.-",  "K"},
                        {".-..", "L"},
                        {"--",   "M"},
                        {"-.",   "N"},
                        {"---",  "O"},
                        {".--.", "P"},
                        {"--.-", "Q"},
                        {".-.",  "R"},
                        {"...",  "S"},
                        {"-",    "T"},
                        {"..-",  "U"},
                        {"...-", "V"},
                        {".--",  "W"},
                        {"-..-", "X"},
                        {"-.--", "Y"},
                        {"--..", "Z"},
                        {".----", "1"},
                        {"-----", "0"},
                        {"..---", "2"},
                        {"...--", "3"},
                        {"....-", "4"},
                        {".....", "5"},
                        {"-....", "6"},
                        {"--...", "7"},
                        {"---..", "8"},
                        {"----.", "9"}
                    };


void Initialize();

int main(void) {
  Initialize();

  while (1){
    if ((TCNT1 - startTime) > large) {
        startTime = TCNT1;
        _delay_ms(1000);
        for(int i=0; i<(sizeof(table)/sizeof(table[0])); ++i)
        {
            startTime = TCNT1;
            if (!strcmp(container, table[i].morse)){

                UART_putstring(table[i].ascii);
                container[0] = '\0';
                num_appended = 0;
                break;
            }
        }
    }
  }
}

void Initialize() {

  //disable global interrupts
  cli();

  //Interrupt pin setup
  TIMSK1 |= (1 << ICIE1);
  TCCR1B |= (1 << ICES1);

  //Input pin
  DDRB &= ~(1 << DDB0);

  // Set up output pins
  DDRB |= (1 << DDB5);
  DDRB |= (1 << DDB4);

  // Prescaling
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B |= (1 << CS10);


  // Reenable interrupts
  sei();

  UART_init(BAUD_PRESCALER);
}

ISR(TIMER1_CAPT_vect) {
  TIFR1 |= (1 << ICF1);

  if (TCCR1B & (1 << ICES1)) {
    TCNT1 = 0;
  } else {
    duration = TCNT1;
    if (duration > small && duration < large) {
        // Dot
        if (duration < medium) {
          duration = 0;
          if (num_appended == 7) {
            container[0] = '\0';
            num_appended = 0;
          } else {
            container[num_appended] = '.';
            container[num_appended + 1] = '\0';
            num_appended++;
          }
          PORTB |= (1 << PORTB5);
          _delay_ms(50);
          PORTB &= ~(1 << PORTB5);
          startTime = TCNT1;
        //   UART_putstring(".\n");
        }

        // Dash
        else {
          duration = 0;
          if (num_appended == 7) {
            container[0] = '\0';
            num_appended = 0;
          } else {
            container[num_appended] = '-';
            container[num_appended + 1] = '\0';
            num_appended++;
          }
          PORTB |= (1 << PORTB4);
          _delay_ms(50);
          PORTB &= ~(1 << PORTB4);
          startTime = TCNT1;
        }

  }
  else {
  }
  }

  TCCR1B ^= (1 << ICES1);
  startTime = TCNT1;
}