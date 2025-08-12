################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug/debug.c 

C_DEPS += \
./Debug/debug.d 

OBJS += \
./Debug/debug.o 


EXPANDS += \
./Debug/debug.c.234r.expand 



# Each subdirectory must supply rules for building sources it contributes
Debug/debug.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug/debug.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

