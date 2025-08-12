################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_adc.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_awu.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_dbgmcu.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_dma.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_exti.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_flash.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_gpio.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_i2c.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_iwdg.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_misc.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_opa.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_pwr.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_rcc.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_spi.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_tim.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_usart.c \
d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_wwdg.c 

C_DEPS += \
./Peripheral/src/ch32x035_adc.d \
./Peripheral/src/ch32x035_awu.d \
./Peripheral/src/ch32x035_dbgmcu.d \
./Peripheral/src/ch32x035_dma.d \
./Peripheral/src/ch32x035_exti.d \
./Peripheral/src/ch32x035_flash.d \
./Peripheral/src/ch32x035_gpio.d \
./Peripheral/src/ch32x035_i2c.d \
./Peripheral/src/ch32x035_iwdg.d \
./Peripheral/src/ch32x035_misc.d \
./Peripheral/src/ch32x035_opa.d \
./Peripheral/src/ch32x035_pwr.d \
./Peripheral/src/ch32x035_rcc.d \
./Peripheral/src/ch32x035_spi.d \
./Peripheral/src/ch32x035_tim.d \
./Peripheral/src/ch32x035_usart.d \
./Peripheral/src/ch32x035_wwdg.d 

OBJS += \
./Peripheral/src/ch32x035_adc.o \
./Peripheral/src/ch32x035_awu.o \
./Peripheral/src/ch32x035_dbgmcu.o \
./Peripheral/src/ch32x035_dma.o \
./Peripheral/src/ch32x035_exti.o \
./Peripheral/src/ch32x035_flash.o \
./Peripheral/src/ch32x035_gpio.o \
./Peripheral/src/ch32x035_i2c.o \
./Peripheral/src/ch32x035_iwdg.o \
./Peripheral/src/ch32x035_misc.o \
./Peripheral/src/ch32x035_opa.o \
./Peripheral/src/ch32x035_pwr.o \
./Peripheral/src/ch32x035_rcc.o \
./Peripheral/src/ch32x035_spi.o \
./Peripheral/src/ch32x035_tim.o \
./Peripheral/src/ch32x035_usart.o \
./Peripheral/src/ch32x035_wwdg.o 


EXPANDS += \
./Peripheral/src/ch32x035_adc.c.234r.expand \
./Peripheral/src/ch32x035_awu.c.234r.expand \
./Peripheral/src/ch32x035_dbgmcu.c.234r.expand \
./Peripheral/src/ch32x035_dma.c.234r.expand \
./Peripheral/src/ch32x035_exti.c.234r.expand \
./Peripheral/src/ch32x035_flash.c.234r.expand \
./Peripheral/src/ch32x035_gpio.c.234r.expand \
./Peripheral/src/ch32x035_i2c.c.234r.expand \
./Peripheral/src/ch32x035_iwdg.c.234r.expand \
./Peripheral/src/ch32x035_misc.c.234r.expand \
./Peripheral/src/ch32x035_opa.c.234r.expand \
./Peripheral/src/ch32x035_pwr.c.234r.expand \
./Peripheral/src/ch32x035_rcc.c.234r.expand \
./Peripheral/src/ch32x035_spi.c.234r.expand \
./Peripheral/src/ch32x035_tim.c.234r.expand \
./Peripheral/src/ch32x035_usart.c.234r.expand \
./Peripheral/src/ch32x035_wwdg.c.234r.expand 



# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/ch32x035_adc.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_adc.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_awu.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_awu.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_dbgmcu.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_dbgmcu.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_dma.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_dma.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_exti.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_exti.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_flash.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_flash.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_gpio.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_gpio.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_i2c.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_i2c.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_iwdg.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_iwdg.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_misc.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_misc.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_opa.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_opa.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_pwr.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_pwr.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_rcc.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_rcc.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_spi.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_spi.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_tim.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_tim.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_usart.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_usart.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Peripheral/src/ch32x035_wwdg.o: d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/src/ch32x035_wwdg.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Debug" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Core" -I"d:/Projects/Code/WCH_CH32X035C8T6/Temp_Control_System/User" -I"d:/Projects/Code/WCH_CH32X035C8T6/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

