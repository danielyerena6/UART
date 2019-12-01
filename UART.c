#include <UART.h>
#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D3
#define LCD_DATA5 PIN_D4
#define LCD_DATA6 PIN_D5
#define LCD_DATA7 PIN_D6

#include <lcd.c>
#include <string.h>
#include <stdlib.h>
int1 flag=0;

      char escritura[100];
     
      int8 i=0;

void menu()
{  
   
   printf("\f   TEST UART MAIN MENU");
   printf("\n\n\n   Choose an option:");
   printf("\n\n   a. Turn ON Led.");
   printf("\n\n   b. Turn OFF  Led.");
   printf("\n\n   c. Print Menu.");
   printf("\n\n   d. Read Voltage.");
   printf("\n\n   e. Read Button State.");
   printf("\n\n   f. Writte LCD.");
   



}

void get_temperature()
{
  int i;
  int16 ADC_VAL = 0;
  float temp;
  
  for(i=0; i<16; i++)
  {
    delay_ms(31);
    ADC_VAL += read_adc();
  }
  ADC_VAL /= 16;    //Average
  temp = (float)ADC_VAL * 0.0009157;  //Input voltage
  temp *= -1.2;  //K
  temp -= -5; //C
  
   fprintf(LAPTOP,"\f\n\n Digital");  
   fprintf(LAPTOP,"\n Voltage");
   fprintf(LAPTOP,"\n %1.2f",temp);  
   delay_ms(1000);
  
}

void button()
{
   int1 boton=input(BTN);
   fprintf(LAPTOP,"\f\n\n Button state");  
   fprintf(LAPTOP,"\n    %d",boton);





}



void LCDMenu()
{
         printf("\f   LCD MAIN MENU");
         printf("\n\n\n   Choose an option:");
         printf("\n\n   '*'. Back to Menu");
         printf("\n\n   '+'. Clean Screen.");
         printf("\n\n   '~'. Line break.");
         printf("\n\n   '.'. Exit.");


}


void LCD()
{
         
         i=0;
         printf("\f   LCD MAIN MENU");
         printf("\n\n\n   Choose an option:");
         printf("\n\n   '*'. Back to Menu");
         printf("\n\n   '+'. Clean Screen.");
         printf("\n\n   '~'. Line break.");
         printf("\n\n   '.'. Exit.");
         
         fprintf(LAPTOP,"\n\n Escribe");
      
      
      
      char escritura[100];
     
      int8 i=0;
      fprintf(LAPTOP,"\n\n Escribiendo");
      printf(lcd_putc,"\f Texto: ");
      
      while(1)
      {
      escritura[i]=getc();
      fprintf(LAPTOP," %c ",escritura[i]);
      printf(lcd_putc,"%c",escritura[i]);
      
      if(escritura[i]=='*')
      {LCDMenu();i=0;}
      
      if(escritura[i]=='+')
      {printf(lcd_putc,"\f");i=0;}
      
      if(escritura[i]=='~')
      {printf(lcd_putc,"\n");i=0;}
      
      if(escritura[i]=='.')
      {break;}
      i++;
      }
      
      
      
      
      
      
     /* for(int j=0;j<i;j++)
      {
         if(escritura[j]=='*' || escritura[j]=='+' || escritura[j]=='~' || escritura[j]=='.')
         {break;}
         printf(lcd_putc,"%c",escritura[j]);
      
      }*/
      menu();
      
   
   
}






void main()
{

  char dummy1,rx_data;
    
   setup_adc_ports(sAN0);
   setup_adc(ADC_AVERAGE_MODE|ADC_CLOCK_DIV_16|ADC_TAD_MUL_0|ADC_ADFLTR_TO_ADPREV_AT_START|ADC_THRESHOLD_INT_DISABLED);
   output_low(LED);
   lcd_init();
   delay_ms(100);
   printf(lcd_putc,"\f UART TEST!  :)");
    
   if(kbhit())
   {
     dummy1 = getc();
   }
    
   delay_ms(1000);
    
   //Print menu on screen
    menu();
    
   while(TRUE)
   {
     if(flag)
     {lcd();}
     if(kbhit())
     {
       rx_data = getchar();
      
       switch(rx_data)
       {
         case 'a':
           output_high(LED);
           printf("\n LED is ON :)");
         break;
      
         case 'b':
           output_low(LED);
           printf("\n LED is OFF :(");
         break;
         
         
         case 'c':
           menu();
         break;
         
         
         case 'd':
            get_temperature();
         break;
         
         case 'e':
            button();
         break;
         
         case 'f':
            LCD();
         break;
         
         
        
         default:
           fprintf(LAPTOP,"\n You have chosen an invalid option!\n %c",rx_data);  
         break;
       }
     }  
   }
}


