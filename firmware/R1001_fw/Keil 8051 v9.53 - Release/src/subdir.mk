################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
A51_UPPER_SRCS += \
../src/SILABS_STARTUP.A51 

C_SRCS += \
../src/InitDevice.c \
../src/Interrupts.c \
../src/R1001_fw_main.c \
../src/drv8825.c \
../src/i2c.c 

OBJS += \
./src/InitDevice.OBJ \
./src/Interrupts.OBJ \
./src/R1001_fw_main.OBJ \
./src/SILABS_STARTUP.OBJ \
./src/drv8825.OBJ \
./src/i2c.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	wine /Applications/SimplicityStudio_v3/developer/toolchains/keil_8051/9.53/BIN/C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/InitDevice.OBJ: /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_fw/inc/InitDevice.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/si_toolchain.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdint.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdbool.h

src/Interrupts.OBJ: /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/compiler_defs.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_fw/inc/i2c.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_fw/inc/global.h /Applications/SimplicityStudio_v3/developer/toolchains/keil_8051/9.53/INC/MATH.H /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdbool.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdint.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/si_toolchain.h

src/R1001_fw_main.OBJ: /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_fw/inc/InitDevice.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/compiler_defs.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_fw/inc/drv8825.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_fw/inc/i2c.h /Users/sherifeid/plugge_git/R1001/firmware/R1001_fw/inc/global.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdbool.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdint.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/si_toolchain.h

src/%.OBJ: ../src/%.A51
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Assembler'
	wine /Applications/SimplicityStudio_v3/developer/toolchains/keil_8051/9.53/BIN/AX51 "@$(patsubst %.OBJ,%.__ia,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/drv8825.OBJ: /Users/sherifeid/plugge_git/R1001/firmware/R1001_fw/inc/drv8825.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/compiler_defs.h /Applications/SimplicityStudio_v3/developer/toolchains/keil_8051/9.53/INC/INTRINS.H /Users/sherifeid/plugge_git/R1001/firmware/R1001_fw/inc/global.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdbool.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdint.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/si_toolchain.h

src/i2c.OBJ: /Users/sherifeid/plugge_git/R1001/firmware/R1001_fw/inc/i2c.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Register_Enums.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/compiler_defs.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdint.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/EFM8BB1/inc/SI_EFM8BB1_Defs.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/stdbool.h /Applications/SimplicityStudio_v3/developer/sdks/si8051/v3/Device/shared/si8051Base/si_toolchain.h


