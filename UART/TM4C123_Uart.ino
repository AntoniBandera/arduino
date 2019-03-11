#include "tm4c123gh6pm.h"
void UART_Init(void){            // should be called only once
  SYSCTL_RCGC1_R |= 0x00000002;  // activate UART1
  SYSCTL_RCGC2_R |= 0x00000004;  // activate port C
  UART1_CTL_R &= ~0x00000001;    // disable UART
  UART1_IBRD_R = 43;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
  UART1_FBRD_R = 26;     // FBRD = round(0.40278 * 64) = 26
  UART1_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
  UART1_CTL_R |= 0x00000001;     // enable UART
  GPIO_PORTC_AFSEL_R |= 0x30;    // enable alt funct on PC5-4
  GPIO_PORTC_DEN_R |= 0x30;      // configure PC5-4 as UART1
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;
  GPIO_PORTC_AMSEL_R &= ~0x30;   // disable analog on PC5-4
}

// Immediately return input or 0 if no input
unsigned char UART_InCharNonBlocking(void){
      if((UART1_FR_R&UART_FR_RXFE) == 0){
          return((unsigned char)(UART1_DR_R&0xFF));
      } else{
          return 0;
      }

}
void initGPIOF(void) {
    SYSCTL_RCGCGPIO_R |=0x20; //active clock on port F
    GPIO_PORTF_DIR_R |= 0x0E; //set PF1-3 as output
    GPIO_PORTF_AFSEL_R &= ~0x0E; //disable alternative function on PF1-33
    GPIO_PORTF_PCTL_R &= ~0x0E;  //configure PF1-3 as GPIO
    GPIO_PORTF_DEN_R |= 0x0E; //enable PF1-3 as digital I/Os
    GPIO_PORTF_AMSEL_R &= ~0x0E; //disable analogue function on PF1-3
}


int main(void){
    initGPIOF();
    UART_Init();             // initialize UART
    unsigned char data = UART_InCharNonBlocking();
    while(1)
    {
       if(data){ // new data have come in from the UART??
              GPIO_PORTF_DATA_R |= 0x02; // update this computer's color
              delay(100);
              GPIO_PORTF_DATA_R &= ~0x02; // update this computer's color
        }
    }
}
