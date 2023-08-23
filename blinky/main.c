//AUTHOR: Sam Cooper
//Purpose: Turn LED1 and LED2 on

#include <msp430.h> 
#define LED1    0
#define LED2    1

//Turns on the LED based on parameter
//LED1 is 0 and LED2 is 1 as defined by macros
void turnOnLED(int led_choice) {
    //If LED1
    if(led_choice == 0) {
        P1DIR |= BIT0;
        P1OUT |= BIT0;
    }
    //If LED2
    if(led_choice == 1) {
        P2DIR |= BIT0;
        P2OUT |= BIT0;
    }
}

//Turns off the LED based on parameter
//LED1 is 0 and LED2 is 1 as defined by macros
void turnOffLED(int led_choice) {
    //If LED1
    if(led_choice == 0) {
        P1DIR |= BIT0;
        P1OUT &= ~BIT0;
    }
    //If LED2
    if(led_choice == 1) {
        P2DIR |= BIT0;
        P2OUT &= ~BIT0;
    }
}

//Set all pins to output and set their output voltage to 0 to save power
void uninitALLpins() {
    //Port 2
    P2DIR |= 0xFF;
    P2OUT &= 0x00;
    //Port 1
    P1DIR |= 0xFF;
    P1OUT &= 0x00;
}

/**
 * main.c
 */
int main(void)
{

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//Disable default high impedance mode for FRAM devies
	PM5CTL0 &= ~LOCKLPM5;

	uninitALLpins();

	turnOffLED(LED1);
	turnOffLED(LED2);
	turnOnLED(LED1);
	turnOnLED(LED2);

	//Enter Low Power Mode
	//No Need to clear this with a watchdog interrupt because there are no interrupts enabled
	__bis_SR_register(LPM3_bits + GIE);

	return 0;
}


//Notes:
//Uses --opt_for_speed 5 and --opt_level=0
//There is a Power optimization warning for PORT A being init but not used. This is an error there is no port A in MSP430FR2311

//END OF FILE
