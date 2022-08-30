/*
 * File:   main.c
 * Author: mustafa-arge
 *
 * Created on 19 A?ustos 2021 Per?embe, 09:12
 */

// PIC16F1512 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1


#define  _XTAL_FREQ 500000

#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = ON         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (VCAP pin function disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

//#define  led_3    PORTBbits.RB3
//#define  led_2    PORTBbits.RB4
//#define  led_1    PORTBbits.RB5

#define led_3     LATBbits.LATB3
#define led_2     LATBbits.LATB4
#define led_1     LATBbits.LATB5


#define p_mosfet  LATCbits.LATC0
#define open_p_mosfet   1
#define close_p_mosfet   0


#define close_switch  0
#define open_switch  1

#define first_switch PORTAbits.RA5


#define second_switch PORTAbits.RA4


#define third_switch PORTAbits.RA3


#define fourth_switch PORTAbits.RA2


#define fifth_switch PORTAbits.RA1


#define sixth_switch PORTAbits.RA0

//#define a_minute 60*2



/*
 typedef struct _control
 {
   unsigned char warning_system_1;  
   unsigned char warning_system_2;
   unsigned char warning_system_3;
   unsigned char warning_system_4;
   unsigned char warning_system_5;
   unsigned char warning_system_6;
}cont_Flag;

cont_Flag *control_Pointer,control_Flag;
*/
//unsigned char warning_system_1=0,warning_system_2=0,warning_system_3=0,warning_system_4=0,warning_system_5=0,warning_system_6=0;
unsigned char attention_flag=0;
unsigned char interval='N';
unsigned int  counter=0,counter_2=0;
//1 dakika için 60 say?s? yeterl? ?ken0,
//unsigned int  a_five_minute=600;
unsigned int  a_minute=60;//normalde 1 dakika için 120 olmas? laz?m sadece elektrik sayaç(KAD?R) için 600 yapt?k
//unsigned int  half_hour=(a_minute*30);
unsigned int  a_hour=7200;
unsigned int  two_hours=14400;
unsigned int  three_hours=21600;
unsigned long  four_hours=28800;
unsigned long  six_hours=86400;// 6 saat ?c?n 43200(6*2*60*60) ama burada 


//unsigned int  a_minute=120;
//unsigned int  half_hour=(a_minute*30);
unsigned int  two_minutes=240;
unsigned int  three_minutes=360;
unsigned int  four_minutes=480;
unsigned long  five_minutes=600;
unsigned long  six_minutes=720;


void __interrupt()tm0_kesme(void);
void warning_led(void);

/*
void station_control_1(void);
void station_control_2(void);
void station_control_3(void);
void station_control_4(void);
void station_control_5(void);
void station_control_6(void);
*/


