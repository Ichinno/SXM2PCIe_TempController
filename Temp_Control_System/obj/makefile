################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Temp_Control_System.hex \

SECONDARY_LIST += \
Temp_Control_System.lst \

SECONDARY_SIZE += \
Temp_Control_System.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: Temp_Control_System.elf secondary-outputs

# Tool invocations
Temp_Control_System.elf: $(OBJS) $(USER_OBJS)
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -T "d:/Projects/Code/WCH_CH32X035C8T6/SRC/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -Xlinker --print-memory-usage -Wl,-Map,"Temp_Control_System.map" --specs=nano.specs --specs=nosys.specs -o "Temp_Control_System.elf" $(OBJS)  $(LIBS)
Temp_Control_System.hex: Temp_Control_System.elf
	@	riscv-none-embed-objcopy -O ihex "Temp_Control_System.elf" "Temp_Control_System.hex"
Temp_Control_System.lst: Temp_Control_System.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "Temp_Control_System.elf" > "Temp_Control_System.lst"
Temp_Control_System.siz: Temp_Control_System.elf
	riscv-none-embed-size --format=berkeley "Temp_Control_System.elf"

# Other Targets
clean:
	-$(RM) $(OBJS) $(EXPANDS) $(CALLGRAPH_DOT) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(S_DEPS)$(S_UPPER_DEPS)$(ASM_DEPS)$(ASM_UPPER_DEPS)$(C_DEPS) Temp_Control_System.elf

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets