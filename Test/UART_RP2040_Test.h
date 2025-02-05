/**
 * 
* @file "UART_RP2040_Test.h"
* @author Madrick3
* @brief UART peripheral abstraction for RP2040
* 
* @COMPONENT: UART
* @VERSION: 01.00.00
*/
/************************************************************
  Version History
  -----------------------------------------------------------
  Revision |  Author   |  Change ID  |  Description
  01.00.00 |  Madrick3 |  Skeleton   |  Initial Creation
************************************************************/

#ifndef UART_TEST_H
#define UART_TEST_H
/************************************************************
  INCLUDES
************************************************************/
#include "UART_RP2040.h"

#define MOCK_UART_TRANSFERBYTE_CALLOUT MOCK_UART_PROCESS_UARTDR


/************************************************************
  EXTERNAL FUNCTION DECLARATIONS
************************************************************/

extern const tRP2040_UART UART_Uninit;
extern volatile tRP2040_UART UART_Live;

extern void printUARTLive(tRP2040_UART * uart);
extern void MOCK_UART_INIT(void);
extern void MOCK_UART_UPDATE(void);
extern uint32 MOCK_UART_PROCESS_TXFIFO(void);
extern void MOCK_UART_PROCESS_UARTDR(void);

extern void test_UART_InitSync_ReturnsOk(void);
extern void test_UART_InitSync_ReturnsNotOk_ConfigPointerNull(void);
extern void test_UART_InitSync_ReturnsNotOk_ConfigPointerIncompatible(void);
extern void test_UART_InitSync_ReturnsOk_IBRD_FBRD_Correct(void);
extern void test_UART_InitSync_ReturnsOk_LCR_CR_Correct(void);

extern void test_UART_TransferSync_ReturnsOK(void);
extern void test_UART_TransferSync_ReturnsOK_TxDataIsBuffered(void);
extern void test_UART_TransferSync_ReturnsNotOk_InputParamFailure_ZeroDataBytes(void);
extern void test_UART_TransferSync_ReturnsNotOk_InputParamFailure_NULLbuffer(void);
extern void test_UART_TransferSync_ReturnsBusy_TxFifoIsFull(void);
extern void test_UART_TransferSync_ReturnsOK_1Byte(void);
extern void test_UART_TransferSync_ReturnsOK_8Byte(void);
/* extern void test_UART_TransferSync_ReturnsOK_ReceptionIsConfirmed(void); */
extern void test_UART_TransferSync_ReturnsOK_TrasnferOneMillionMessages(void);

/************************************************************
  LOCAL VARIABLES
************************************************************/

/************************************************************
  LOCAL FUNCTIONS
************************************************************/

#endif /* UART_TEST_H */