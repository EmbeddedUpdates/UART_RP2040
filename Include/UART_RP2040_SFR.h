/**
 * 
* @file "UART_RP2040.h"
* @author Madrick3
* @brief Provides a single layer abstraction over the UART peripheral interface of the RP2040 microcontroller.
* 
* @COMPONENT: UART_RP2040
* @VERSION: 00.01.00 
*/
/************************************************************
  Version History
  -----------------------------------------------------------
  Revision |  Author   |  Change ID  |  Description
  00.00.00 |  AUTHOR   |  DRAFT      |  Initial Creation
************************************************************/

#ifndef UART_SFR_H
#define UART_SFR_H
/************************************************************
  INCLUDES
************************************************************/
#include "Platform_Types.h"

/************************************************************
  DEFINES
************************************************************/
#if defined (RP2040)
#define SFR_IOS(x) ((unsigned int *)(x))
#endif /* VIRTUAL TARGET*/
#if defined (VIRTUAL_TARGET)
/* Virtual target has a 64 bit memory address which is marked as type long */
#define SFR_IOS(x) ((unsigned long *)(x))
#endif /* VIRTUAL TARGET*/

#if !defined( VIRTUAL_TARGET )
/* Base Register Address */
#define UART_BASE0                      0x40034000  /* d 1074085888 */
#define UART_BASE UART_BASE0
// #define UART_BASE1                      0x40038000  /* d 1074085888 */

#else /* VIRTUAL TARGET */

typedef struct vtt_RP2040_UART
{
  uint32 UARTDR;
  uint32 UARTRSR;
  uint8 reserved0[0x10];
  uint32 UARTFR;
  uint8 reserved1[4];
  uint32 UARTILPR;
  uint32 UARTIBRD;
  uint32 UARTFBRD;
  uint32 UARTLCR_H;
  uint32 UARTCR;
  uint32 UARTIFLS;
  uint32 UARTIMSC;
  uint32 UARTRIS;
  uint32 UARTMIS;
  uint32 UARTICR;
  uint32 UARTDMACR;
  uint8 reserved2[0xF94];
  uint32 UARTPERIPHID0;
  uint32 UARTPERIPHID1;
  uint32 UARTPERIPHID2;
  uint32 UARTPERIPHID3;
  uint32 UARTPCELLID0;
  uint32 UARTPCELLID1;
  uint32 UARTPCELLID2;
  uint32 UARTPCELLID3;
} tRP2040_UART;
/* Virtual Target has 64 bit word size and must be casted as such to accomodate virtual access */
#define UART_BASE (uint64)&UART_Live
#endif /* VIRTUAL_TARGET */

#define UART_REG_UARTDR_OFFSET          0x0000
#define UART_REG_UARTRSR_OFFSET         0x0004
#define UART_REG_UARTFR_OFFSET          0x0018
#define UART_REG_UARTILPR_OFFSET        0x0020
#define UART_REG_UARTIBRD_OFFSET        0x0024
#define UART_REG_UARTFBRD_OFFSET        0x0028
#define UART_REG_UARTLCR_H_OFFSET       0x002C
#define UART_REG_UARTCR_OFFSET          0x0030
#define UART_REG_UARTIFLS_OFFSET        0x0034
#define UART_REG_UARTIMSC_OFFSET        0x0038
#define UART_REG_UARTRIS_OFFSET         0x003C
#define UART_REG_UARTMIS_OFFSET         0x0040
#define UART_REG_UARTICR_OFFSET         0x0044
#define UART_REG_UARTDMACR_OFFSET       0x0048
#define UART_REG_UARTPERIPHID0_OFFSET   0x0FE0
#define UART_REG_UARTPERIPHID1_OFFSET   0x0FE4
#define UART_REG_UARTPERIPHID2_OFFSET   0x0FE8
#define UART_REG_UARTPERIPHID3_OFFSET   0x0FEC
#define UART_REG_UARTPCELLID0_OFFSET    0x0FF0
#define UART_REG_UARTPCELLID1_OFFSET    0x0FF4
#define UART_REG_UARTPCELLID2_OFFSET    0x0FF8
#define UART_REG_UARTPCELLID3_OFFSET    0x0FFC

#define UART_REG_UARTDR         SFR_IOS(UART_BASE + UART_REG_UARTDR_OFFSET)
#define UART_REG_UARTRSR        SFR_IOS(UART_BASE + UART_REG_UARTRSR_OFFSET)
#define UART_REG_UARTFR         SFR_IOS(UART_BASE + UART_REG_UARTFR_OFFSET)
#define UART_REG_UARTILPR       SFR_IOS(UART_BASE + UART_REG_UARTILPR_OFFSET)
#define UART_REG_UARTIBRD       SFR_IOS(UART_BASE + UART_REG_UARTIBRD_OFFSET)
#define UART_REG_UARTFBRD       SFR_IOS(UART_BASE + UART_REG_UARTFBRD_OFFSET)
#define UART_REG_UARTLCR_H      SFR_IOS(UART_BASE + UART_REG_UARTLCR_H_OFFSET)
#define UART_REG_UARTCR         SFR_IOS(UART_BASE + UART_REG_UARTCR_OFFSET)
#define UART_REG_UARTIFLS       SFR_IOS(UART_BASE + UART_REG_UARTIFLS_OFFSET)
#define UART_REG_UARTIMSC       SFR_IOS(UART_BASE + UART_REG_UARTIMSC_OFFSET)
#define UART_REG_UARTRIS        SFR_IOS(UART_BASE + UART_REG_UARTRIS_OFFSET)
#define UART_REG_UARTMIS        SFR_IOS(UART_BASE + UART_REG_UARTMIS_OFFSET)
#define UART_REG_UARTICR        SFR_IOS(UART_BASE + UART_REG_UARTICR_OFFSET)
#define UART_REG_UARTDMACR      SFR_IOS(UART_BASE + UART_REG_UARTDMACR_OFFSET)
#define UART_REG_UARTPERIPHID0  SFR_IOS(UART_BASE + UART_REG_UARTPERIPHID0_OFFSET)
#define UART_REG_UARTPERIPHID1  SFR_IOS(UART_BASE + UART_REG_UARTPERIPHID1_OFFSET)
#define UART_REG_UARTPERIPHID2  SFR_IOS(UART_BASE + UART_REG_UARTPERIPHID2_OFFSET)
#define UART_REG_UARTPERIPHID3  SFR_IOS(UART_BASE + UART_REG_UARTPERIPHID3_OFFSET)
#define UART_REG_UARTPCELLID0   SFR_IOS(UART_BASE + UART_REG_UARTPCELLID0_OFFSET)
#define UART_REG_UARTPCELLID1   SFR_IOS(UART_BASE + UART_REG_UARTPCELLID1_OFFSET)
#define UART_REG_UARTPCELLID2   SFR_IOS(UART_BASE + UART_REG_UARTPCELLID2_OFFSET)
#define UART_REG_UARTPCELLID3   SFR_IOS(UART_BASE + UART_REG_UARTPCELLID3_OFFSET)

/************************************************************
  ENUMS AND TYPEDEFS
************************************************************/

/************************************************************
  EXTERN FUNCTIONS
************************************************************/

/************************************************************
  GLOBAL FUNCTIONS
************************************************************/

#endif /* TEMPLATE_SFR_H */ 
