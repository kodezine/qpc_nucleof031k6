#include <stdbool.h>
#include "main.h"
#include "SEGGER_RTT.h"
uint8_t addOneToByte(const uint8_t byte)
{
    return(byte + 1);
}

void delayMe(void)
{
    for (int i = 0; i < 5000; i++)
    {
        asm("nop");
    }
}

void SystemInit(void)
{

}
int main (void)
{
    SEGGER_RTT_Init();
    
  SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

  SEGGER_RTT_WriteString(0, "SEGGER Real-Time-Terminal Sample\r\n\r\n");
    SystemInit();
    do{
        addOneToByte(1);
          SEGGER_RTT_WriteString(0, "SEGGER Real-Time-Terminal Sample\r\n\r\n");
          delayMe();

    }while(true);
    return 0;
}