#include <avr/io.h>

int main(void)
{
    DDRB |= (1 << DDB5);     // PB5 output
    DDRB &= ~(1 << DDB0);    // PB0 input

    while (1)
    {
        if (PINB & (1 << PINB0))
        {
            // PB0 HIGH -> LED ON
            PORTB |= (1 << PORTB5);
        }
        else
        {
            // PB0 LOW -> LED OFF
            PORTB &= ~(1 << PORTB5);
        }
    }
}