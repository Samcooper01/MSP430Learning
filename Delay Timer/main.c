#include <msp430.h> 
#include <stdio.h>
#include <stdbool.h>

#define LED1    0
#define LED2    1

bool toggleSwitch = true;

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

//Setup for ACLK
void setACLKsource() {
    //Set clock to 32k-hz source
    //clear bits 8-9
    CSCTL4 &= ~(0x0600);
    //set bits 8-9 to 01 for REF0 clock
    CSCTL4 |= (0x0200);
}

void timerB_init() {
    //Clear the timer
    TB0CTL |= TBCLR;
    //Set initial count value to 0
    TB0R = 0;
    //Set clock source to ACLK
    TB0CTL |= TBSSEL__ACLK;
    //divide clock input by 8
    TB0CTL |= ID__8;
    //Set to continuous mode
    TB0CTL |= MC__UP;
    //Set to 16 bit
    TB0CTL |= CNTL_0;
}

//MAIN
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    setACLKsource();
    //clock runs at 4khz
    timerB_init();

    //enable interrupts
    TB0CTL |= TBIE_1;

    //set value to count to
    //This will take one second to count to
    TB0CCR0 = 4000;


    while(1) {
        __bis_SR_register(LPM0_bits + GIE);
        if(toggleSwitch) {
            turnOnLED(LED1);
            turnOffLED(LED2);
        }
        else {
            turnOffLED(LED1);
            turnOnLED(LED2);
        }

    }
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR (void)
{

    toggleSwitch = !toggleSwitch;
    //clear flag
    TB0CTL &= ~TBIFG;
    __bic_SR_register_on_exit(LPM0_bits + GIE); //exit LPM0
}
