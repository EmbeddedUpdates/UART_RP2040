
/**
 * @file UART_RP2040.h
 * @author pflaherty
 * @date 01.13.2024
 * @brief 
 * 
 * COMPONENT: UART_RP2040
 * VERSION: 01.01.00
 *
 * Change History
 * 01.13.2024 - Initial Creation
 */
#ifndef UART_RP2040_CFG_H
#define UART_RP2040_CFG_H

/************************************************************
  DEFINES
************************************************************/
/************************************************************
  INCLUDES
************************************************************/
#include "Platform_Types.h"
/************************************************************
  ENUMS AND TYPEDEFS
************************************************************/
typedef struct UART_RP2040_Config_tag
{
  uint32 baudrate;
  uint32 uartclk;
  uint8 lineControlRegVal;
} UART_RP2040_Config;

extern UART_RP2040_Config UART_RP2040_CFG;


#if defined( VIRTUAL_TARGET )
#define UART_TRANSFERBYTE_CALLOUT MOCK_UART_PROCESS_UARTDR
extern void UART_TRANSFERBYTE_CALLOUT(void);
#endif /* !VIRTUAL_TARGET */

#if defined( UART_TRANSFERBYTE_CALLOUT )
extern void UART_TRANSFERBYTE_CALLOUT(void);
#endif

/************************************************************
  EXTERN FUNCTIONS
************************************************************/

/************************************************************
  GLOBAL FUNCTIONS
************************************************************/

#endif /* UART_RP2040_CFG_H */

