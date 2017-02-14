/*
 * BL_functions.c
 *
 *  Created on: Feb 12, 2017
 *      Author: sherifeid
 */

#include "BL_functions.h"
#include <compiler_defs.h>
#include "R1001_bl_main.h"
#include <SI_EFM8BB1_Defs.h>
#include "EFM8BB1_FlashPrimitives.h"

U8 Flash_Key0;
U8 Flash_Key1;

//-----------------------------------------------------------------------------
// Set_TX_TGT_RSP_OK
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Sets TX response code to TGT_RSP_OK.
//-----------------------------------------------------------------------------
void Set_TX_TGT_RSP_OK(void)
{
    SMB_DATA_OUT[0] = TGT_RSP_OK;
}

//-----------------------------------------------------------------------------
// Set_TX_TGT_RSP_BL_MODE
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Sets TX response code to TGT_RSP_BL_MODE.
//-----------------------------------------------------------------------------
void Set_TX_TGT_RSP_BL_MODE(void)
{
    SMB_DATA_OUT[0] = TGT_RSP_BL_MODE;
}

//-----------------------------------------------------------------------------
// Set_TX_TGT_RSP_UNSUPPORTED_CMD
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Sets TX response code to Set_TX_TGT_RSP_UNSUPPORTED_CMD.
//-----------------------------------------------------------------------------
void Set_TX_TGT_RSP_UNSUPPORTED_CMD (void)
{
    SMB_DATA_OUT[0] = TGT_RSP_UNSUPPORTED_CMD;
}

//-----------------------------------------------------------------------------
// Set_TX_TGT_RSP_ADDR_INVALID
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Sets TX response code to Set_TX_TGT_RSP_ADDR_INVALID.
//-----------------------------------------------------------------------------
void Set_TX_TGT_RSP_ADDR_INVALID (void)
{
    // Invalid application address
    SMB_DATA_OUT[0] = TGT_RSP_ADDR_INVALID;
}

//-----------------------------------------------------------------------------
// TGT_Pre_Flash
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Gets the FLKEY code out of Rx_Buf and clears Rx_Buf to help prevent flash
// corruption.
//-----------------------------------------------------------------------------
void TGT_Pre_Flash(void)
{
    // Store relevant information
    Flash_Key0 = SMB_DATA_IN[1];
    Flash_Key1 = SMB_DATA_IN[2];
    SMB_DATA_IN[1] = 0;
    SMB_DATA_IN[2] = 0;
}


//-----------------------------------------------------------------------------
// TGT_Erase_Page
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Erases one page of flash.
//-----------------------------------------------------------------------------
void TGT_Erase_Page(void)
{
    // Command Format:
    // [0] Command
    // [1] flash key code0
    // [2] flash key code1
    // [3] addr0 (LSB)
    // [4] addr1 (MSB)
    // [5] N/A

    // Response:
    // [0] Response code

    UU16 FlashAddr;
    FlashAddr.U8[LSB] = SMB_DATA_IN[3];
    FlashAddr.U8[MSB] = SMB_DATA_IN[4];

    // Address out-of-bounds
    // Setup for flash operation
    TGT_Pre_Flash();

    if (ValidAppAddr(FlashAddr.U16))
    {
        Set_TX_TGT_RSP_OK();
        FLASH_PageErase(FlashAddr.U16);         // execute page erase
    }
    else
    {
        Set_TX_TGT_RSP_ADDR_INVALID();
    }
}

//-----------------------------------------------------------------------------
// TGT_Write_Flash
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Writes 1 - 32 bytes of flash.
//-----------------------------------------------------------------------------
void TGT_Write_Flash(void)
{
    // Command Format:
    // [0] Command
    // [1] flash key code0
    // [2] flash key code1
    // [3] addr0 (LSB)
    // [4] addr1 (MSB)
    // [5] numbytes

    // Bytes to write:
    // [0] byte0
    // [1] byte1
    // [.] ...
    // [numbytes-1] byte(numbytes-1)

    // Response:
    // [0] Response code

    UU16 start_addr;
    U8 numbytes;
    U8 data * Rx_Buf_ptr = &SMB_DATA_IN[6];

    start_addr.U8[LSB] = SMB_DATA_IN[3];
    start_addr.U8[MSB] = SMB_DATA_IN[4];
    numbytes = SMB_DATA_IN[5];

    // Setup for flash operation
    TGT_Pre_Flash();

    // check for the whole range of address
    if (ValidAppAddr(start_addr.U16) & ValidAppAddr(start_addr.U16 + numbytes))
    {
        while (numbytes--)
        {
            FLASH_ByteWrite(start_addr.U16, *(Rx_Buf_ptr));

            Rx_Buf_ptr++;
            start_addr.U16++;
        }
        Set_TX_TGT_RSP_OK();
    }
    else
    {
        Set_TX_TGT_RSP_ADDR_INVALID();
    }
}

//-----------------------------------------------------------------------------
// TGT_Read_Flash
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Reads 1 - 32 bytes of flash.
//-----------------------------------------------------------------------------
void TGT_Read_Flash(void)
{
    // Command Format:
    // [0] Command
    // [1] flash key code0
    // [2] flash key code1
    // [3] addr0 (LSB)
    // [4] addr1 (MSB)
    // [5] numbytes

    // Response:
    // [0] Response code
    // [1] byte0
    // [2] byte1
    // [.] ...
    // [numbytes] byte(numbytes-1)

    UU16 start_addr;
    U8 numbytes;
    U8 Tx_Buf_ptr = 1;

    start_addr.U8[LSB] = SMB_DATA_IN[3];
    start_addr.U8[MSB] = SMB_DATA_IN[4];
    numbytes = SMB_DATA_IN[5];

    // Setup for flash operation
    TGT_Pre_Flash();

    // check for the whole range of address
    if (ValidAppAddr(start_addr.U16) & ValidAppAddr(start_addr.U16 + numbytes))
    {
        while (numbytes--)
        {
            SMB_DATA_OUT[Tx_Buf_ptr] = FLASH_ByteRead(start_addr.U16);

            Tx_Buf_ptr++;
            start_addr.U16++;
        }
        Set_TX_TGT_RSP_OK();
    }
    else
    {
        Set_TX_TGT_RSP_ADDR_INVALID();
    }
}

// This function checks if the address is valid
bool ValidAppAddr(U16 addr)
{
    if ((addr >= APP_FW_START_ADDR) & (addr <= APP_FW_END_ADDR))
    {
        return true;
    }
    else
    {
        return false;
    }

}
