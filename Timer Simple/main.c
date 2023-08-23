#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Disable the GPIO power-on default high-impedance mode to activate
	// previously configured port settings
	PM5CTL0 &= ~LOCKLPM5;


	//Initially stop the timer
	//TB0CCTL0 = 0;
	TB0CTL |= TBCLR;
	//Set initial count value to 0
	TB0R = 0;

	//Set clock source to SMCLK
	TB0CTL |= TBSSEL_1;
	//Set to up mode
	TB0CTL |= MC_1;
	//Set to 16 bit
	TB0CTL |= CNTL_0;

    //enable interrupts
    TB0CTL |= TBIE_1;

	//set value to count to
    TB0CCR0 = 100;


	while(1) {
	    __bis_SR_register(LPM0_bits + GIE);
	}
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR (void)
{
    __bic_SR_register_on_exit(LPM0_bits + GIE); //exit LPM0
}
