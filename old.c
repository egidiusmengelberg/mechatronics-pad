#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>


ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
	PORTB ^= _BV(PB7);
	TCNT1 = 49911;   // for 1 sec at 16 MHz
}

int main(void) {
    cli();

    DDRB |= _BV(PB7); 
    
    TCNT1 = 49911;   // for 1 sec at 16 MHz	

	TCCR1A = 0x00;
	TCCR1B = (1<<CS10) | (1<<CS12);  // Timer mode with 1024 prescler
	TIMSK1 = (1 << TOIE1);   // Enable timer1 overflow interrupt(TOIE1)
	sei();        // Enable global interrupts by setting global interrupt enable bit in SREG

    while(1) {}
}