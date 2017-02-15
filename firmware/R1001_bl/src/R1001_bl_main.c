
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
#include <compiler_defs.h>
#include "R1001_bl_main.h"
#include "smb.h"
#include "BL_functions.h"
#include "EFM8BB1_FlashPrimitives.h"

//-- Defines
#define APP_MODE        0
#define BOOTLOADER_MODE 1


// $[Generated Includes]
// [Generated Includes]$

// Global Variables
bit DATA_READY = 0;                    // Set to '1' by the SMBus ISR
                                       // when a new data byte has been
                                       // received.
// Global holder for SMBus data.
// All receive data is written here
// NUM_BYTES_WR used because an SMBus write is Master->Slave
uint8_t SMB_DATA_IN[TGT_BL_BUF_SIZE];

// Global holder for SMBus data.
// All transmit data is read from here
// NUM_BYTES_RD used because an SMBus read is Slave->Master
uint8_t SMB_DATA_OUT[TGT_BL_BUF_SIZE];


//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------

int main(void)
{
    // Call hardware initialization routine
//    enter_DefaultMode_from_RESET();


    U8 device_mode = BOOTLOADER_MODE;
    U8 code* codeptr;
    //---------------------------------------
    // Check the bootloader consition.
    //---------------------------------------
    codeptr = (U8 code*)(APP_FW_SIG0_ADDR);
   // The Signature (in Flash) should be valid to allow application FW execution.
   // This is written at the end of the bootloading process by the bootloader.
    if (*codeptr == SIG_BYTE0)
    {
        *codeptr--;
        if (*codeptr == SIG_BYTE1)
        {
            *codeptr--;
            if (*codeptr == SIG_BYTE2)
            {
                *codeptr--;
                if (*codeptr == SIG_BYTE3)
                {
                    // All signature bytes match.
                    device_mode = APP_MODE;
                }
            }
        }
    }

    // Enter bootloader mode on flash error reset
    if ((RSTSRC & 0x40) != 0)
    {
        // Check to see if the last reset was a flash error reset
        device_mode == BOOTLOADER_MODE;
    }

    if (device_mode == APP_MODE)
    {
        // If not in BL Override, jump to application
        START_APPLICATION();
    }

    //-------------------------------------------
    // ** BL Mode ** Initialize MCU and Variables
    //-------------------------------------------
    // Call hardware initialization routine
    enter_DefaultMode_from_RESET();
    // Set I2C address
    SetI2CSlaveAddress();

    //-------------------------------------------
    // Main Loop
    //-------------------------------------------

    while (1)
    {
        // Wait until a command is received
        while (!DATA_READY);             // New SMBus data received? gets out of the loop with a command transfer is complete

        DATA_READY = 0;

        // now we look at the contents of the data in the buffer and act accordingly
        switch(SMB_DATA_IN[0]){
            case TGT_CMD_RESET_MCU:
                Set_TX_TGT_RSP_OK();
                RSTSRC = 0x12; // Initiate software reset with vdd monitor enabled
                break;
            case TGT_CMD_ERASE_FLASH_PAGE:
                TGT_Erase_Page();
                break;
            case TGT_CMD_WRITE_FLASH_BYTES:
                TGT_Write_Flash();
                break;
            case TGT_CMD_READ_FLASH_BYTES:
                TGT_Read_Flash();
                break;
            default:
                Set_TX_TGT_RSP_UNSUPPORTED_CMD();
                break;
        }

        // Set flash keys to 0
//        Flash_Key0 = 0;
//        Flash_Key1 = 0;
    }
}
