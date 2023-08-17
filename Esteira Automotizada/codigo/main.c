#include "conf.h" 
#include "lcd.h"
#include "i2c.h"
#include "rtc.h"
#include "teclado.h"
#include "adc.h"

unsigned char tmp;
unsigned char tmp2;
unsigned char tmp3;
unsigned char min=0;
unsigned int l;
unsigned char m=1;
unsigned char aux=1;
unsigned int max=0;
unsigned int n=0;
unsigned int troca;
unsigned char b1=0;
unsigned char b0=0;
unsigned int check=0;



void __interrupt() ISR(void){

    if(INTCONbits.INT0IF == 1){

        INTCONbits.INT0IF = 0;
        
        if(max==0 || min>=max)
            {
                lcd_cmd(L_L1) ;
                lcd_cmd(L_CLR) ;
                lcd_str("Vazio") ;
                
            }
            else
            {
              
   
                troca=m;
                
                tmp2=(unsigned char)troca;
                lcd_cmd(L_CLR) ;
                lcd_cmd(L_L1) ;
                lcd_str("Entrada") ;
                lcd_cmd(L_L2) ;
                lcd_str("Movendo") ;
                lcd_cmd(L_L3) ;
                lcd_str("Mala") ;
                while(tmp2==255){ tmp2=tc_tecla(); }
                TRISD=0x00;
                if(tmp2==10){
                tmp2=tmp2+0x20;
                }else{
                if(tmp2==12){
                tmp2=tmp2+0x17;
                }else{
                 tmp2=tmp2+0x30;
                }   
                }
                lcd_dat(tmp2);
                __delay_ms(100);
                m++;
                b1=0;
                b0=0;
                for(l=0;l<4;l++, min++)
                {
                    tmp3=e2pext_r(min);
                    tmp3=tmp3-0x30;
                    if(min%2==1)
                    {
                        b0+=tmp3;
                    }
                    else
                    {
                        b1+=tmp3;
                    }
                }
                
                
                TRISD=0x00 ; // Portas D e E sao usadas no LCD
                TRISE=0x00 ;
                TRISCbits.TRISC0=0;
                TRISEbits.TRISE0=0;
                if(b1%2==1)
                {
                     PORTCbits.RC0=1;
                }
                  if(b0%2==1)
                {
                     PORTEbits.RE0=1;
                }
               
                  PORTCbits.RC2=1;
                  TRISA=0x00;  // pinos como saidas
                  LATA=0x00;   // zera LATB
                  PORTA=0;
                  
                     lcd_cmd(L_L1) ;
                     lcd_str("Terminal 1") ;
                      PORTAbits.RA0=1;
                      __delay_ms(200);
                    if(b1%2==0 && b0%2==0)
                    {   
                        for(l=0;l<10;l++)
                        {
                             PORTAbits.RA0=1;
                            __delay_ms(10);
                            PORTAbits.RA0=0;
                            __delay_ms(10);
                        }
                     lcd_cmd(L_L2) ;
                     lcd_str("Parado") ;    
                    }
                    else
                    {
                        lcd_cmd(L_L1) ;
                        lcd_str("Terminal 2") ;
                        PORTAbits.RA0=0;
                        PORTAbits.RA1=1;
                        __delay_ms(200);
                        if(b1%2==0 && b0%2==1)
                        {   
                             for(l=0;l<10;l++)
                            {   
                             PORTAbits.RA1=1;
                            __delay_ms(10);
                            PORTAbits.RA1=0;
                            __delay_ms(10);
                            }
                        lcd_cmd(L_L2) ;
                        lcd_str("Parado") ;
                        }
                        else
                        {
                            lcd_cmd(L_L1) ;
                            lcd_str("Terminal 3") ;
                            PORTAbits.RA1=0;
                            PORTAbits.RA2=1;
                            __delay_ms(200);
                            if(b1%2==1 && b0%2==0)
                            {   
                                 for(l=0;l<10;l++)
                                {
                                 PORTAbits.RA2=1;
                                 __delay_ms(10);
                                PORTAbits.RA2=0;
                                __delay_ms(10);
                                }
                            lcd_cmd(L_L2) ;
                            lcd_str("Parado") ;
                            }
                            else
                            {
                                lcd_cmd(L_L1) ;
                                lcd_str("Terminal 4") ;
                                PORTAbits.RA2=0;
                                PORTAbits.RA3=1;
                                __delay_ms(200);
                                
                                 for(l=0;l<10;l++)
                                {
                                 PORTAbits.RA3=1;
                                 __delay_ms(10);
                                PORTAbits.RA3=0;
                                __delay_ms(10);
                                }
                                lcd_cmd(L_L2) ;
                                lcd_str("Parado") ;
                                PORTAbits.RA3=0;
                            }
                        }
                    }
                __delay_ms(200);
               
                PORTCbits.RC2=0;
               PORTCbits.RC0=0;
               PORTEbits.RE0=0;
              
            }
                lcd_cmd(L_CLR) ;
                check=0;
            
    }else{

        if(INTCON3bits.INT1IF == 1){

            INTCON3bits.INT1IF = 0;
  
        TRISA=0xFF;
        TRISB=0x00;
        TRISD=0x00;
        TRISE=0x00;
        ADCON1=0x02 ;
         
      lcd_cmd(L_CLR) ;
       lcd_cmd(L_L1) ;
      lcd_str("Digite o codigo") ;
      lcd_cmd(L_L2);
      lcd_str("da mala ") ;
      lcd_cmd(L_L3);
      lcd_str("de 4 digitos") ;
      lcd_cmd(L_L4);
      for(l=20;l<24;l++)
      {
        
        TRISB=0xF0;
        TRISD=0x0F;
        tmp=tc_tecla();
        while(tmp==255){ tmp=tc_tecla(); }
        TRISD=0x00;
        if(tmp==10){
        tmp=tmp+0x20;
        }else{
        if(tmp==12){
            tmp=tmp+0x17;
        }else{
           tmp=tmp+0x30;
        }   
        }
         TRISC=0x01;
        e2pext_w(max,tmp); 
        tmp2=e2pext_r(max);
        lcd_dat(tmp2); 
        max++;
        
      }
      __delay_ms(200) ;
      
      ADCON1 = 0x0F; 
      TRISC=0x01;
      TRISD=0x00 ; // Portas D e E sao usadas no LCD
      TRISE=0x00 ;
      TRISE=0x00 ;
      TRISB=0x07 ;
      TRISA=0x10 ;
      lcd_cmd(L_CLR) ;
      check=0;
        }
        else{
            if(INTCON3bits.INT2IF == 1){
            INTCON3bits.INT2IF=0;   // Limpa a interrupcao  

            if(max==0 || min>=max)
            {
                lcd_cmd(L_L1) ;
                lcd_cmd(L_CLR) ;
                lcd_str("Vazio") ;
            }
            else
            {
                n=min;
                aux=m;
                while(n<max)
                {
                tmp2=aux;
                lcd_cmd(L_L1) ;
                lcd_cmd(L_CLR) ;
                lcd_str("Mala") ;
                while(tmp2==255){ tmp2=tc_tecla(); }
                TRISD=0x00;
                if(tmp2==10){
                tmp2=tmp2+0x20;
                }else{
                if(tmp2==12){
                tmp2=tmp2+0x17;
                }else{
                 tmp2=tmp2+0x30;
                }   
                }
                lcd_dat(tmp2) ;
                lcd_cmd(L_L2) ;
                for(l=0;l<4;l++,n++)
                {
                     lcd_dat(e2pext_r(n));
                }
                
                __delay_ms(100) ;
                aux++;
                }
                
            }
            

             __delay_ms(200) ;

            }
            lcd_cmd(L_CLR) ;
            check=0;
        }            
    }     
  }


 void main(void) {        

      unsigned char x;
      ADCON1 = 0x0F; 
      TRISC=0x01;
      TRISD=0x00 ; // Portas D e E sao usadas no LCD
      TRISE=0x00 ;
      TRISB=0x07 ;
      TRISA=0x10 ;
      lcd_init( );                  
      adc_init( ) ;
      i2c_init();
      RCONbits.IPEN = 0;
      INTCONbits.GIE = 1; 
      INTCONbits.INT0IE = 1;  
      INTCON3bits.INT1IE = 1; 
      INTCON3bits.INT2IE = 1; 
       
      lcd_cmd(0x0C);
      x=0x10;
      while(1){
          if(check==0)
          {
          
             
          lcd_cmd(L_CLR) ;
          lcd_cmd(L_L1) ;
          lcd_str("     Menu    ") ;
          lcd_cmd(L_L2) ;
          lcd_str("     Malas   ") ;
          check=1;
          }
          PORTB=x;
          x=(x<<1);
          if(x==0)x=0x10;
          __delay_ms(40);

      }  

          

 }