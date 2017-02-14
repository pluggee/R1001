################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
A51_UPPER_SRCS += \
../src/SILABS_STARTUP.A51 

C_SRCS += \
../src/BL_functions.c \
../src/EFM8BB1_FlashPrimitives.c \
../src/InitDevice.c \
../src/Interrupts.c \
../src/R1001_bl_main.c \
../src/smb.c 

OBJS += \
./src/BL_functions.OBJ \
./src/EFM8BB1_FlashPrimitives.OBJ \
./src/InitDevice.OBJ \
./src/Interrupts.OBJ \
./src/R1001_bl_main.OBJ \
./src/SILABS_STARTUP.OBJ \
./src/smb.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine /Applications/SimplicityStudio_v3/developer/toolchains/keil_8051/9.53/BIN/C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/BL_functions.OBJ: /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/BL_functions.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/compiler_defs.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/R1001_bl_main.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/EFM8BB1_FlashPrimitives.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdbool.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdint.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/si_toolchain.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h

src/EFM8BB1_FlashPrimitives.OBJ: /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/EFM8BB1_FlashPrimitives.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/si_toolchain.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdint.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdbool.h

src/InitDevice.OBJ: /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/InitDevice.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/si_toolchain.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdint.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdbool.h

src/Interrupts.OBJ: /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/smb.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/R1001_bl_main.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/si_toolchain.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdint.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdbool.h

src/R1001_bl_main.OBJ: /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/InitDevice.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/compiler_defs.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/R1001_bl_main.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/smb.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/BL_functions.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/EFM8BB1_FlashPrimitives.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdbool.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdint.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/si_toolchain.h

src/%.OBJ: ../src/%.A51
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Assembler'
	wine /Applications/SimplicityStudio_v3/developer/toolchains/keil_8051/9.53/BIN/AX51 "@$(patsubst %.OBJ,%.__ia,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/smb.OBJ: /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/compiler_defs.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/smb.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_bl/inc/R1001_bl_main.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdbool.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdint.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/si_toolchain.h


