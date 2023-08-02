/*
 * File:   ADcTemperatureMeasure.c
 * Author: Anik
 *
 * Created on August 3, 2023, 2:15 AM
 */

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 4000000      // Define the frequency of the internal oscillator (4MHz)
#include <xc.h>
#define RS PORTDbits.RD0
#define RW PORTDbits.RD1
#define EN PORTDbits.RD2
unsigned int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;

unsigned int temp, adc;
float temperature, adc1;

void delay (unsigned int i) {
    while(i--);
}

void lcd_data(unsigned char data) {
    PORTC = data;
    RS = 1;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void lcd_command(unsigned char cmd) {
    PORTC = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    __delay_ms(500);
    EN = 0;
}

void lcd_string(const char *d, unsigned char num) {
    unsigned char w;
    for(w = 0; w < num; w++) {
        lcd_data(d[w]);
    }
}

void lcd_initialise() {
    lcd_command(0x38);
    lcd_command(0x06);
    lcd_command(0x0C);
    lcd_command(0x01);
}

void interrupt adc_conv() {
    if (PIR1bits.ADIF == 1) {
        adc = ((unsigned int)ADRESH << 8);
        adc = adc + ADRESL;
        PIR1bits.ADIF = 0;
    }
}

void main(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.ADIE = 1;
    TRISC = 0x00;
    TRISD = 0x00;
    lcd_initialise();
    lcd_command(0x81);
    lcd_string("SENSOR", 6);
    ADCON0 = 0x41;
    ADCON1 = 0x8E;

    while(1) {
        ADCON0 = ADCON0 | (0x04);
        adc1 = adc / 0.046; // temp value finding
        temperature = adc1 * 100; // fetching decimal place numbers

        lcd_command(0xc1);
        a = (int)temperature / 10;
        b = (int)temperature % 10;
        c = a % 10;
        d = a / 10; // Corrected from a % 10 to a / 10
        e = d % 10;
        f = d / 10;
        lcd_data(f + 0x30);
        lcd_data(e + 0x30);
        lcd_data('.');
        lcd_data(c + 0x30);
        lcd_data(b + 0x30);
    }

    return;
}
