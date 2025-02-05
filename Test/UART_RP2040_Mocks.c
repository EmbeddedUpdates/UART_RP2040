
/**
 * @file UART_RP2040_Mocks.c
 * @author pflaherty
 * @date 02.03.2024
 * @brief 
 * 
 * COMPONENT: UART_RP2040
 * VERSION: 01.01.00
 *
 * Change History
 * Feb.03.2024 - Initial Creation for mocks
 */

/************************************************************
  DEFINES
************************************************************/

/************************************************************
  INCLUDES
************************************************************/
#include "UART_RP2040.h"
#include "RingBuffer.h"
#include <stdio.h>

/************************************************************
  ENUMS AND TYPEDEFS
************************************************************/

/************************************************************
  EXTERN FUNCTIONS
************************************************************/
/************************************************************
  LOCAL VARIABLES
************************************************************/
RingBuffer txFifo;
uint8 lastByteTransmitted = 0x0;

/************************************************************
  GLOBAL FUNCTIONS
************************************************************/
static void printJustOneMember(unsigned int * member, char * memberName)
{
  printf("%s address: %p\n", memberName, member);
  printf("%s value: %p\n", memberName, *member);
}

void printUARTLive(tRP2040_UART * uart)
{
  printf("\n");
  printf("Timer_Live:\n");
  printJustOneMember((unsigned int *)uart, "UART_LIVE");
  printJustOneMember(&uart->UARTDR, "UARTDR");
  printJustOneMember(&uart->UARTRSR, "UARTRSR");
  printJustOneMember(&uart->UARTFR, "UARTFR");
  printJustOneMember(&uart->UARTILPR, "UARTILPR");
  printJustOneMember(&uart->UARTIBRD, "UARTIBRD");
  printJustOneMember(&uart->UARTFBRD, "UARTFBRD");
  printJustOneMember(&uart->UARTLCR_H, "UARTLCR_H");
  printJustOneMember(&uart->UARTCR, "UARTCR");
  printJustOneMember(&uart->UARTIFLS, "UARTIFLS");
  printJustOneMember(&uart->UARTIMSC, "UARTIMSC");
  printJustOneMember(&uart->UARTRIS, "UARTRIS");
  printJustOneMember(&uart->UARTMIS, "UARTMIS");
  printJustOneMember(&uart->UARTICR, "UARTICR");
  printJustOneMember(&uart->UARTDMACR, "UARTDMACR");
  printJustOneMember(&uart->UARTPERIPHID0, "UARTPERIPHID0");
  printJustOneMember(&uart->UARTPERIPHID1, "UARTPERIPHID1");
  printJustOneMember(&uart->UARTPERIPHID2, "UARTPERIPHID2");
  printJustOneMember(&uart->UARTPERIPHID3, "UARTPERIPHID3");
  printJustOneMember(&uart->UARTPCELLID0, "UARTPCELLID0");
  printJustOneMember(&uart->UARTPCELLID1, "UARTPCELLID1");
  printJustOneMember(&uart->UARTPCELLID2, "UARTPCELLID2");
  printJustOneMember(&uart->UARTPCELLID3, "UARTPCELLID3");
  printf("\n");
}

uint8 MOCK_UART_PROCESS_TXFIFO(void)
{
  uint8 readBuffer = 0x0;
  while(txFifo.count > 0)
  {
    txFifo.read(&txFifo, &readBuffer, 1);
    /*printf("Transmitted %x\n", readBuffer);*/
    UART_Live.UARTFR = UART_Live.UARTFR & ~(1<<5);
  }
  lastByteTransmitted = readBuffer;
  return lastByteTransmitted;
}

void MOCK_UART_PROCESS_UARTDR(void)
{
  if(txFifo.count < txFifo.capacity)
  {
    if(E_NOT_OK == txFifo.write(&txFifo, (uint8 *)&UART_Live.UARTDR, 1))
    {
      printf("transmit failed\n");
    }
    else
    {
      /* printf("queued: %x\n", (*(&UART_Live.UARTDR))); */
      UART_Live.UARTDR &= 0xFFFFFF00; /* simulate clearing of data to transmit */
      if(txFifo.count == 32)
        UART_Live.UARTFR |= (1 << 5);
    }
    ;
  }
}

void MOCK_UART_UPDATE(void)
{
    MOCK_UART_PROCESS_UARTDR(); /* Transmit the current message */
    (void)MOCK_UART_PROCESS_TXFIFO(); /* put the current message on the 'bus', flush the fifo */
}

void MOCK_UART_INIT(void)
{
    Std_ErrorCode retVal = E_NOT_OK;
    retVal = RingBuffer_Create(&txFifo, 1, 32);
    while(E_OK != retVal);
}

/* 
features of real uart 

1. TX and RX FIFOs
2. programmable baud rate generator
    The UART operation and baud rate values are controlled by the Line Control Register, UARTLCR_H and the baud rate
    divisor registers (Integer Baud Rate Register, UARTIBRD and Fractional Baud Rate Register, UARTFBRD).



3. line break detection
4. 5,6,7,8 bit length for serial interface
5. 1 or 2 stop bits
6. programmable hardware flow control
7. individually maskable interrupts from the RX (timeout, transmit, modem status, error)
    7.a also combined interrupt for ambove cases
8. DMA rx signals for interfacing with a DMA controller
9. If a framing, parity, or break error occurs during reception, the appropriate error bit is set, and is stored in the FIFO. 
    If an overrun condition occurs, the overrun register bit is set immediately and FIFO data is prevented from being overwritten.

*/