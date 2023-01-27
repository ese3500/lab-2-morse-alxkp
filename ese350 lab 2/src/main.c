#include <avr/io.h>

void Initialize() {
  DDRB |= (1<<DDB4);
  DDRB |= (1<<DDB3);
  DDRB |= (1<<DDB2);
  DDRB |= (1<<DDB1);
}

int main(void) {
  Initialize();

  PORTB |= (1<<PORTB4);
  PORTB |= (1<<PORTB3);
  PORTB |= (1<<PORTB2);
  PORTB |= (1<<PORTB1);
}
