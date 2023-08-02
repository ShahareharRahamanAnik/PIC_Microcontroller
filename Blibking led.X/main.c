#include <xc.h>

// Configuration bits
#pragma config FOSC = HS        // High-Speed Crystal Oscillator (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000     // Define the oscillator frequency (20 MHz)

#define LED_PIN RC0             // Define the pin connected to the LED

void main() {
    TRISC0 = 0;                // Set RC0 as an output
    
    while (1) {
        LED_PIN = 1;           // Turn ON the LED
        __delay_ms(500);       // Delay 500 milliseconds
        
        LED_PIN = 0;           // Turn OFF the LED
        __delay_ms(500);       // Delay 500 milliseconds
    }
}
