#include <18F46K42.h>
#device ADC=12

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOEXTOSC                 //External Oscillator not enabled
#FUSES PUT_16MS              
#FUSES BORV28                   //Brownout reset at 2.8V

#use delay(internal=16MHz)
#use FIXED_IO( A_outputs=PIN_A2 )
#define LED   PIN_A2
#define BTN   PIN_B0

#use rs232(baud=19200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=LAPTOP)



