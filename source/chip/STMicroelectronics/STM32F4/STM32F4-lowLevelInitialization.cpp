/**
 * \file
 * \brief chip::lowLevelInitialization() implementation for STM32F4
 *
 * \author Copyright (C) 2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-09-18
 */

#include "distortos/chip/lowLevelInitialization.hpp"

#include "distortos/chip/STM32F4-FLASH.hpp"
#include "distortos/chip/STM32F4-RCC.hpp"

#include "distortos/architecture/configureSysTick.hpp"

namespace distortos
{

namespace chip
{

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void lowLevelInitialization()
{
#ifdef CONFIG_CHIP_STM32F4_FLASH_PREFETCH_ENABLE
	configureInstructionPrefetch(true);
#else	// !def CONFIG_CHIP_STM32F4_FLASH_PREFETCH_ENABLE
	configureInstructionPrefetch(false);
#endif	// !def CONFIG_CHIP_STM32F4_FLASH_PREFETCH_ENABLE
	enableInstructionCache();
	enableDataCache();

#ifdef CONFIG_CHIP_STM32F4_RCC_STANDARD_CLOCK_CONFIGURATION_ENABLE

#ifdef CONFIG_CHIP_STM32F4_RCC_HSE_ENABLE

#ifdef CONFIG_CHIP_STM32F4_RCC_HSE_CLOCK_BYPASS
	constexpr bool hseClockBypass {true};
#else	// !def CONFIG_CHIP_STM32F4_RCC_HSE_CLOCK_BYPASS
	constexpr bool hseClockBypass {};
#endif	// !def CONFIG_CHIP_STM32F4_RCC_HSE_CLOCK_BYPASS
	enableHse(hseClockBypass);

#endif	// def CONFIG_CHIP_STM32F4_RCC_HSE_ENABLE

#ifdef CONFIG_CHIP_STM32F4_RCC_PLL_ENABLE

#if defined(CONFIG_CHIP_STM32F4_RCC_PLLSRC_HSI)
	constexpr bool pllClockSourceHse {};
#elif defined(CONFIG_CHIP_STM32F4_RCC_PLLSRC_HSE)
	constexpr bool pllClockSourceHse {true};
#endif
	configurePllClockSource(pllClockSourceHse);

	constexpr uint32_t pllInHz {pllClockSourceHse == false ? hsiHz : CONFIG_CHIP_STM32F4_RCC_HSE_HZ};
	constexpr uint32_t vcoInHz {pllInHz / CONFIG_CHIP_STM32F4_RCC_PLLM};
	static_assert(minVcoInHz <= vcoInHz && vcoInHz <= maxVcoInHz, "Invalid VCO input frequency!");
	configurePllInputClockDivider(CONFIG_CHIP_STM32F4_RCC_PLLM);

	constexpr uint32_t vcoOutHz {vcoInHz * CONFIG_CHIP_STM32F4_RCC_PLLN};
	static_assert(minVcoOutHz <= vcoOutHz && vcoOutHz <= maxVcoOutHz, "Invalid VCO output frequency!");

#if defined(CONFIG_CHIP_STM32F4_RCC_PLLP_DIV2)
	constexpr uint8_t pllp {pllpDiv2};
#elif defined(CONFIG_CHIP_STM32F4_RCC_PLLP_DIV4)
	constexpr uint8_t pllp {pllpDiv4};
#elif defined(CONFIG_CHIP_STM32F4_RCC_PLLP_DIV6)
	constexpr uint8_t pllp {pllpDiv6};
#elif defined(CONFIG_CHIP_STM32F4_RCC_PLLP_DIV8)
	constexpr uint8_t pllp {pllpDiv8};
#endif

	constexpr uint32_t pllOutHz {vcoOutHz / pllp};
	static_assert(pllOutHz <= maxPllOutHz, "Invalid PLL output frequency!");

	constexpr uint32_t pllqOutHz {vcoOutHz / CONFIG_CHIP_STM32F4_RCC_PLLQ};
	static_assert(pllqOutHz <= maxPllqOutHz, "Invalid PLL \"Q\" output frequency!");

	enablePll(CONFIG_CHIP_STM32F4_RCC_PLLN, pllp, CONFIG_CHIP_STM32F4_RCC_PLLQ);

#endif	// def CONFIG_CHIP_STM32F4_RCC_PLL_ENABLE

#if defined(CONFIG_CHIP_STM32F4_RCC_SYSCLK_HSI)
	constexpr uint32_t sysclkHz {hsiHz};
	constexpr SystemClockSource systemClockSource {SystemClockSource::hsi};
#elif defined(CONFIG_CHIP_STM32F4_RCC_SYSCLK_HSE)
	constexpr uint32_t sysclkHz {CONFIG_CHIP_STM32F4_RCC_HSE_HZ};
	constexpr SystemClockSource systemClockSource {SystemClockSource::hse};
#elif defined(CONFIG_CHIP_STM32F4_RCC_SYSCLK_PLL)
	constexpr uint32_t sysclkHz {pllOutHz};
	constexpr SystemClockSource systemClockSource {SystemClockSource::pll};
#endif	// defined(CONFIG_CHIP_STM32F4_RCC_SYSCLK_PLL)

#if defined(CONFIG_CHIP_STM32F4_RCC_AHB_DIV1)
	constexpr auto hpre = hpreDiv1;
#elif defined(CONFIG_CHIP_STM32F4_RCC_AHB_DIV2)
	constexpr auto hpre = hpreDiv2;
#elif defined(CONFIG_CHIP_STM32F4_RCC_AHB_DIV4)
	constexpr auto hpre = hpreDiv4;
#elif defined(CONFIG_CHIP_STM32F4_RCC_AHB_DIV8)
	constexpr auto hpre = hpreDiv8;
#elif defined(CONFIG_CHIP_STM32F4_RCC_AHB_DIV16)
	constexpr auto hpre = hpreDiv16;
#elif defined(CONFIG_CHIP_STM32F4_RCC_AHB_DIV64)
	constexpr auto hpre = hpreDiv64;
#elif defined(CONFIG_CHIP_STM32F4_RCC_AHB_DIV128)
	constexpr auto hpre = hpreDiv128;
#elif defined(CONFIG_CHIP_STM32F4_RCC_AHB_DIV256)
	constexpr auto hpre = hpreDiv256;
#elif defined(CONFIG_CHIP_STM32F4_RCC_AHB_DIV512)
	constexpr auto hpre = hpreDiv512;
#endif	// defined(CONFIG_CHIP_STM32F4_RCC_AHB_DIV512)

	constexpr uint32_t ahbHz {sysclkHz / hpre};
	configureAhbClockDivider(hpre);

#if defined(CONFIG_CHIP_STM32F4_RCC_APB1_DIV1)
	constexpr auto ppre1 = ppreDiv1;
#elif defined(CONFIG_CHIP_STM32F4_RCC_APB1_DIV2)
	constexpr auto ppre1 = ppreDiv2;
#elif defined(CONFIG_CHIP_STM32F4_RCC_APB1_DIV4)
	constexpr auto ppre1 = ppreDiv4;
#elif defined(CONFIG_CHIP_STM32F4_RCC_APB1_DIV8)
	constexpr auto ppre1 = ppreDiv8;
#elif defined(CONFIG_CHIP_STM32F4_RCC_APB1_DIV16)
	constexpr auto ppre1 = ppreDiv16;
#endif	// defined(CONFIG_CHIP_STM32F4_RCC_APB1_DIV16)

	constexpr uint32_t apb1Hz {ahbHz / ppre1};
	static_assert(apb1Hz <= maxApb1Hz, "Invalid APB1 (low speed) frequency!");
	configureApbClockDivider(false, ppre1);

#if defined(CONFIG_CHIP_STM32F4_RCC_APB2_DIV1)
	constexpr auto ppre2 = ppreDiv1;
#elif defined(CONFIG_CHIP_STM32F4_RCC_APB2_DIV2)
	constexpr auto ppre2 = ppreDiv2;
#elif defined(CONFIG_CHIP_STM32F4_RCC_APB2_DIV4)
	constexpr auto ppre2 = ppreDiv4;
#elif defined(CONFIG_CHIP_STM32F4_RCC_APB2_DIV8)
	constexpr auto ppre2 = ppreDiv8;
#elif defined(CONFIG_CHIP_STM32F4_RCC_APB2_DIV16)
	constexpr auto ppre2 = ppreDiv16;
#endif	// defined(CONFIG_CHIP_STM32F4_RCC_APB2_DIV16)

	constexpr uint32_t apb2Hz {ahbHz / ppre2};
	static_assert(apb2Hz <= maxApb2Hz, "Invalid APB2 (high speed) frequency!");
	configureApbClockDivider(true, ppre2);

#else	// !def CONFIG_CHIP_STM32F4_RCC_STANDARD_CLOCK_CONFIGURATION_ENABLE

	constexpr uint32_t ahbHz {CONFIG_CHIP_STM32F4_RCC_AHB_HZ};

#endif	// !def CONFIG_CHIP_STM32F4_RCC_STANDARD_CLOCK_CONFIGURATION_ENABLE

#if CONFIG_CHIP_STM32F4_VDD_MV < 2100
	constexpr uint32_t frequencyThresholdHz {20000000};
#elif CONFIG_CHIP_STM32F4_VDD_MV < 2400
	constexpr uint32_t frequencyThresholdHz {22000000};
#elif CONFIG_CHIP_STM32F4_VDD_MV < 2700
	constexpr uint32_t frequencyThresholdHz {24000000};
#else
	constexpr uint32_t frequencyThresholdHz {30000000};
#endif

	constexpr uint8_t flashLatency {(ahbHz - 1) / frequencyThresholdHz};
	static_assert(flashLatency <= maxFlashLatency, "Invalid flash latency!");
	configureFlashLatency(flashLatency);

#ifdef CONFIG_CHIP_STM32F4_RCC_STANDARD_CLOCK_CONFIGURATION_ENABLE

	switchSystemClock(systemClockSource);

#endif	// def CONFIG_CHIP_STM32F4_RCC_STANDARD_CLOCK_CONFIGURATION_ENABLE

	constexpr uint32_t period {ahbHz / CONFIG_TICK_RATE_HZ};
	constexpr uint32_t periodDividedBy8 {period / 8};
	constexpr bool divideBy8 {period > architecture::maxSysTickPeriod};
	// at least one of the periods must be valid
	static_assert(period <= architecture::maxSysTickPeriod || periodDividedBy8 <= architecture::maxSysTickPeriod,
			"Invalid SysTick configuration!");
	architecture::configureSysTick(divideBy8 == false ? period : periodDividedBy8, divideBy8);
}

}	// namespace chip

}	// namespace distortos