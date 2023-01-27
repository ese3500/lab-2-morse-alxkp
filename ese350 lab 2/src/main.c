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

  int counter = 0;

  while (1)
  {
    if (PIND & (1 << PIND7)) {
      if (counter == 4) {
        counter = 0;
      } else {
        counter++;
      }
    }
    
    switch (counter)
    {
    case 0:
      PORTB &= ~(0x1C);
      _delay_ms(200);
      PORTB |= (1 << PORTB1);
      break;
    case 1:
      PORTB &= ~(0x1A);
      _delay_ms(200);
      PORTB |= (1 << PORTB2);
      break;
    case 2:
      PORTB &= ~(0x16);
      _delay_ms(200);
      PORTB |= (1 << PORTB3);
      break;
    case 3:
      PORTB &= ~(0xE);
      _delay_ms(200);
      PORTB |= (1 << PORTB4);
      break;
    default:
      break;
    }
  }
}
