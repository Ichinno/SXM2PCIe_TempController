################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Startup/startup_ch32x035.S 

S_UPPER_DEPS += \
./Startup/startup_ch32x035.d 

OBJS += \
./Startup/startup_ch32x035.o 


EXPANDS += \
./Startup/startup_ch32x035.S.234r.expand 



# Each subdirectory must supply rules for building sources it contributes
Startup/startup_ch32x035.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Startup/startup_ch32x035.S
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -x assembler-with-cpp -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

