################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Keil tools exit code 1 is warnings only, so don't treat as an error in make
RC := test $$? -lt 2

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: R1001_bl.omf

# Tool invocations
R1001_bl.omf: echo_path $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Keil 8051 Linker'
	wine /Applications/SimplicityStudio_v3/developer/toolchains/keil_8051/9.53/BIN/LX51 "@R1001_bl.lnp" || $(RC)
	@echo 'Finished building target: $@'

# Change from all upper case to the expected case
	@-mv "R1001_BL.OMF.CRBUILD" "$@"

# Generate hex file: R1001_bl.hex
	@wine /Applications/SimplicityStudio_v3/developer/toolchains/keil_8051/9.53/BIN/Ohx51 "R1001_bl.omf" "HEXFILE (R1001_bl.hex)" "H386" 2>&1 >/dev/null

# Other Targets
clean:
	-$(RM) $(OBJS)$(EXECUTABLES) R1001_bl.omf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
# echo the path
echo_path:
	@echo PATH=$$PATH
	@echo ' '

