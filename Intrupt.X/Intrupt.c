/*
 * File:   Intrupt.c
 * Author: Anik
 *
 * Created on August 2, 2023, 1:21 AM
 */


#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 4000000      // Define the frequency of the internal oscillator (4MHz)
#include <xc.h>

void interrupt external(){
    if(INTCONbits.INTF == 1){
        PORTBbits.RB1 = ~PORTBbits.RB1; 
        INTCONbits.INTF= 0;
    }
}
void main(void) {
    INTCONbits.GIE = 1;
    INTCONbits.INTE = 1;
    INTCONbits.PEIE = 1;
    OPTION_REGbits.INTEDG = 1;   //https://youtu.be/9xty6u_R66A
    TRISB1 = 0;
    while(1){
       
    }
    return;
}
