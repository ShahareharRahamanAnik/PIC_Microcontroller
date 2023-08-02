/*
 * File:   lcd16x2.c
 * Author: Anik
 *
 * Created on August 1, 2023, 2:35 PM
 */

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

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
#define RS PORTDbits.RD0
#define RW PORTDbits.RD1
#define EN PORTDbits.RD2
void lcd_data(unsigned char data){
    PORTC  = data;
    RS = 1;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}
void lcd_command(unsigned char cmd){
    PORTC  = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}
void lcd_string(const unsigned char *str, unsigned char num) //str= system
{
    unsigned char i;
    for(i=0;i<num;i++){
        lcd_data(str[i]);
    }
}
void lcd_initialise(){
    lcd_command(0x38);
    lcd_command(0x06);
    lcd_command(0x0C);
    lcd_command(0x01);
    
}
void main(void) {
    
        TRISC =0x00;
        TRISD = 0x00;
        lcd_initialise();
        while(1){
            lcd_command(0x81);
            lcd_string("Micro",6);
            lcd_command(0xC1);
            lcd_string("Controller",11);
    }
    
    return;
}
