
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
#ifndef UART_RP2040_H
#define UART_RP2040_H

/************************************************************
  DEFINES
************************************************************/
/************************************************************
  INCLUDES
************************************************************/

#include "Reset_RP2040.h"
#include "BRS_RP2040.h"
#include "ComStack_Types.h"
#include "UART_RP2040_SFR.h"
#include "UART_RP2040_cfg.h"

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
 * Initializes the UART according to the UART_RP2040_Config structure. Initializes the UART Baudrate and Control registers
 *  Prepares the UART for Transmissiona AND reception. Assumes that the clock path is already prepared for the UART peripheral.
 * 
 * @param config: initial config for the UART peripheral, including baudrate and clock configurations.
 * @return 
 *         0: 'E_COM_OK' if the initialization is successful
 *         1: 'E_COM_NOT_OK' if the initialization is not successful, typically due to misconfigured configuration struct
 *
 * @pre  Clockpaths to UART are already initialized.
 * @post n/a
 * @invariant n/a
 *
 */
extern Std_ComErrorCode UART_RP2040_InitSync( UART_RP2040_Config * config );

/**
 * Transmits data given to the UART peripheral hardware. Stores the data into the TxFifo. In the case that
 *  Data can not fit in the TxFifo (i.e. because the TxFifos are not flushing in time), reports E_COM_BUSY.
 * 
 * @param databuffer: pointer to bytes to be transferred on the UART.
 * @param length: number of bytes to transfer on UART from the buffer. UINT8 -> Maximum of 255 bytes to transfer.
 * @return 
 *         0: 'E_COM_OK' if the Transfer is successful
 *         1: 'E_COM_NOT_OK' if the Transfer is not successful, typically due to unsupported input parameters
 *         2: 'E_COM_BUSY' if the FIFO is full and it is not possible to add the data to the FIFO.
 *      0xFF: 'E_COM_UNKNOWN' in the case of early return from subfunction. Default return value, but should be overwritten.
 *
 * @pre  UART is initialized.
 * @post n/a
 * @invariant n/a
 *
 */
extern Std_ComErrorCode UART_RP2040_TransferSync ( uint8 * buffer, uint8 length);

#endif /* UART_RP2040_H */

