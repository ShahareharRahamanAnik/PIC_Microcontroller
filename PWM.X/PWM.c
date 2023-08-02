/*
 * File:   PWM.c
 * Author: Anik
 *
 * Created on August 3, 2023, 3:59 AM
 */

// CONFIG
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
unsigned int DutyCycle;
void PWMCycle(DutyCycle){
    CCPR1L = DutyCycle>>2;
    CCP1CON = CCP1CON & 0xCF;
    CCP1CON = CCP1CON | (0x30 & (DutyCycle<<4));
}
unsigned int i=0;

void main(void) {
    TRISC   = 0x00;
    CCP1CON = 0x0C;
    PR2     = 0xFF;
    T2CON   = 0x04;
    while(1){
        for(i=0; i<1023; i++){
            PWMCycle(i);
            __delay_ms(2);
        }
        for(i=1023; i>0; i++){
            PWMCycle(i);
            __delay_ms(2);
        }
    }
    return;
}
