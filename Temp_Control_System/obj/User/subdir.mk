################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/AiP650E.c \
../User/ch32x035_it.c \
../User/main.c \
../User/system_ch32x035.c 

C_DEPS += \
./User/AiP650E.d \
./User/ch32x035_it.d \
./User/main.d \
./User/system_ch32x035.d 

OBJS += \
./User/AiP650E.o \
./User/ch32x035_it.o \
./User/main.o \
./User/system_ch32x035.o 


EXPANDS += \
./User/AiP650E.c.234r.expand \
./User/ch32x035_it.c.234r.expand \
./User/main.c.234r.expand \
./User/system_ch32x035.c.234r.expand 



# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

