/*
 * File:   keypad.c
 * Author: Anik
 *
 * Created on August 2, 2023, 12:28 AM
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
#define RS PORTDbits.RD0
#define RW PORTDbits.RD1
#define EN PORTDbits.RD2
#define C1 PORTBbits.RB1
#define C2 PORTBbits.RB2
#define C3 PORTBbits.RB3
#define A PORTBbits.RB4
#define B PORTBbits.RB5
#define C PORTBbits.RB6
#define D PORTBbits.RB7
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
void keypad(){
  C1=1;C2=0;C3=0;
  if(A==1){
      lcd_data('1');
      while(A==1);
  }
  if(B==1){
      lcd_data('4');
      while(B==1);
  }
  if(C==1){
      lcd_data('7');
      while(C==1);
  }
  if(D==1){
      lcd_data('*');
      while(D==1);
  }
   C1=0;C2=1;C3=0;
  if(A==1){
      lcd_data('2');
      while(A==1);
  }
  if(B==1){
      lcd_data('5');
      while(B==1);
  }
  if(C==1){
      lcd_data('8');
      while(C==1);
  }
  if(D==1){
      lcd_data('0');
      while(D==1);
  } C1=0;C2=0;C3=1;
  if(A==1){
      lcd_data('3');
      while(A==1);
  }
  if(B==1){
      lcd_data('6');
      while(B==1);
  }
  if(C==1){
      lcd_data('9');
      while(C==1);
  }
  if(D==1){
      lcd_data('#');
      while(D==1);
  }
}
void main(void) {
    
        TRISC =0x00;
        TRISD = 0x00;
        TRISB = 0xF0;
        lcd_initialise();
       
            lcd_command(0x80);
            lcd_string("Keypad:",7);
            lcd_command(0xC1);
            
       while(1){
           keypad();
    }
    
    return;
}
