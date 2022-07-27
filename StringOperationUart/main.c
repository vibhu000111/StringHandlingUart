/*
 * StringOperationUart.c
 *
 * Created: 12/4/2021 1:24:02 PM
 * Author : Vibhu
 */ 

#define F_CPU 16000000L
#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define  BAUD 9600
#include <util/setbaud.h>
#define MAX 64
volatile unsigned char buffer [MAX];
volatile int index=0;

ISR(USART_RX_vect) {
	char received= UDR0 ;
	if(received == '\r')
	{
		UDR0= buffer[index];
		UCSR0B&=~_BV(RXCIE0);
		UCSR0B|= _BV(UDRIE0);
		
			}
	else
	{
		buffer[index]=received;
		index++;
		if(index>=MAX)
		index=0;
	}
	
	}
ISR(USART_UDRE_vect)
{
	if(index>=0)
	{
		index--;
		UDR0=buffer[index];
	}
	else
	{
	UCSR0B&=~_BV(UDRIE0);
	UCSR0B|= _BV(RXCIE0);	
	}
}
void uart_in_it()
{
	UBRR0H=UBRRH_VALUE;
	UBRR0L=UBRRL_VALUE;
	#if USE_2X
	UCSR0A|=_BV(U2X0);
	#else 
	UCSR0A&=~_BV(U2X0);
	#endif
	UCSR0C|=_BV(UCSZ01)|_BV(UCSZ00);
	UCSR0B|=_BV(RXCIE0)|_BV(RXEN0)|_BV(TXEN0);
}
int main(void)
{
    uart_in_it();
	sei();
    while (1) 
    {
    }
	return(0);
}

