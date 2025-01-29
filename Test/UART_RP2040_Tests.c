/* =========================================================================
    Unity - A Test Framework for C
    ThrowTheSwitch.org
    Copyright (c) 2007-24 Mike Karlesky, Mark VanderVoord, & Greg Williams
    SPDX-License-Identifier: MIT
========================================================================= */


/* #include "UART_RP2040.h" */
#include "UART_RP2040_Test.h"
#include "unity.h"

#pragma ab

void setUp(void)
{
}

/* 
  These are run after each test, so we want to make sure the global variable is 'UNINIT' 
  so that each test can behave as if its its own test. 
*/
void tearDown(void)
{

}

/* HELPER FUNCTIONS */

void printJustOneMember(unsigned int * member, char * memberName)
{
  printf("%s address: %#010x\n", memberName, member);
  printf("%s value: %#010x\n", memberName, *member);
}

void printUARTLive(void)
{
  printf("\n");
  // printf("Timer_Live:\n");
  // printJustOneMember((unsigned int *)&Timer_Live, "Timer_Live");
  // printJustOneMember(&Timer_Live.TIMEHW, "Timer_Live_TIMEHW");
  // printJustOneMember(&Timer_Live.TIMELW, "Timer_Live_TIMELW");
  // printJustOneMember(&Timer_Live.TIMEHR, "Timer_Live_TIMEHR");
  // printJustOneMember(&Timer_Live.TIMELR, "Timer_Live_TIMELR");
  // printJustOneMember(&Timer_Live.ALARM0, "Timer_Live_ALARM0");
  // printJustOneMember(&Timer_Live.ALARM1, "Timer_Live_ALARM1");
  // printJustOneMember(&Timer_Live.ALARM2, "Timer_Live_ALARM2");
  // printJustOneMember(&Timer_Live.ALARM3, "Timer_Live_ALARM3");
  // printJustOneMember(&Timer_Live.INTS, "Timer_Live_INTS");
  printf("\n");
}

/* TESTS */