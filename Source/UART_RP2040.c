#include "UART_RP2040.h"
extern void uart_send ( unsigned int x );
#define RESETS_BASE                 0x4000C000

#define RESETS_RESET_RW             (RESETS_BASE+0x0000)
#define RESETS_RESET_XOR            (RESETS_BASE+0x1000)
#define RESETS_RESET_SET            (RESETS_BASE+0x2000)
#define RESETS_RESET_CLR            (RESETS_BASE+0x3000)

#define RESETS_WDSEL_RW             (RESETS_BASE+0x4+0x0000)
#define RESETS_WDSEL_XOR            (RESETS_BASE+0x4+0x1000)
#define RESETS_WDSEL_SET            (RESETS_BASE+0x4+0x2000)
#define RESETS_WDSEL_CLR            (RESETS_BASE+0x4+0x3000)

#define RESETS_RESET_DONE_RW        (RESETS_BASE+0x8+0x0000)
#define RESETS_RESET_DONE_XOR       (RESETS_BASE+0x8+0x1000)
#define RESETS_RESET_DONE_SET       (RESETS_BASE+0x8+0x2000)
#define RESETS_RESET_DONE_CLR       (RESETS_BASE+0x8+0x3000)

#define IO_BANK0_BASE               0x40014000

#define IO_BANK0_GPIO0_CTRL_RW      (IO_BANK0_BASE+0x004+0x0000)
#define IO_BANK0_GPIO0_CTRL_XOR     (IO_BANK0_BASE+0x004+0x1000)
#define IO_BANK0_GPIO0_CTRL_SET     (IO_BANK0_BASE+0x004+0x2000)
#define IO_BANK0_GPIO0_CTRL_CLR     (IO_BANK0_BASE+0x004+0x3000)

#define IO_BANK0_GPIO1_CTRL_RW      (IO_BANK0_BASE+0x00C+0x0000)
#define IO_BANK0_GPIO1_CTRL_XOR     (IO_BANK0_BASE+0x00C+0x1000)
#define IO_BANK0_GPIO1_CTRL_SET     (IO_BANK0_BASE+0x00C+0x2000)
#define IO_BANK0_GPIO1_CTRL_CLR     (IO_BANK0_BASE+0x00C+0x3000)

#define IO_BANK0_GPIO25_STATUS_RW   (IO_BANK0_BASE+0x0C8+0x0000)
#define IO_BANK0_GPIO25_STATUS_XOR  (IO_BANK0_BASE+0x0C8+0x1000)
#define IO_BANK0_GPIO25_STATUS_SET  (IO_BANK0_BASE+0x0C8+0x2000)
#define IO_BANK0_GPIO25_STATUS_CLR  (IO_BANK0_BASE+0x0C8+0x3000)

#define IO_BANK0_GPIO25_CTRL_RW     (IO_BANK0_BASE+0x0CC+0x0000)
#define IO_BANK0_GPIO25_CTRL_XOR    (IO_BANK0_BASE+0x0CC+0x1000)
#define IO_BANK0_GPIO25_CTRL_SET    (IO_BANK0_BASE+0x0CC+0x2000)

/************************************************************
  LOCAL VARIABLES
************************************************************/
#if defined ( VIRTUAL_TARGET )

const tRP2040_UART UART_Uninit = { 0 };

#endif /* VIRTUAL_TARGET */

static Std_ComErrorCode UART_RP2040_TransferByte ( uint8 byte )
{
    Std_ComErrorCode retVal = E_COM_UNKNOWN;
    uint8 timeout = 0xFF;

    /* consider that timeout could occur - we just loop through*/
    while(0 != ((*UART_REG_UARTFR)&(1<<5)) && (0 < timeout))
    {
        timeout--;
    }

    if(0 == timeout)
    {
        /* 
            either a timeout has occured, or the fifo is full so we are busy.
            busy makes more sense since FULL buffer indicates the bus is busy.
        */
        retVal = E_COM_BUSY;
    }
    else
    {
        /* FIFO has a slot, lets queue data to transmit */
        *UART_REG_UARTDR = byte;
        retVal = E_COM_OK;
#if defined( VIRTUAL_TARGET )
        UART_TRANSFERBYTE_CALLOUT();
#endif /* VIRTUAL_TARGET */
    }

    return retVal;
}

Std_ComErrorCode UART_RP2040_InitSync ( UART_RP2040_Config * config )
{
    Std_ComErrorCode retVal = E_COM_OK;
    if( NULL  == config )
    {
        retVal = E_COM_NOT_OK;
    }

    if( E_COM_OK == retVal )
    {
#if !defined( VIRTUAL_TARGET )
    Reset_RP2040_ReleaseReset(kRESET_RESETS_UART0);
#endif /* VIRTUAL_TARGET */

    /* 
        BRD = UARTCLK / (16 * BAUDRATE) = IBRD.FBRD
            BRD = 12,000,000 / (16 * 115200)
            BRD = 6.51041667
        IBRD = 6
        FBRD = 0.51041667 * 64 = 32.6666667 ~= 33
    */

    if( 115200 == config->baudrate )
    {
        if(12000000 == config->uartclk )
        {
            *UART_REG_UARTIBRD = 6;
            *UART_REG_UARTFBRD = 33;
        }
        else
        {
            /* in the case of no matching uartclk configuration, report a generic failure */
            retVal = E_COM_NOT_OK;
        }
    }
    else
    {
        /* in the case of no matching uartclk configuration, report a generic failure */
        retVal = E_COM_NOT_OK;
    }

    /* configure word length and fifo enable*/
    *UART_REG_UARTLCR_H = config->lineControlRegVal;
    /* Enable transmit and enable UART */
    *UART_REG_UARTCR = ((1<<8)|(1<<0));

#if !defined( VIRTUAL_TARGET )
    PUT32(IO_BANK0_GPIO0_CTRL_RW,2);    //UART TX
#endif /* !VIRTUAL_TARGET */
    }
    return retVal;
}

Std_ComErrorCode UART_RP2040_TransferSync ( uint8 * dataBuffer , uint8 length)
{
    Std_ComErrorCode retVal = E_COM_UNKNOWN;
    uint8 i;

    if( (0 == length) || (NULL == dataBuffer) )
    {
        retVal = E_COM_NOT_OK;
    }

    /* No error has been detected so far - we can attempt transmission */
    for(i = 0; i < length; i++)
    {
        if((E_COM_UNKNOWN == retVal) || (E_COM_OK == retVal))
        {
            retVal = UART_RP2040_TransferByte(dataBuffer[i]);
        }
    }

    return retVal;
}