unsigned int first_con=0,second_con=0,third_con=0,fourth_con=0,fifth_con=0,sixth_con=0;
void main(void) {
   
  ANSELA=0b00000000;//turn off adc pina feature of this device by writing "0" so no more it is digital io pin
  ANSELB=0b00000000;//turn off adc pinb feature of this device by writing "0" so no more it is digital io pin
  ANSELC=0b00000000;//turn off adc pinc  feature of this device by writing "0" so no more it is digital io pin
    
    
  TRISA=0b00111111;//a port is output this command is not enough because adc port is using this port also we have to close adc pins 
  TRISB=0b00000000; //for output 0, for input 1
  TRISC=0b00000000;  //output
  
  //PORTA=0x00;
  //PORTB=0x00;
  //PORTC=0x00;
    
  LATA=0x00;
  LATB=0x00;
  LATC=0b00000000;
  
  
  
  
  OPTION_REGbits.INTEDG=0;
  OPTION_REGbits.TMR0CS=0;
  //OPTION_REGbits.TMR0SE=0;
  OPTION_REGbits.PSA=0;  
  OPTION_REGbits.PS=7;
  
  
  INTCONbits.TMR0IE=0;
  INTCONbits.TMR0IF=0;
  TMR0=0;
  
  INTCONbits.GIE=1;
  
  //control_Pointer=&control_Flag;
  
  //control_Pointer->warning_system_1=0;      
  //control_Pointer->warning_system_2=0;
  //control_Pointer->warning_system_3=0;
 // control_Pointer->warning_system_4=0;
  
  __delay_ms(1000);
    while(1)
    {
    
       
       
        
        
        /*
        if(1==control_Pointer->warning_system_1)
        {
            station_control_1();
            
        }
         
        if(1==control_Pointer->warning_system_2)
        {
            station_control_2();
        }
        
        if(1==control_Pointer->warning_system_3)
        {
            station_control_3();
            
        }
        
        if(1==control_Pointer->warning_system_4)
        {
            station_control_4();
        }
        if(1==control_Pointer->warning_system_5)
        {
            station_control_5();
            
        }
         
        if(1==control_Pointer->warning_system_6)
        {
            station_control_6();
        }
*/
         
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        if(1==first_con)
        {
        if((counter==a_minute)&&(interval=='N'))
        {
        INTCONbits.TMR0IE=0;
        counter=0;    
        interval='Y';
        INTCONbits.TMR0IE=1;
        }
        }
        
        
        if(1==second_con)
        {
        if((counter==a_hour)&&(interval=='N'))
        {
        INTCONbits.TMR0IE=0;
        counter=0;    
        interval='Y';
        INTCONbits.TMR0IE=1;
        }
        }
        
        
        if(1==third_con)
        {
        if((counter==two_hours)&&(interval=='N'))
        {
        INTCONbits.TMR0IE=0;
        counter=0;    
        interval='Y';
        INTCONbits.TMR0IE=1;
        }
        }
        
        
        if(1==fourth_con)
        {
        if((counter==three_hours)&&(interval=='N'))
        {
        INTCONbits.TMR0IE=0;
        counter=0;    
        interval='Y';
        INTCONbits.TMR0IE=1;
        }
        }
        
        
        if(1==fifth_con)
        {
        if((counter==four_hours)&&(interval=='N'))
        {
        INTCONbits.TMR0IE=0;
        counter=0;    
        interval='Y';
        INTCONbits.TMR0IE=1;
        }
        }
        
        
        if(1==sixth_con)
        {
        if((counter==six_hours)&&(interval=='N'))
        {
        INTCONbits.TMR0IE=0;
        counter=0;    
        interval='Y';
        INTCONbits.TMR0IE=1;
        }
        }
        
        
        
        
        
        
        
        
        
        
        
        
        if((counter_2==30)&&(interval=='Y'))
        {
          INTCONbits.TMR0IE=0;
          counter_2=0;
          interval='N';
          INTCONbits.TMR0IE=1;
        }
        
        
        
        
        
        
        
        
        
        
        
        if((first_switch==open_switch)&&(first_con==0))
        
        {
       
            
      
                  
                __delay_ms(500);
                led_3=1;
                while(second_switch==open_switch)
                {
                    warning_led();
                }
                while(third_switch==open_switch)
                {
                    warning_led();
                }
                while(fourth_switch==open_switch)
                {
                    warning_led();
                }
                while(fifth_switch==open_switch)
                {
                    warning_led();
                }
                while(sixth_switch==open_switch)
                {
                    warning_led();
                }
                
                first_con=1;
                second_con=0;
                third_con=0;
                fourth_con=0;
                fifth_con=0;
                sixth_con=0;
                INTCONbits.TMR0IE=1;      
                  
                
                
            
            
        }
       
        
        if((first_switch==close_switch)&&(first_con==1))
        
        {
           
            led_3=0;
           first_con=0;
           second_con=0;
           third_con=0;
           fourth_con=0;
           fifth_con=0;
           sixth_con=0;
           
           p_mosfet=close_p_mosfet;
           counter=0;
           counter_2=0;
           led_1=0;
           led_2=0;
           interval='N';
           INTCONbits.TMR0IE=0;
        }
        
       
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        if((second_switch==open_switch)&&(second_con==0))
        
        {
           
              
                  
                   __delay_ms(500);
                   led_3=1;
                while(first_switch==open_switch)
                {
                    warning_led();
                }
                while(third_switch==open_switch)
                {
                    warning_led();
                }
                while(fourth_switch==open_switch)
                {
                    warning_led();
                }
                while(fifth_switch==open_switch)
                {
                    warning_led();
                }
                while(sixth_switch==open_switch)
                {
                    warning_led();
                }
                   
                   first_con=0;
                   second_con=1;
                   third_con=0;
                   fourth_con=0;
                   fifth_con=0;
                   sixth_con=0;
                   INTCONbits.TMR0IE=1;
                      
                  
                  
              
            
        }
       
        if((second_switch==close_switch)&&(second_con==1))
        
        {
           
            led_3=0;
            first_con=0;
           second_con=0;
           third_con=0;
           fourth_con=0;
           fifth_con=0;
           sixth_con=0;
           
           p_mosfet=close_p_mosfet;
           counter=0;
           counter_2=0;
           led_1=0;
           led_2=0;
           interval='N';
           //attention_flag=0;
          // control_Pointer->warning_system_2=0;
           INTCONbits.TMR0IE=0;
        }
        
        
        
        
        
        
        
        
        
        if((third_switch==open_switch)&&(third_con==0))
        
        {
            __delay_ms(500);
            led_3=1;
           
                while(first_switch==open_switch)
                {
                    warning_led();
                }
                while(second_switch==open_switch)
                {
                    warning_led();
                }
                while(fourth_switch==open_switch)
                {
                    warning_led();
                }
                while(fifth_switch==open_switch)
                {
                    warning_led();
                }
                while(sixth_switch==open_switch)
                {
                    warning_led();
                }
            
            
            
            first_con=0;
           second_con=0;
           third_con=1;
           fourth_con=0;
           fifth_con=0;
           sixth_con=0;
           INTCONbits.TMR0IE=1;
            
        
            
        }
       if((third_switch==close_switch)&&(third_con==1))
        
        {
           
            led_3=0;
            first_con=0;
           second_con=0;
           third_con=0;
           fourth_con=0;
           fifth_con=0;
           sixth_con=0;
           
           p_mosfet=close_p_mosfet;
           counter=0;
           counter_2=0;
           led_1=0;
           led_2=0;
           interval='N';
           INTCONbits.TMR0IE=0;
             
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
         if((fourth_switch==open_switch)&&(fourth_con==0))
        
        {
            __delay_ms(500);
            led_3=1;
                while(first_switch==open_switch)
                {
                    warning_led();
                }
                while(second_switch==open_switch)
                {
                    warning_led();
                }
                while(third_switch==open_switch)
                {
                    warning_led();
                }
                while(fifth_switch==open_switch)
                {
                    warning_led();
                }
                while(sixth_switch==open_switch)
                {
                    warning_led();
                }
           first_con=0;
           second_con=0;
           third_con=0;
           fourth_con=1;
           fifth_con=0;
           sixth_con=0;
           INTCONbits.TMR0IE=1;
        
            
        }
       if((fourth_switch==close_switch)&&(fourth_con==1))
        
        {
           
            led_3=0;
            first_con=0;
           second_con=0;
           third_con=0;
           fourth_con=0;
           fifth_con=0;
           sixth_con=0;
           
           
           p_mosfet=close_p_mosfet;
           counter=0;
           counter_2=0;
           led_1=0;
           led_2=0;
           interval='N';
           INTCONbits.TMR0IE=0;
        
             
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    
         if((fifth_switch==open_switch)&&(fifth_con==0))
        
        {
            __delay_ms(500);
            led_3=1;
                while(first_switch==open_switch)
                {
                    warning_led();
                }
                while(second_switch==open_switch)
                {
                    warning_led();
                }
                while(third_switch==open_switch)
                {
                    warning_led();
                }
                while(fourth_switch==open_switch)
                {
                    warning_led();
                }
                while(sixth_switch==open_switch)
                {
                    warning_led();
                }
           first_con=0;
           second_con=0;
           third_con=0;
           fourth_con=0;
           fifth_con=1;
           sixth_con=0;
           INTCONbits.TMR0IE=1; 
        
            
        }
       if((fifth_switch==close_switch)&&(fifth_con==1))
        
        {
           
            led_3=0;
            first_con=0;
           second_con=0;
           third_con=0;
           fourth_con=0;
           fifth_con=0;
           sixth_con=0;
           
           
           p_mosfet=close_p_mosfet;
           counter=0;
           counter_2=0;
           led_1=0;
           led_2=0;
           interval='N';
           INTCONbits.TMR0IE=0;
        
             
        }
        
        
        
        
        
        
        
        
        
        
        
        
        
         if((sixth_switch==open_switch)&&(sixth_con==0))
        
        {
            __delay_ms(500);
            led_3=1;
                while(first_switch==open_switch)
                {
                    warning_led();
                }
                while(second_switch==open_switch)
                {
                    warning_led();
                }
                while(third_switch==open_switch)
                {
                    warning_led();
                }
                while(fourth_switch==open_switch)
                {
                    warning_led();
                }
                while(fifth_switch==open_switch)
                {
                    warning_led();
                }
           first_con=0;
           second_con=0;
           third_con=0;
           fourth_con=0;
           fifth_con=0;
           sixth_con=1;
           INTCONbits.TMR0IE=1; 
        
            
        }
       if((sixth_switch==close_switch)&&(sixth_con==1))
        
        {
           
            led_3=0;
            first_con=0;
           second_con=0;
           third_con=0;
           fourth_con=0;
           fifth_con=0;
           sixth_con=0;
           
           
           p_mosfet=close_p_mosfet;
           counter=0;
           counter_2=0;
           led_1=0;
           led_2=0;
           interval='N';
           INTCONbits.TMR0IE=0;
        
             
        }
        
        
        
        
        
        
        
        
    }
    
    return;
}
void __interrupt()tm0_kesme(void)
{
   if(INTCONbits.TMR0IF)
   {
       INTCONbits.TMR0IE=0;
       
       if(interval=='N')
       {
       ++counter;       
       led_1^=1;
       p_mosfet=open_p_mosfet;
       }
       
       if(interval=='Y')
       {
           ++counter_2;
           led_2^=1;
       p_mosfet=close_p_mosfet;
       }
         
        
   }
   
     INTCONbits.TMR0IF=0;//flag should be cleared by the programmer
     INTCONbits.TMR0IE=1;//again we are  opening interrupt so that interrupt occured
     
     //TMR0=0;
}
void warning_led(void)
{    
     led_3=0;
     led_3=1;
      __delay_ms(150);
     led_3=0;
     __delay_ms(150);
               /*
                first_con=0;
                second_con=0;
                third_con=0;
                fourth_con=0;
                fifth_con=0;
                sixth_con=0;
                control_Pointer->warning_system_1=0;
                control_Pointer->warning_system_2=0;
                control_Pointer->warning_system_3=0;
                control_Pointer->warning_system_4=0;
                control_Pointer->warning_system_5=0;
                control_Pointer->warning_system_6=0;
                */
     
     
      counter=0;
      counter_2=0;
      led_1=0;
      led_2=0;
      interval='N';
      //attention_flag=0;
      //control_Pointer->warning_system_1=0;
      INTCONbits.TMR0IE=0;
}

/*
void station_control_1(void)
{
            while(1==control_Pointer->warning_system_2)
            {
               
                warning_led();
                
                
            }
              while(1==control_Pointer->warning_system_3)
            {
               
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_4)
            {
               
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_5)
            {
               
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_6)
            {
               
                warning_led();
                
                
            }
    
    
    
    
    
    
}
void station_control_2(void)
{
            while(1==control_Pointer->warning_system_1)
            {
               
                warning_led();
                
                
            }
              while(1==control_Pointer->warning_system_3)
            {
               
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_4)
            {
                
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_5)
            {
                
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_6)
            {
               
                warning_led();
                
                
            }
    
    
    
}

void station_control_3(void)
{
            while(1==control_Pointer->warning_system_1)
            {
               
                warning_led();
                
                
            }
              while(1==control_Pointer->warning_system_2)
            {
                
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_4)
            {
               
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_5)
            {
                
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_6)
            {
                
                warning_led();
                
                
            }
    
    
    
    
    
    
}

void station_control_4(void)
{
            while(1==control_Pointer->warning_system_1)
            {
               
                warning_led();
                
                
            }
              while(1==control_Pointer->warning_system_2)
            {
                
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_3)
            {
                
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_5)
            {
                
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_6)
            {
                
                warning_led();
                
                
            }
    
    
    
    
    
    
}

void station_control_5(void)
{
            while(1==control_Pointer->warning_system_1)
            {
               
                warning_led();
                
                
            }
              while(1==control_Pointer->warning_system_2)
            {
                
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_3)
            {
              
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_4)
            {
               
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_6)
            {
               
                warning_led();
                
                
            }
    
    
    
    
    
    
}
void station_control_6(void)
{
            while(1==control_Pointer->warning_system_1)
            {
                
                warning_led();
                
                
            }
              while(1==control_Pointer->warning_system_2)
            {
              
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_3)
            {
               
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_4)
            {
                
                warning_led();
                
                
            }
             while(1==control_Pointer->warning_system_5)
            {
              
                warning_led();
                
                
            }
    
    
    
    
    
    
}
 */