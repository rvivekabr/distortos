#
# file: cmake/50-STM32-USARTv2.cmake
#
# author: Copyright (C) 2018-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
#
# Automatically generated file - do not edit!
#

distortosSetFixedConfiguration(BOOLEAN
		DISTORTOS_CHIP_USART_HAS_CR1_M1_BIT
		ON)

distortosSetConfiguration(BOOLEAN
		distortos_Peripherals_USART1
		OFF
		HELP "Enable USART1 low-level driver."
		OUTPUT_NAME DISTORTOS_CHIP_USART1_ENABLE)

distortosSetFixedConfiguration(BOOLEAN
		DISTORTOS_CHIP_USART1_HAS_FIFO
		OFF)

if(distortos_Peripherals_USART1)

	set(ARCHITECTURE_NVIC_USART1_ENABLE ON)

endif()

distortosSetConfiguration(BOOLEAN
		distortos_Peripherals_USART2
		OFF
		HELP "Enable USART2 low-level driver."
		OUTPUT_NAME DISTORTOS_CHIP_USART2_ENABLE)

distortosSetFixedConfiguration(BOOLEAN
		DISTORTOS_CHIP_USART2_HAS_FIFO
		OFF)

if(distortos_Peripherals_USART2)

	set(ARCHITECTURE_NVIC_USART2_ENABLE ON)

endif()

distortosSetConfiguration(BOOLEAN
		distortos_Peripherals_USART3
		OFF
		HELP "Enable USART3 low-level driver."
		OUTPUT_NAME DISTORTOS_CHIP_USART3_ENABLE)

distortosSetFixedConfiguration(BOOLEAN
		DISTORTOS_CHIP_USART3_HAS_FIFO
		OFF)

if(distortos_Peripherals_USART3)

	set(ARCHITECTURE_NVIC_USART3_ENABLE ON)

	list(APPEND DISTORTOS_CHIP_GPIOD_DEPENDENTS "USART3 RX")
	list(APPEND DISTORTOS_CHIP_GPIOD_DEPENDENTS "USART3 TX")

endif()

distortosSetConfiguration(BOOLEAN
		distortos_Peripherals_UART4
		OFF
		HELP "Enable UART4 low-level driver."
		OUTPUT_NAME DISTORTOS_CHIP_UART4_ENABLE)

distortosSetFixedConfiguration(BOOLEAN
		DISTORTOS_CHIP_UART4_HAS_FIFO
		OFF)

if(distortos_Peripherals_UART4)

	set(ARCHITECTURE_NVIC_UART4_ENABLE ON)

endif()

distortosSetConfiguration(BOOLEAN
		distortos_Peripherals_UART5
		OFF
		HELP "Enable UART5 low-level driver."
		OUTPUT_NAME DISTORTOS_CHIP_UART5_ENABLE)

distortosSetFixedConfiguration(BOOLEAN
		DISTORTOS_CHIP_UART5_HAS_FIFO
		OFF)

if(distortos_Peripherals_UART5)

	set(ARCHITECTURE_NVIC_UART5_ENABLE ON)

endif()

distortosSetConfiguration(BOOLEAN
		distortos_Peripherals_USART6
		OFF
		HELP "Enable USART6 low-level driver."
		OUTPUT_NAME DISTORTOS_CHIP_USART6_ENABLE)

distortosSetFixedConfiguration(BOOLEAN
		DISTORTOS_CHIP_USART6_HAS_FIFO
		OFF)

if(distortos_Peripherals_USART6)

	set(ARCHITECTURE_NVIC_USART6_ENABLE ON)

endif()

distortosSetConfiguration(BOOLEAN
		distortos_Peripherals_UART7
		OFF
		HELP "Enable UART7 low-level driver."
		OUTPUT_NAME DISTORTOS_CHIP_UART7_ENABLE)

distortosSetFixedConfiguration(BOOLEAN
		DISTORTOS_CHIP_UART7_HAS_FIFO
		OFF)

if(distortos_Peripherals_UART7)

	set(ARCHITECTURE_NVIC_UART7_ENABLE ON)

endif()

distortosSetConfiguration(BOOLEAN
		distortos_Peripherals_UART8
		OFF
		HELP "Enable UART8 low-level driver."
		OUTPUT_NAME DISTORTOS_CHIP_UART8_ENABLE)

distortosSetFixedConfiguration(BOOLEAN
		DISTORTOS_CHIP_UART8_HAS_FIFO
		OFF)

if(distortos_Peripherals_UART8)

	set(ARCHITECTURE_NVIC_UART8_ENABLE ON)

endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/source/chip/STM32/peripherals/USARTv2/distortos-sources.cmake")
