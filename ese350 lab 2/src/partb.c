#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void Initialize();

int main(void) {
  Initialize();


  while (1){}
}

void Initialize() {
  
  //disable global interrupts
  cli();

  //Interrupt pin setup
  TIMSK1 |= (1 << ICIE1);
  TCCR1B |= (1 << ICES1);
  DDRB |= (1 << DDB5); // Sets up input pin
  
  // Reenable interrupts
  sei();
}

ISR(TIMER1_CAPT_vect) {
//   edge = ICR1;
  TIFR1 |= (1 << ICF1);

  if (PINB & (1 << PINB0)) {
    PORTB |= (1 << PORTB5);
  } else {
    PORTB &= ~(1 << PORTB5);
  }

  TCCR1B ^= (1 << ICES1);
}
