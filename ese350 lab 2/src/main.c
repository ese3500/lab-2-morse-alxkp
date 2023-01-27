#include <avr/io.h>
#include <util/delay.h>

void Initialize() {
  DDRB |= (1<<DDB4);
  DDRB |= (1<<DDB3);
  DDRB |= (1<<DDB2);
  DDRB |= (1<<DDB1);
  DDRD &= ~(1<<DDD7);
}

int main(void) {
  Initialize();

  while (1)
  {
    if(PIND&(1<<PIND7)) {
      PORTB |= (1<<PORTB4);
      PORTB |= (1<<PORTB3);
      PORTB |= (1<<PORTB2);
      PORTB |= (1<<PORTB1);
    } else {
      PORTB &= ~(1<<PORTB4);
      PORTB &= ~(1<<PORTB3);
      PORTB &= ~(1<<PORTB2);
      PORTB &= ~(1<<PORTB1);
    }
  }
}
