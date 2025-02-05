/* =========================================================================
    Unity - A Test Framework for C
    ThrowTheSwitch.org
    Copyright (c) 2007-24 Mike Karlesky, Mark VanderVoord, & Greg Williams
    SPDX-License-Identifier: MIT
========================================================================= */


/* #include "UART_RP2040.h" */
#include "UART_RP2040_Test.h"
#include "ComStack_Types.h"
#include "MemPool.h"
#include "unity.h"

#pragma ab

extern uint32 lastByteTransmitted;

void setUp(void)
{
    UART_Live = UART_Uninit;
}

/* 
  These are run after each test, so we want to make sure the global variable is 'UNINIT' 
  so that each test can behave as if its its own test. 
*/
void tearDown(void)
{
  MOCK_UART_PROCESS_TXFIFO();
  MemPool_ClearInternalMemPool();
}

/* HELPER FUNCTIONS */
void test_UART_InitSync_ReturnsOk(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  retVal = UART_RP2040_InitSync(&UART_RP2040_CFG);
  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_UART_InitSync_ReturnsNotOk_ConfigPointerNull(void)
{
  Std_ErrorCode retVal = E_OK;
  retVal = UART_RP2040_InitSync((UART_RP2040_Config *) NULL);
  TEST_ASSERT_EQUAL(E_NOT_OK, retVal);
}

void test_UART_InitSync_ReturnsNotOk_ConfigPointerIncompatible(void)
{
  Std_ErrorCode retVal = E_OK;
  
  UART_RP2040_Config badUARTConfig =
  {
    115000,
    12000000,
    0x70
  };
  retVal = UART_RP2040_InitSync(&badUARTConfig);
  TEST_ASSERT_EQUAL(E_NOT_OK, retVal);
}

void test_UART_InitSync_ReturnsOk_IBRD_FBRD_Correct(void)
{
  Std_ErrorCode retVal = E_NOT_OK;
  retVal = UART_RP2040_InitSync(&UART_RP2040_CFG);
  TEST_ASSERT_EQUAL(6, UART_Live.UARTIBRD);
  TEST_ASSERT_EQUAL(33, UART_Live.UARTFBRD);
  TEST_ASSERT_EQUAL(E_OK, retVal);
}

void test_UART_InitSync_ReturnsOk_LCR_CR_Correct(void)
{
  Std_ComErrorCode retVal = E_COM_UNKNOWN;
  retVal = UART_RP2040_InitSync(&UART_RP2040_CFG);
  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0x70, UART_Live.UARTLCR_H);
  TEST_ASSERT_EQUAL(0x101, UART_Live.UARTCR);

}

void test_UART_TransferSync_ReturnsOK(void)
{
  Std_ComErrorCode retVal = E_COM_UNKNOWN;
  retVal = UART_RP2040_InitSync(&UART_RP2040_CFG);
  uint8 buf[4] = {0xfa, 0xce, 0xbe, 0xef};
  retVal = UART_RP2040_TransferSync(buf, 4);
  MOCK_UART_PROCESS_TXFIFO();
  TEST_ASSERT_EQUAL(E_COM_OK, retVal);
}

void test_UART_TransferSync_ReturnsOK_TxDataIsBuffered(void)
{
  Std_ComErrorCode retVal = E_COM_UNKNOWN;
  retVal = UART_RP2040_InitSync(&UART_RP2040_CFG);
  uint8 buf[4] = {0xfa, 0xce, 0xbe, 0xef};
  retVal = UART_RP2040_TransferSync(buf, 4);
  MOCK_UART_PROCESS_TXFIFO();
  TEST_ASSERT_EQUAL(E_COM_OK, retVal);
  TEST_ASSERT_EQUAL(0xEF, lastByteTransmitted);
}

void test_UART_TransferSync_ReturnsNotOk_InputParamFailure_ZeroDataBytes(void)
{
  Std_ComErrorCode retVal = E_COM_UNKNOWN;
  retVal = UART_RP2040_InitSync(&UART_RP2040_CFG);
  uint8 buf[4] = {0xfa, 0xce, 0xbe, 0xef};
  retVal = UART_RP2040_TransferSync(buf, 0);
  TEST_ASSERT_EQUAL(E_COM_NOT_OK, retVal);
}

