#include <xc.h>

// Define the LED pin
#define LED_PORT PORTD
#define LED_PIN 0

void main(void) {
    // Set the LED pin as output
    LED_PORTbits.RD0 = 0;

    // Infinite loop
    while (1) {
        // Turn the LED on
        LED_PORTbits.RD0 = 1;

        // Delay for a second
        __delay_ms(1000);

        // Turn the LED off
        LED_PORTbits.RD0 = 0;

        // Delay for a second
        __delay_ms(1000);
    }
}
