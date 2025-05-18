##############################################################################
# Definitions for the STM32 U073 board
##############################################################################

#-----------------------------------------------------------------------------
# Compilation flags
#-----------------------------------------------------------------------------

#MCU compilation flags
MCU_FLAGS ?= -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft

BOARD_C_DEFS =  \
	-DUSE_HAL_DRIVER \
	-DSTM32U073xx

#-----------------------------------------------------------------------------
# Hardware-specific sources
#-----------------------------------------------------------------------------
BOARD_C_SOURCES = \
	smtc_modem_hal/smtc_modem_hal.c\
	smtc_hal_u0/smtc_hal_flash.c\
	smtc_hal_u0/smtc_hal_gpio.c\
	smtc_hal_u0/smtc_hal_mcu.c\
	smtc_hal_u0/smtc_hal_rtc.c\
	smtc_hal_u0/smtc_hal_rng.c\
	smtc_hal_u0/smtc_hal_spi.c\
	smtc_hal_u0/smtc_hal_lp_timer.c\
	smtc_hal_u0/smtc_hal_trace.c\
	smtc_hal_u0/smtc_hal_uart.c\
	smtc_hal_u0/smtc_hal_watchdog.c

BOARD_C_INCLUDES =  \
	-Imcu_drivers/core/STM32U0xx\
	-Imcu_drivers/cmsis/Core/Include\
	-Imcu_drivers/cmsis/Device/ST/STM32U0xx/Include\
	-Imcu_drivers/STM32U0xx_HAL_Driver/Inc\
	-Imcu_drivers/STM32U0xx_HAL_Driver/Inc/Legacy\
	-Ismtc_modem_hal\
	-I.\
	-Ismtc_hal_u0
