
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


/************************************************************
  DEFINES
************************************************************/
#define UART0_BASE                  0x40034000

#define UART0_BASE_UARTDR_RW        (UART0_BASE+0x000+0x0000)
#define UART0_BASE_UARTFR_RW        (UART0_BASE+0x018+0x0000)
#define UART0_BASE_UARTIBRD_RW      (UART0_BASE+0x024+0x0000)
#define UART0_BASE_UARTFBRD_RW      (UART0_BASE+0x028+0x0000)
#define UART0_BASE_UARTLCR_H_RW     (UART0_BASE+0x02C+0x0000)
#define UART0_BASE_UARTCR_RW        (UART0_BASE+0x030+0x0000)
/************************************************************
  INCLUDES
************************************************************/
#include "Reset_RP2040.h"
// #include "GPIO_RP2040.h"
#include "BRS_RP2040.h"
/************************************************************
  ENUMS AND TYPEDEFS
************************************************************/

/************************************************************
  EXTERN FUNCTIONS
************************************************************/

/************************************************************
  GLOBAL FUNCTIONS
************************************************************/

/**
 * @brief Adds all module init functions to the OS Init lists
 * 
 * @note Should be the only place to call OS_ADDINIT()
 */
extern void UART_RP2040_InitSync ( void );

extern void UART_RP2040_TransferSync ( uint32 dataToTransfer );
