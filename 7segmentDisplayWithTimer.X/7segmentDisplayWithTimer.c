/*
 * File:   7segmentDisplayWithTimer.c
 * Author: Anik
 *
 * Created on August 2, 2023, 11:01 PM
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
#define _XTAL_FREQ 20000000      // Define the frequency of the internal oscillator (4MHz)
#define s1 1;
#define s0 0;
#include <xc.h>
unsigned char timer_count=0;
unsigned char number = 00;
unsigned char i, j;
unsigned char seg[10]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
void interrupt timer_0()
{
    if(INTCONbits.TMR0IF == 1)
    {
        if(timer_count == 2){
            timer_count =0;
        }
        if(timer_count==1){
        PORTCbits.RC0= 1;
        PORTCbits.RC1= 0;
        PORTB = seg[i];}
       // __delay_ms(10);   ekhne delay hbe na cz ekhne delay dya mane code er cycle k delay dya. but code nijei jehetu each 10ms e chk kortese tai value ta save thkei hbe.. nieje theke delay dile hbe bt ete code er time e bere jbe
        if(timer_count == 0){
        PORTCbits.RC1= 1;
        PORTCbits.RC0= 0;
        PORTB = seg[j];}
        timer_count++ ;
        INTCONbits.TMR0IF = 0;
    }
}
void main(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.TMR0IE = 1;
 
    OPTION_REG = 0X07;   //https://youtu.be/774-knrUXKw
    TMR0 = 59;
    TRISB = 0X00;
    TRISC0 = 0;
    TRISC1 = 0;
    while(1){
        i = number / 10;
        j = number%10;
         number++;
        if(number == 100){
            number = 0;
        }
        __delay_ms(1000);
    }
    return;
}

