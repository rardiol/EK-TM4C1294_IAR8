#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "driverlib/systick.h"
#include "driverleds.h" // Projects/drivers

// MEF com apenas 2 estados e 1 evento temporal que alterna entre eles
// Seleção por evento

typedef uint8_t state_t;

volatile uint8_t Evento = 0;

void SysTick_Handler(void){
  Evento = 1;
} // SysTick_Handler

void main(void){
  static state_t Estado = 0x00; // estado inicial da MEF
  
  LEDInit(LED1);
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();

  while(1){
    if(Evento){
      Evento = 0;
      switch(Estado){
        case 0x0:
          LEDOff(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          Estado = 0x1;
          break;
        case 0x1:
          LEDOn(LED1);
          Estado = 0x3;
          break;
        case 0x3:
          LEDOn(LED2);
          Estado = 0x2;
          break;       
        case 0x2:
          LEDOff(LED1);
          Estado = 0x6;
          break;          
        case 0x6:
          LEDOn(LED3);
          Estado = 0x7;
          break;          
        case 0x7:
          LEDOn(LED1);
          Estado = 0x5;
          break;          
        case 0x5:
          LEDOff(LED2);
          Estado = 0x4;
          break;
        case 0x4:
          LEDOff(LED1);
          Estado = 0x0;
          break;
      } // switch
    } // if
  } // while
} // main