void test_UART_TransferSync_ReturnsNotOk_InputParamFailure_NULLbuffer(void)
{
  Std_ComErrorCode retVal = E_COM_UNKNOWN;
  retVal = UART_RP2040_InitSync(&UART_RP2040_CFG);
  uint8 * buf = NULL;
  retVal = UART_RP2040_TransferSync(buf, 4);
  TEST_ASSERT_EQUAL(E_COM_NOT_OK, retVal);
}

void test_UART_TransferSync_ReturnsBusy_TxFifoIsFull(void)
{
  Std_ComErrorCode retVal = E_COM_UNKNOWN;
  int i;
  uint8 buf[4] = {0xFA, 0xCE, 0xBE, 0xEF};
  retVal = UART_RP2040_InitSync(&UART_RP2040_CFG);
  for(i = 0; i < 32; i++)
  {
    retVal = UART_RP2040_TransferSync(&i, 1);
  }
  retVal = UART_RP2040_TransferSync(buf, 1);
  TEST_ASSERT_EQUAL(E_COM_BUSY, retVal);
  MOCK_UART_PROCESS_TXFIFO();
  TEST_ASSERT_EQUAL(0x1F, lastByteTransmitted);
}

void test_UART_TransferSync_ReturnsOK_1Byte(void)
{
  Std_ComErrorCode retVal = E_COM_UNKNOWN;
  uint8 buf[4] = {0xFA, 0xCE, 0xBE, 0xEF};
  retVal = UART_RP2040_InitSync(&UART_RP2040_CFG);
  retVal = UART_RP2040_TransferSync(buf, 1);
  MOCK_UART_PROCESS_TXFIFO();
  TEST_ASSERT_EQUAL(E_OK, retVal);
  TEST_ASSERT_EQUAL(0xFA, lastByteTransmitted);
}

void test_UART_TransferSync_ReturnsOK_8Byte(void)
{
  Std_ComErrorCode retVal = E_COM_UNKNOWN;
  uint8 buf[8] = {0xFA, 0xCE, 0xBE, 0xEF, 0xDE, 0xAD, 0xFA, 0xDE};

  retVal = UART_RP2040_InitSync(&UART_RP2040_CFG);
  retVal = UART_RP2040_TransferSync(buf, 8);
  MOCK_UART_PROCESS_TXFIFO();
  TEST_ASSERT_EQUAL(0xDE, lastByteTransmitted);
  TEST_ASSERT_EQUAL(E_OK, retVal);
}

/* void test_UART_TransferSync_ReturnsOK_ReceptionIsConfirmed(void)
{
  Std_ComErrorCode retVal = E_COM_UNKNOWN;
  uint8 buf[4] = {0xFA, 0xCE, 0xBE, 0xEF};

  retVal = UART_RP2040_InitSync(&UART_RP2040_CFG);
  retVal = UART_RP2040_TransferSync(buf, 0);
  retVal = E_COM_UNKNOWN;
  TEST_ASSERT_EQUAL(E_OK, retVal);
} */

void test_UART_TransferSync_ReturnsOK_TrasnferOneMillionMessages(void)
{
  Std_ComErrorCode retVal = E_COM_UNKNOWN;
  uint8 buf[4] = {0xFA, 0xCE, 0xBE, 0xEF};
  uint32 i = 0, j = 0;

  retVal = UART_RP2040_InitSync(&UART_RP2040_CFG);
  for(j = 0; j < 10000; j++)
  {
    for(i = 0; i < 256; i++)
    {
      retVal = UART_RP2040_TransferSync(&i, 1);
      (void)MOCK_UART_PROCESS_TXFIFO();  
      TEST_ASSERT_EQUAL(E_OK, retVal);
      TEST_ASSERT_EQUAL(i, lastByteTransmitted);
    }
  }
}

/* TESTS */