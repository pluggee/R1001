/*
 * BL_functions.h
 *
 *  Created on: Feb 12, 2017
 *      Author: sherifeid
 */

#include <compiler_defs.h>

#ifndef BL_FUNCTIONS_H_
#define BL_FUNCTIONS_H_

// Specify 24-bit linear addresses here (do not use banked 16-bit addresses)
#define APP_FW_START_ADDR       0x0400
#define APP_FW_END_ADDR         0x1DFF              // last address of application firmware

// FW signature address
#define APP_FW_SIG0_ADDR        APP_FW_END_ADDR

// Signature Bytes
#define SIG_BYTE0               0x3D
#define SIG_BYTE1               0xC2
#define SIG_BYTE2               0xA5
#define SIG_BYTE3               0x1B

// ---------------------------------
// Boot Loader Command Codes
// ---------------------------------
#define TGT_CMD_RESET_MCU           0x00
#define TGT_CMD_GET_VERSION         0x01
#define TGT_CMD_ERASE_FLASH_PAGE    0x02
#define TGT_CMD_WRITE_FLASH_BYTES   0x03
#define TGT_CMD_READ_FLASH_BYTES    0x04
#define TGT_CMD_ENTER_BL_MODE       0x05

// ---------------------------------
// Target BL Response Codes
// ---------------------------------
#define TGT_RSP_OK                  0x00 // RSP_OK should always be 0
#define TGT_RSP_PARAMETER_INVALID   0x01
#define TGT_RSP_UNSUPPORTED_CMD     0x02
#define TGT_RSP_BL_MODE             0x03
#define TGT_RSP_ERROR               0x80
#define TGT_RSP_ADDR_INVALID        0x81 // added by Juicyboard, invalid address to flash, write or read

// bootloader response functions
void Set_TX_TGT_RSP_OK(void);
void Set_TX_TGT_RSP_BL_MODE(void);
void Set_TX_TGT_RSP_UNSUPPORTED_CMD (void);
void TGT_Pre_Flash(void);
void TGT_Erase_Page(void);
void TGT_Write_Flash(void);
void TGT_Read_Flash(void);

bool ValidAppAddr(U16);

extern U8 Flash_Key0;
extern U8 Flash_Key1;

#endif /* BL_FUNCTIONS_H_ */
